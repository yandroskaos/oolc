#include <cassert>
#include "types_decorator_visitor.h"

#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>

#include <errors/handler.h>

using namespace Semantics;
using namespace AST;

void TypesDecoratorVisitor::InsertCast(string _type, AST::Node* _parent, AST::Node*& _son, int _line)
{
	if(_type == "null" || Types::Type::IsNull(*_son->GetType()))
		return;

	ErrorHandler::Warning("Implicit cast from " + _son->GetType()->Name() + " to " + _type, _line);

	AST::CastExprNode* castNode = new AST::CastExprNode(_type, _son);
	castNode->SetType(Types::table[_type]);

	_son->SetParent(castNode);
	castNode->SetParent(_parent);
	
	_son = castNode;
}

void TypesDecoratorVisitor::CheckAssignment(Types::Type* _tl, Types::Type* _tr, AST::Node* _parent,	AST::Node* _son)
{
	if(*_tl != *_tr)
	{
		if(_tr->ImplicitCastTo(*_tl))
		{
			if(!Types::Type::IsNull(*_tr))
			{
				InsertCast(_tl->Name(), _parent, _son, _parent->GetLine());
			}
		}
		else
		{
			ErrorHandler::SemanticError("Type " + _tr->Name() + " cannot be assigned to type " + _tl->Name(), _parent->GetLine());
		}
	}
}

void TypesDecoratorVisitor::CheckBooleanExpresion(AST::BinaryOperatorExprNode* _node)
{
	Types::Type* t1 = _node->leftExpr->GetType();
	Types::Type* t2 = _node->rightExpr->GetType();

	if(!Types::Type::IsBool(*t1))
	{
		ErrorHandler::SemanticError("Left type " + t1->Name() + " is not bool", _node->GetLine());
	}

	if(!Types::Type::IsBool(*t2))
	{
		ErrorHandler::SemanticError("Right type " + t2->Name() + " is not bool", _node->GetLine());
	}

	_node->SetType(Types::table["bool"]);
}

void TypesDecoratorVisitor::CheckEqualityExpresion(AST::BinaryOperatorExprNode* _node)
{
	Types::Type* t1 = _node->leftExpr->GetType();
	Types::Type* t2 = _node->rightExpr->GetType();

	if(Types::Type::IsVoid(*t1) || Types::Type::IsMethod(*t1))
	{
		ErrorHandler::SemanticError("Left type " + t1->Name() + " cannot be used in a comparison", _node->GetLine());
	}

	if(Types::Type::IsVoid(*t2) || Types::Type::IsMethod(*t2))
	{
		ErrorHandler::SemanticError("Right type " + t2->Name() + " cannot be used in a comparison", _node->GetLine());
	}

	if(t1->ImplicitCastTo(*t2))
	{
		InsertCast(t2->Name(), _node, _node->leftExpr, _node->GetLine());
	}
	
	if(t2->ImplicitCastTo(*t1))
	{
		InsertCast(t1->Name(), _node, _node->rightExpr, _node->GetLine());
	}

	_node->SetType(Types::table["bool"]);
}

void TypesDecoratorVisitor::CheckRelationalExpresion(AST::BinaryOperatorExprNode* _node)
{
	Types::Type* t1 = _node->leftExpr->GetType();
	Types::Type* t2 = _node->rightExpr->GetType();

	if(!Types::Type::IsNumeric(*t1))
	{
		ErrorHandler::SemanticError("Left type " + t1->Name() + " is not char, int or real", _node->GetLine());
	}

	if(!Types::Type::IsNumeric(*t2))
	{
		ErrorHandler::SemanticError("Right type " + t2->Name() + " is not char, int or real", _node->GetLine());
	}

	if(t1->ImplicitCastTo(*t2))
	{
		InsertCast(t2->Name(), _node, _node->leftExpr, _node->GetLine());
	}
	
	if(t2->ImplicitCastTo(*t1))
	{
		InsertCast(t1->Name(), _node, _node->rightExpr, _node->GetLine());
	}

	_node->SetType(Types::table["bool"]);
}

void TypesDecoratorVisitor::CheckAritmethicalExpresion(AST::BinaryOperatorExprNode* _node)
{
	Types::Type* t1 = _node->leftExpr->GetType();
	Types::Type* t2 = _node->rightExpr->GetType();

	if(!Types::Type::IsNumeric(*t1))
	{
		ErrorHandler::SemanticError("Left type " + t1->Name() + " is not char, int or real", _node->GetLine());
	}

	if(!Types::Type::IsNumeric(*t2))
	{
		ErrorHandler::SemanticError("Right type " + t2->Name() + " is not char, int or real", _node->GetLine());
	}

	if(t1->ImplicitCastTo(*t2))
	{
		InsertCast(t2->Name(), _node, _node->leftExpr, _node->GetLine());
		_node->SetType(t2);
	}
	else if(t2->ImplicitCastTo(*t1) )
	{
		InsertCast(t1->Name(), _node, _node->rightExpr, _node->GetLine());
		_node->SetType(t1);
	}
	else
		_node->SetType(t1);
}

Types::Method* TypesDecoratorVisitor::CreateMethodType(Collection const& _arguments)
{
	vector<string> argumentTypeNames;
	for(auto argument : _arguments)
	{
		string typeName = argument->GetType()->Name();
		argumentTypeNames.push_back(typeName);
	}

	Types::Method* methodType = new Types::Method("void", argumentTypeNames);
	
	Types::Type* t = Types::table[methodType->Name()];
	if(t)
	{
		delete methodType;
		return dynamic_cast<Types::Method*>(t);
	}
	
	Types::table.Add(methodType);
	return methodType;
}

bool TypesDecoratorVisitor::FindMethod(Types::Method* _methodType, vector<Symbols::Method*> _methodList, Symbols::Method*& _methodWanted)
{
	_methodWanted = 0;

	//
	// Find exact match
	//	
	for(Symbols::Method* method : _methodList)
	{
		if(_methodType->CompareSignature(dynamic_cast<Types::Method*>(method->Type())))
		{
			_methodWanted = method;
			break;
		}
	}
	if(_methodWanted)
		return true;

	//
	// If not found, look up for an overload with implicit casts
	//
	for(Symbols::Method* method : _methodList)
	{
		if(_methodType->ImplicitCastTo(*method->Type()))
		{
			_methodWanted = method;
			break;
		}
	}

	if(_methodWanted)
		return true;

	//
	// There is no call with those type parameters
	//
	return false;
}

void TypesDecoratorVisitor::CastMethodCall(Types::Method* _methodType, AST::Collection& _arguments, AST::Node* _parent, int _lineNumber)
{
	vector<Types::Type*> argTypes = _methodType->GetArguments();
	for(size_t i = 0; i < argTypes.size(); ++i)
	{
		Types::Type* t = _arguments[i]->GetType();

		if( *t != *argTypes[i] &&
		     t->ImplicitCastTo(*argTypes[i]))
		{
			InsertCast(argTypes[i]->Name(), _parent, _arguments[i], _lineNumber);
		}
	}
}

void TypesDecoratorVisitor::SlotContextSet()
{
	contexts.push(stack<Types::Type*>());
}

void TypesDecoratorVisitor::SlotContextReset()
{
	contexts.pop();
}

bool TypesDecoratorVisitor::SlotContextEmpty()
{
	return contexts.top().empty();
}

Types::Type* TypesDecoratorVisitor::SlotContextLastType()
{
	return contexts.top().top();
}

void TypesDecoratorVisitor::SlotContextPush(Types::Type* _type)
{
	contexts.top().push(_type);
}

bool TypesDecoratorVisitor::SlotContextError()
{
	return !SlotContextEmpty() && SlotContextLastType() == 0;
}

void TypesDecoratorVisitor::SlotContextSetError()
{
	SlotContextPush(0);
}

bool TypesDecoratorVisitor::SlotContextAnidated()
{
	return contexts.size() > 1;
}

TypesDecoratorVisitor::TypesDecoratorVisitor()
	: actualClass(0)
	, actualMethod(0)
	, actualVariableAddress(0)
{}

VISIT(TypesDecoratorVisitor, ClassNode)
{
	actualClass = dynamic_cast<Types::Class*>(Types::table[_node->name]);
	
	COLLECTION_ACCEPT(_node->members);
}

VISIT(TypesDecoratorVisitor, AttributeNode)
{
	Types::Class* parent = actualClass->GetParent();
	while(parent)
	{
		Symbols::Attribute* attributeInParents = parent->GetAttribute(_node->name);
		if(attributeInParents && attributeInParents->GetAccess() != Symbols::Access::Private)
		{
			ErrorHandler::SemanticError("Attribute " + _node->name + " in class " + actualClass->Name() + " has already been defined in a parent class " + parent->Name(), _node->GetLine());
			break;
		}

		parent = parent->GetParent();
	}

	if(_node->init)
	{
		_node->init->Accept(this);

		CheckAssignment(_node->GetType(), _node->init->GetType(), _node, _node->init);
	}
}

VISIT(TypesDecoratorVisitor, MethodNode)
{
	actualMethod = _node->symbol;
	actualVariableAddress = 0;

	Symbols::table.Set();
	vector<Symbols::Variable*> arguments = dynamic_cast<Symbols::Method*>(_node->symbol)->GetArguments();
	for(auto argument : arguments)
	{
		Symbols::table.Add(argument);
	}

	_node->body->Accept(this);

	Symbols::table.Reset();
}


VISIT(TypesDecoratorVisitor, WriteStatementNode)
{
	_node->expr->Accept(this);

	Types::Type* t = _node->expr->GetType();
	
	if(!Types::Type::IsPrimitive(*t) && !Types::Type::IsString(*t))
	{
		ErrorHandler::SemanticError("Type " + t->Name() + " can not be written", _node->GetLine());
	}
}

VISIT(TypesDecoratorVisitor, ReadStatementNode)
{
	_node->slot->Accept(this);

	if(!dynamic_cast<AST::SlotNode*>(_node->slot)->isLeftValue)
	{
		ErrorHandler::SemanticError("Can not read into somethig that is not an l-value", _node->GetLine());
	}

	Types::Type* t = _node->slot->GetType();

	if(!Types::Type::IsPrimitive(*t) && !Types::Type::IsString(*t))
	{
		ErrorHandler::SemanticError("Type " + t->Name() + " can not be read", _node->GetLine());
	}
}

VISIT(TypesDecoratorVisitor, BlockStatementNode)
{
	Symbols::table.Set();

	COLLECTION_ACCEPT(_node->statements);

	Symbols::table.Reset();
}

VISIT(TypesDecoratorVisitor, IfElseStatementNode)
{
	_node->condition->Accept(this);

	Types::Type* t = _node->condition->GetType();
	if(!Types::Type::IsBool(*t))
	{
		ErrorHandler::SemanticError("If condition has type different than bool (" + t->Name() + ") in method " +  actualMethod->Name() + " of class  " + actualClass->Name(), _node->GetLine());
	}

	_node->ifBody->Accept(this);

	if(_node->elseBody)
		_node->elseBody->Accept(this);
}

VISIT(TypesDecoratorVisitor, WhileStatementNode)
{
	_node->condition->Accept(this);

	Types::Type* t = _node->condition->GetType();
	if(!Types::Type::IsBool(*t))
	{
		ErrorHandler::SemanticError("While condition has type different than bool (" + t->Name() + ") in method " +  actualMethod->Name() + " of class  " + actualClass->Name(), _node->GetLine());
	}

	_node->body->Accept(this);
}

VISIT(TypesDecoratorVisitor, ForStatementNode)
{
	if(_node->init)
		_node->init->Accept(this);

	if(_node->condition)
	{
		_node->condition->Accept(this);

		Types::Type* t = _node->condition->GetType();
		if(!Types::Type::IsBool(*t))
		{
			ErrorHandler::SemanticError("For condition has type different than bool (" + t->Name() + ") in method " +  actualMethod->Name() + " of class  " + actualClass->Name(), _node->GetLine());
		}
	}

	if(_node->update)
		_node->update->Accept(this);

	_node->body->Accept(this);
}

VISIT(TypesDecoratorVisitor, VariableNode)
{
	Types::Type* t = Types::table[_node->type];
	if(!t)
	{
		ErrorHandler::SemanticError("Type " + _node->type + " has not been defined", _node->GetLine());
		return;
	}
	else if(Types::Type::IsVoid(*t))
	{
		ErrorHandler::SemanticError("Variable type cannot be void", _node->GetLine());
		return;
	}

	if(Types::table[_node->name])
	{
		ErrorHandler::SemanticError("Variable name " + _node->name + " can not be the same as a type name", _node->GetLine());
	}

	_node->SetType(t);
	
	if(_node->init)
	{
		_node->init->Accept(this);

		CheckAssignment(_node->GetType(), _node->init->GetType(), _node, _node->init);
	}
	else
	{
		ErrorHandler::Warning("Local variable " + _node->name + " is not initialized", _node->GetLine());
	}

	Symbols::Symbol* v = Symbols::table.SearchLastContextOnly(_node->name);
	if(v)
	{
		ErrorHandler::SemanticError("Variable " + _node->name + " has already been defined as " + v->Type()->Name(), _node->GetLine());
	}

	_node->symbol = new Symbols::Variable(_node->name, t, false);
	_node->symbol->SetAddress(actualVariableAddress++);
	Symbols::table.Add(_node->symbol);
}


VISIT(TypesDecoratorVisitor, NullExprNode)
{
	_node->SetType(Types::table["null"]);
}

VISIT(TypesDecoratorVisitor, BoolCteExprNode)
{
	_node->SetType(Types::table["bool"]);
}

VISIT(TypesDecoratorVisitor, CharCteExprNode)
{
	_node->SetType(Types::table["char"]);
}

VISIT(TypesDecoratorVisitor, IntCteExprNode)
{
	_node->SetType(Types::table["int"]);
}

VISIT(TypesDecoratorVisitor, RealCteExprNode)
{
	_node->SetType(Types::table["real"]);
}

VISIT(TypesDecoratorVisitor, StringCteExprNode)
{
	_node->SetType(Types::table["string"]);
}

VISIT(TypesDecoratorVisitor, GreaterExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckRelationalExpresion(_node);
}

VISIT(TypesDecoratorVisitor, LesserExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckRelationalExpresion(_node);
}

VISIT(TypesDecoratorVisitor, EqualExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckEqualityExpresion(_node);
}

VISIT(TypesDecoratorVisitor, NotEqualExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckEqualityExpresion(_node);
}

VISIT(TypesDecoratorVisitor, AndExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckBooleanExpresion(_node);
}

VISIT(TypesDecoratorVisitor, OrExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckBooleanExpresion(_node);
}

VISIT(TypesDecoratorVisitor, PlusExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckAritmethicalExpresion(_node);
}

VISIT(TypesDecoratorVisitor, MinusExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckAritmethicalExpresion(_node);
}

VISIT(TypesDecoratorVisitor, MulExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckAritmethicalExpresion(_node);
}

VISIT(TypesDecoratorVisitor, DivExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckAritmethicalExpresion(_node);
}

VISIT(TypesDecoratorVisitor, AssignmentExprNode)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);

	CheckAssignment(_node->leftExpr->GetType(), _node->rightExpr->GetType(), _node, _node->rightExpr);
	
	if(!dynamic_cast<AST::SlotNode*>(_node->leftExpr)->isLeftValue)
	{
		ErrorHandler::SemanticError("Cannot assign to a non l-value", _node->GetLine());
	}

	_node->SetType(_node->leftExpr->GetType());
}

VISIT(TypesDecoratorVisitor, NotExprNode)
{
	_node->expr->Accept(this);
	
	Types::Type* t = _node->expr->GetType();
	if(!Types::Type::IsBool(*t))
	{
		ErrorHandler::SemanticError("Type " + t->Name() + " cannot be applied operator not", _node->GetLine());
	}

	_node->SetType(Types::table["bool"]);
}

VISIT(TypesDecoratorVisitor, MinusUnaryExprNode)
{
	_node->expr->Accept(this);

	Types::Type* t = _node->expr->GetType();
	if(!Types::Type::IsNumeric(*t))
	{
		ErrorHandler::SemanticError("Type " + t->Name() + " cannot be applied unary minus operator", _node->GetLine());
	}

	_node->SetType(t);
}

VISIT(TypesDecoratorVisitor, CastExprNode)
{
	_node->expr->Accept(this);

	Types::Type* castType = Types::table[_node->type];
	Types::Type* nodeType = _node->expr->GetType();

	_node->SetType(nodeType);

	if(!castType)
	{
		ErrorHandler::SemanticError("Type " + _node->type + " has not been defined", _node->GetLine());
		return;	
	}
	else if(Types::Type::IsVoid(*castType))
	{
		ErrorHandler::SemanticError("Type cast cannot be void", _node->GetLine());
		return;
	}

	if(!nodeType->ImplicitCastTo(*castType) && !nodeType->ExplicitCastTo(*castType))
	{
		ErrorHandler::SemanticError("Cannot convert type " + nodeType->Name() + " to type " + castType->Name(), _node->GetLine());
		return;
	}

	ErrorHandler::Warning("Cast from " + nodeType->Name() + " to " + castType->Name(), _node->GetLine());
	
	_node->SetType(castType);
}

VISIT(TypesDecoratorVisitor, NewExprNode)
{
	Types::Type* t = Types::table[_node->type];
	if(!t)
	{
		ErrorHandler::SemanticError("Type " + _node->type + " has not been defined", _node->GetLine());
		return;
	}
	else if(!Types::Type::IsClass(*t))
	{
		ErrorHandler::SemanticError("Type " + _node->type + " is not a class", _node->GetLine());
		return;
	}
	else if(Types::Type::IsInterface(*t))
	{
		ErrorHandler::SemanticError("Type " + _node->type + " is an interface and cannot be instantiated", _node->GetLine());
		return;
	}

	Types::Class* classType = dynamic_cast<Types::Class*>(t);

	COLLECTION_ACCEPT(_node->exprs);

	Types::Method*           constructorType = CreateMethodType(_node->exprs);
	vector<Symbols::Method*> constructors    = classType->GetMethod(classType->Name());

	Symbols::Method* constructorCall = nullptr;
	if(!FindMethod(constructorType, constructors, constructorCall))
	{
		ErrorHandler::SemanticError("Incorrect constructor call to " + _node->type + ". Call was made with " + constructorType->Name(), _node->GetLine());
	}
	else
	{
		CastMethodCall(dynamic_cast<Types::Method*>(constructorCall->Type()), _node->exprs, _node, _node->GetLine());
	}
	
	_node->SetType(t);
}

VISIT(TypesDecoratorVisitor, NewArrayExprNode)
{
	Types::Type* t = Types::table[_node->type];
	if(!t)
	{
		ErrorHandler::SemanticError("Type " + _node->type + " has not been defined", _node->GetLine());
		return;
	}
	else if(!Types::Type::IsPrimitive(*t) && !Types::Type::IsString(*t) && !Types::Type::IsAggregate(*t))
	{
		ErrorHandler::SemanticError("Type " + _node->type + " cannot be used as array base", _node->GetLine());
		return;
	}

	COLLECTION_ACCEPT(_node->exprs);

	for(auto expr : _node->exprs)
	{
		Types::Type* t = expr->GetType();

		if(!Types::Type::IsInt(*t) && !t->ImplicitCastTo(*Types::table["int"]))
		{
			ErrorHandler::SemanticError("Type " + t->Name() + " is not an integral type and cannot be used as array declarator", _node->GetLine());
		}
	}

	_node->SetType(Types::table[to_string(_node->exprs.size()) + _node->type]);
}

VISIT(TypesDecoratorVisitor, SlotNode)
{
	SlotContextSet();
	accessMustBeStatic = actualMethod->IsStatic();

	COLLECTION_ACCEPT(_node->exprs);

	if(SlotContextError())
	{
		SlotContextReset();
		return;
	}

	AST::Node* last = _node->exprs[_node->exprs.size() - 1];
	_node->SetType(last->GetType());

	//
	// Left value calculation
	//
	_node->isLeftValue = false;
	IdentifierSlotNode* n = dynamic_cast<IdentifierSlotNode*>(last);
	if(n)
	{
		//
		// Visitation went well, so it is a leftValue
		// if there was no method call or if there were indexes
		//
		_node->isLeftValue = !n->methodInvocation || !n->indexes.empty();
	}
	
	SlotContextReset();
}

VISIT(TypesDecoratorVisitor, ThisSlotNode)
{
	if(actualMethod->IsStatic())
	{
		ErrorHandler::SemanticError("This can not be used in an static method: " + actualClass->Name() + "::"+actualMethod->Name(), _node->GetLine());
	}

	_node->SetType(actualClass);

	SlotContextPush(_node->GetType());
}

VISIT(TypesDecoratorVisitor, IdentifierSlotNode)
{
	if(SlotContextError())
		return;

	//
	// Class Name
	//
	Types::Type* t = Types::table[_node->identifier];
	if(t)
	{
		if(!SlotContextEmpty())
		{
			ErrorHandler::SemanticError("Type identifier " + _node->identifier + " is not at root of slot expression", _node->GetLine());
			SlotContextSetError();
			return;
		}

		if(!dynamic_cast<Types::Class*>(t))
		{
			ErrorHandler::SemanticError("Type identifier " + _node->identifier + " is not a class", _node->GetLine());
			SlotContextSetError();
			return;
		}

		if(_node->methodInvocation)
		{
			ErrorHandler::SemanticError("Type identifier " + _node->identifier + " cannot be called", _node->GetLine());
			SlotContextSetError();
			return;
		}

		if(_node->indexes.size())
		{
			ErrorHandler::SemanticError("Type identifier " + _node->identifier + " cannot be indexed", _node->GetLine());
			SlotContextSetError();
			return;
		}

		_node->SetType(t);
		SlotContextPush(_node->GetType());
		accessMustBeStatic = true;
		return;
	}

	//
	// Local Variable
	//
	Symbols::Symbol* s = 0;
	bool             localSymbol = true;

	if(SlotContextEmpty() && Symbols::table[_node->identifier])
	{
		if(_node->methodInvocation)
		{
			ErrorHandler::SemanticError("Variable " + _node->identifier + " cannot be called", _node->GetLine());
			SlotContextSetError();
			return;
		}

		s = Symbols::table[_node->identifier];
	}
	//
	// Class Member
	//
	else
	{
		//
		// If there was not previous type, it is enclosing class
		//
		if(SlotContextEmpty())
		{
			SlotContextPush(actualClass);
		}

		//
		// Check if it is an attribute or method
		//
		Types::Class* c = dynamic_cast<Types::Class*>(SlotContextLastType());
	
		if(!c)
		{
			ErrorHandler::SemanticError("Type " + SlotContextLastType()->Name() + " cannot be dereferenced", _node->GetLine());
			SlotContextSetError();
			return;
		}

		if(_node->methodInvocation)
		{
			COLLECTION_ACCEPT(_node->arguments);

			//
			// Method
			//
			Types::Method* methodType = CreateMethodType(_node->arguments);
			Symbols::Method* m = 0;
			Types::Class* p = c;
			while(p && !m)
			{
				vector<Symbols::Method*> v = p->GetMethod(_node->identifier);
				FindMethod(methodType, v, m);
				if(m)
				{
					CastMethodCall(dynamic_cast<Types::Method*>(m->Type()), _node->arguments, _node, _node->GetLine());
					break;
				}
				localSymbol = false;
				p = p->GetParent();
			}
			s = m;
		}
		else
		{
			//
			// Attribute
			//
			Types::Class* p = c;
			while(p && !s)
			{
				s = p->GetAttribute(_node->identifier);
				if(s)
				{
					break;
				}
				localSymbol = false;
				p = p->GetParent();
			}
		}
	}

	//
	// No symbol found
	//
	if(!s)
	{
		if(_node->methodInvocation)
		{
			ErrorHandler::SemanticError("Unknown indentifier " + _node->identifier + " or invalid parameters in call when parsing " + actualClass->Name()+"::" + actualMethod->Name(), _node->GetLine());
		}
		else
		{
			ErrorHandler::SemanticError("Unknown indentifier " + _node->identifier + " when parsing " + actualClass->Name()+"::" + actualMethod->Name(), _node->GetLine());
		}
		SlotContextSetError();
		return;
	}

	//
	// If it was a member, perform additional checks
	//
	Symbols::Member* m = dynamic_cast<Symbols::Member*>(s);
	if(m)
	{
		if(accessMustBeStatic && !m->IsStatic())
		{
			ErrorHandler::SemanticError("Member " + SlotContextLastType()->Name() + "::" + s->Name() + " is not static", _node->GetLine());
		}

		//
		// Different class
		//
		if(*SlotContextLastType() != *actualClass)
		{
			if(m->GetAccess() != Symbols::Access::Public)
			{
				ErrorHandler::SemanticError("Member " + SlotContextLastType()->Name() + "::" + s->Name() + " has not public access", _node->GetLine());
			}
		}
		//
		// Same class
		//
		else
		{
			if(!localSymbol && m->GetAccess() == Symbols::Access::Private)
			{
				ErrorHandler::SemanticError("Member " + SlotContextLastType()->Name() + "::" + s->Name() + " belongs to an ancestor and has private access", _node->GetLine());
			}
		}
	}

	//
	// Calculate final type
	//
	Types::Type* finalType = s->Type();
	if(_node->methodInvocation)
	{
		finalType = dynamic_cast<Types::Method*>(s->Type())->GetReturnType();
	}

	//
	// Check indexes
	//
	if(!_node->indexes.empty())
	{
		if(!Types::Type::IsArray(*finalType))
		{
			ErrorHandler::SemanticError(finalType->Name() + " of expression in " + _node->identifier + " is not an array so it can not be indexed", _node->GetLine());		
			SlotContextSetError();
			return;
		}

		COLLECTION_ACCEPT(_node->indexes);

		for(auto n : _node->indexes)
		{
			Types::Type* t = n->GetType();

			if(!Types::Type::IsInt(*t) && !t->ImplicitCastTo(*Types::table["int"]))
			{
				ErrorHandler::SemanticError("Index type " + t->Name() + " is not an integral type", _node->GetLine());
			}
		}

		Types::Array* a = dynamic_cast<Types::Array*>(finalType);

		if(a->GetDimensions() > _node->indexes.size())
		{
			string typeName = to_string(a->GetDimensions() - _node->indexes.size()) + a->GetBaseType()->Name();

			Types::Type* t = Types::table[typeName];

			finalType = t;
		}
		else if(a->GetDimensions() == _node->indexes.size())
		{
			finalType = a->GetBaseType();
		}
		else
		{
			ErrorHandler::SemanticError(_node->identifier + " is not an array so it can not be indexed", _node->GetLine());
			SlotContextSetError();
			return;
		}
	}
	
	accessMustBeStatic = false;
	_node->SetType(finalType);
	SlotContextPush(_node->GetType());
	_node->symbol = s;
}
