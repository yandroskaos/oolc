#include "types_builder_visitor.h"

#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>

#include <symbols/symbols.h>

#include <errors/handler.h>
#include <utils/functional.h>

using namespace Semantics;
using namespace AST;

VISIT(TypesBuilderVisitor, ProgramNode)
{
	TypesInserterVisitor typesInserter;
	_node->Accept(&typesInserter);

	TypesConstructorVisitor typesConstructor;
	_node->Accept(&typesConstructor);
}



void TypesInserterVisitor::CheckDoesNotExists(string _type, int _line)
{
	Types::Type* t = Types::table[_type];
	
	if(t)
	{
		ErrorHandler::SemanticError("Type " + _type + " has already been defined", _line);
	}
}

VISIT(TypesInserterVisitor, InterfaceNode)
{
	CheckDoesNotExists(_node->name, _node->GetLine());

	Types::Interface* interfaceType = new Types::Interface(_node->name);
	Types::table.Add(interfaceType);

	_node->SetType(interfaceType);
}

VISIT(TypesInserterVisitor, ClassNode)
{
	CheckDoesNotExists(_node->name, _node->GetLine());
	
	Types::Class* classType = new Types::Class(_node->name);
	Types::table.Add(classType);

	_node->SetType(classType);
}



TypesConstructorVisitor::TypesConstructorVisitor()
	: actualClass(0)
{
}

VISIT(TypesConstructorVisitor, InterfaceNode)
{
	actualClass = dynamic_cast<Types::Class*>(Types::table[_node->name]);

	COLLECTION_ACCEPT(_node->members);
}

VISIT(TypesConstructorVisitor, PrototypeNode)
{
	bool errors = false;

	if(!Types::table[_node->returnType])
	{
		ErrorHandler::SemanticError("Return type " + _node->returnType + " from interface method " + _node->name + " does not exist", _node->GetLine());
		errors = true;
	}
	
	for(auto typeName : _node->argumentTypes)
	{
		Types::Type* t = Types::table[typeName];
		if(!t)
		{
			ErrorHandler::SemanticError("Argument type " + typeName + " from interface method " + _node->name + " does not exist", _node->GetLine());
			errors = true;
		}
		else if (Types::Type::IsVoid(*t))
		{
			ErrorHandler::SemanticError("Argument type " + typeName + " from interface method " + _node->name + " is void", _node->GetLine());
			errors = true;
		}
	}

	if(Types::table[_node->name])
	{
		ErrorHandler::SemanticError("Interface method " + _node->name + " has the same name as an existing type", _node->GetLine());
		errors = true;
	}

	if(errors)
		return;

	Types::Method*   methodType   = new Types::Method(_node->returnType, _node->argumentTypes);
	Symbols::Method* methodSymbol = new Symbols::Method(_node->name, vector<string>(), methodType, actualClass, false, Symbols::Access::Public);
	actualClass->AddMethod(methodSymbol);

	_node->SetType(methodType);
	_node->symbol = methodSymbol;
}

VISIT(TypesConstructorVisitor, ClassNode)
{
	bool errors = false;

	actualClass = dynamic_cast<Types::Class*>(Types::table[_node->name]);
	
	if(_node->parent != "")
	{
		Types::Type* parent = Types::table[_node->parent];
		if(!parent)
		{
			ErrorHandler::SemanticError("Parent class " + _node->parent + " of class " + _node->name + " has not been defined", _node->GetLine());
			errors = true;
		}
		else if(!Types::Type::IsClass(*parent))
		{
			ErrorHandler::SemanticError("Type " + _node->parent + " cannot be parent of class " + _node->name, _node->GetLine());
			errors = true;
		}
		else
		{
			actualClass->SetParent(dynamic_cast<Types::Class*>(parent));
		}
	}

	for(auto interfaceName : _node->interfaces)
	{
		Types::Type* interfaceType = Types::table[interfaceName];
		if(!interfaceType)
		{
			ErrorHandler::SemanticError("Interface type " + interfaceName + " in definition of class " + _node->name + " has not been defined", _node->GetLine());
			errors = true;
		}
		else if(!Types::Type::IsInterface(*interfaceType))
		{
			ErrorHandler::SemanticError("Interface type " + interfaceName + " in definition of class " + _node->name + " is not an interface", _node->GetLine());
		}
		else
		{
			actualClass->AddInterface(dynamic_cast<Types::Interface*>(interfaceType));
		}
	}

	if(errors)
		return;

	COLLECTION_ACCEPT(_node->members);

	vector<Symbols::Method*> constructors = actualClass->GetMethod(_node->name);

	bool parameterlessConstructor = 
	predicateT<Symbols::Method*>(constructors, [](Symbols::Method* c)
	{
		Types::Method* type = dynamic_cast<Types::Method*>(c->Type());
		return type->GetArguments().empty();
	});

	if(!parameterlessConstructor)
	{
		AST::BlockStatementNode* body = new AST::BlockStatementNode();

		AST::MethodNode* emptyConstructor = new AST::MethodNode();
		emptyConstructor->isStatic   = false;
        emptyConstructor->access     = Symbols::Access::Public;
		emptyConstructor->returnType = "void";
		emptyConstructor->name       = _node->name;
		emptyConstructor->argumentTypes.clear();
		emptyConstructor->argumentNames.clear();
		
		body->SetParent(emptyConstructor);
		emptyConstructor->body = body;

		emptyConstructor->SetParent(_node);
		_node->members.push_back(emptyConstructor);

		Types::Method*   methodType   = new Types::Method("void", vector<string>());
		Symbols::Method* methodSymbol = new Symbols::Method(_node->name, vector<string>(), methodType, actualClass, false, Symbols::Access::Public);
		actualClass->AddMethod(methodSymbol);

		emptyConstructor->SetType(methodType);
		emptyConstructor->symbol = methodSymbol;
	}
}

VISIT(TypesConstructorVisitor, AttributeNode)
{
	bool errors = false;

	Types::Type* type = Types::table[_node->type];
	if(!type)
	{
		ErrorHandler::SemanticError("Type " + _node->type + " of attribute " + _node->name + " has not been defined", _node->GetLine());
		errors = true;
	}
	else if(Types::Type::IsVoid(*type))
	{
		ErrorHandler::SemanticError("Type " + _node->type + " of attribute " + _node->name + " cannot be void", _node->GetLine());
		errors = false;
	}

	if(Types::table[_node->name])
	{
		ErrorHandler::SemanticError("Attribute " + _node->name + " has the same name as an existing type", _node->GetLine());
		errors = true;
	}

	if(actualClass->GetAttribute(_node->name))
	{
		ErrorHandler::SemanticError("Attribute " + _node->name + " in class " + actualClass->Name() + " has already been defined", _node->GetLine());
		errors = true;
	}

	Symbols::Attribute* attribute = new Symbols::Attribute(_node->name, type, actualClass, _node->isStatic, _node->access);
	actualClass->AddAttribute(attribute);

	_node->SetType(type);
	_node->symbol = attribute;
}

VISIT(TypesConstructorVisitor, MethodNode)
{
	bool errors = false;

	if(!Types::table[_node->returnType])
	{
		ErrorHandler::SemanticError("Return type " + _node->returnType + " from class method " + _node->name + " does not exist", _node->GetLine());
		errors = true;
	}
	
	for(auto typeName : _node->argumentTypes)
	{
		Types::Type* t = Types::table[typeName];
		if(!t)
		{
			ErrorHandler::SemanticError("Argument type " + typeName + " from class method " + _node->name + " does not exist", _node->GetLine());
			errors = true;
		}
		else if(Types::Type::IsVoid(*t))
		{
			ErrorHandler::SemanticError("Argument type " + typeName + " from class method " + _node->name + " is void", _node->GetLine());
			errors = true;
		}
	}

	if(_node->name != actualClass->Name() && Types::table[_node->name])
	{
		ErrorHandler::SemanticError("Class method " + _node->name + " has the same name as an existing type", _node->GetLine());
		errors = true;
	}

	Types::Method* methodType = new Types::Method(_node->returnType, _node->argumentTypes);

	vector<Symbols::Method*> methodList = actualClass->GetMethod(_node->name);
	for(auto method : methodList)
	{
		Types::Method* type = dynamic_cast<Types::Method*>(method->Type());
		if(type->CompareSignature(methodType))
		{
			ErrorHandler::SemanticError("Method with same signature [" + type->Name() + "] has already been defined in class " + actualClass->Name(), _node->GetLine());
			errors = true;
		}
	}

	if(errors)
		return;

	Symbols::Method* methodSymbol = new Symbols::Method(_node->name, _node->argumentNames, methodType, actualClass, _node->isStatic, _node->access);
	actualClass->AddMethod(methodSymbol);

	_node->SetType(methodType);
	_node->symbol = methodSymbol; 
}
