#include "il_generator.h"
#include "method_variables_visitor.h"

#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>

#include <compiler.h>

using namespace CodeGeneration;
using namespace AST;

bool ILGenerator::IsMain(AST::MethodNode* _node)
{
	Symbols::Method* s = dynamic_cast<Symbols::Method*>(_node->symbol);
	Types::Method*   t = dynamic_cast<Types::Method*>(s->Type());

	if( s->IsStatic()                               && 
		s->GetAccess() == Symbols::Access::Public   &&
		Types::Type::IsVoid(*t->GetReturnType())    && 
	   (s->Name() == "main" || s->Name() == "Main") &&
	    t->GetArguments().size() == 1               &&
	    t->GetArguments()[0]->Name() == "1string"	   
	)
	{
		return true;
	}

	return false;
}

string ILGenerator::AccessName(Symbols::Access _access)
{
	switch(_access)
	{
		case Symbols::Access::Public    : return "public";
		case Symbols::Access::Protected : return "protected";
		case Symbols::Access::Private   : return "private";
	}
	return "";
}

string ILGenerator::CTSTypeName(Types::Type* t)
{
	if(Types::Type::IsVoid(*t))
	{
		return "[mscorlib]System.Void";
	}
	if(Types::Type::IsBool(*t))
	{
		return "[mscorlib]System.Boolean";
	}
	if(Types::Type::IsChar(*t))
	{
		return "[mscorlib]System.Char";
	}
	if(Types::Type::IsInt(*t))
	{
		return "[mscorlib]System.Int32";
	}
	if(Types::Type::IsReal(*t))
	{
		return "[mscorlib]System.Double";
	}
	if(Types::Type::IsString(*t))
	{
		return "[mscorlib]System.String";
	}
	if(Types::Type::IsArray(*t))
	{
		Types::Array* a = dynamic_cast<Types::Array*>(t);
		return CTSTypeName(a->GetBaseType()) + Types::Array::Brackets(a->GetDimensions());
	}
	if(Types::Type::IsClass(*t))
	{
		return t->Name();
	}

	//throw exception;
	return t->Name();
}

string ILGenerator::CTSTypeName(string _type)
{
	return CTSTypeName(Types::table[_type]);
}

string ILGenerator::CTSTypeName(AST::Node* _node)
{
	return CTSTypeName(_node->GetType());
}

string ILGenerator::ILTypeName(Types::Type* t)
{
	if(Types::Type::IsVoid(*t))
	{
		return "void";
	}
	if(Types::Type::IsBool(*t))
	{
		return "bool";
	}
	if(Types::Type::IsChar(*t))
	{
		return "char";
	}
	if(Types::Type::IsInt(*t))
	{
		return "int32";
	}
	if(Types::Type::IsReal(*t))
	{
		return "float64";
	}
	if(Types::Type::IsString(*t))
	{
		return "string";
	}
	if(Types::Type::IsArray(*t))
	{
		Types::Array* a = dynamic_cast<Types::Array*>(t);
		return ILTypeName(a->GetBaseType()) + Types::Array::Brackets(a->GetDimensions());
	}
	if(Types::Type::IsClass(*t))
	{
		//return "class " + Compiler::Assembly() + "." + t-Name();
		return "class " + t->Name();
	}
	//throw exception;
	return t->Name();
}

string ILGenerator::ILTypeName(string _type)
{
	return ILTypeName(Types::table[_type]);
}

string ILGenerator::ILTypeName(AST::Node* _node)
{
	return ILTypeName(_node->GetType());
}

string ILGenerator::Arguments(AST::MethodNode* _method)
{
	string arguments = "";

	if(!_method->argumentTypes.empty())
	{
		for(size_t i = 0; i < _method->argumentTypes.size(); ++i)
		{
			string type = _method->argumentTypes[i];
			string name = _method->argumentNames[i];
			arguments += ILTypeName(type) + " " + name;

			if (i != _method->argumentTypes.size() - 1)
			{
				arguments += ", ";
			}
		}
	}

	return arguments;
}

string ILGenerator::Arguments(AST::Collection const& _call)
{
	string arguments = "";

	if(!_call.empty())
	{
		for(size_t i = 0; i < _call.size(); ++i)
		{
			arguments += ILTypeName(_call[i]);

			if(i != _call.size() - 1)
			{
				arguments += ", ";
			}
		}
	}

	return arguments;
}

string ILGenerator::Anidate(int _anidation)
{
	string result = "";
	for(int i = 0; i < anidation; i++)
		result += "\t";
	return result;
}

void ILGenerator::Write(string _line)
{
	file << Anidate(anidation) << _line;
}

void ILGenerator::WriteLn(string _line)
{
	Write(_line);
	file << endl;
}

string ILGenerator::Locals(int _anidation, string _returnType, AST::Node* _block)
{
	MethodVariablesVisitor mvv(_anidation, _returnType);
	_block->Accept(&mvv);

	string locals = "";
	
	if(mvv.HasVariables())
	{
		locals += ".locals init\n";
		locals += Anidate(anidation) + "(\n";
		locals += Anidate(anidation) + mvv.Line()+")";
	}

	lastReturnAddress = mvv.ReturnAddress();
	
	return locals;
}

string ILGenerator::Return(string _returnType, int _address)
{
	string returnLabel = string("RET") + to_string(retLabels++) + ":" + "\n";

	if(_returnType != "void")
	{
		returnLabel += Anidate(anidation) + "ldloc " + to_string(_address)+"\n";
	}

	returnLabel += Anidate(anidation) + "ret";

	return returnLabel;
}

void ILGenerator::Label(string _label)
{
	file << _label << ":" << endl;
}

void ILGenerator::GenerateStore(AST::SlotNode* _node)
{
	AST::IdentifierSlotNode* id = dynamic_cast<AST::IdentifierSlotNode*>(*_node->exprs.rbegin());

	if(!id->indexes.empty())
	{
		Types::Type* t = _node->GetType();

		if(Types::Type::IsPrimitive(*t) && !Types::Type::IsReal(*t))
		{
			WriteLn("stelem.i4");
		}
		else if(Types::Type::IsReal(*t))
		{
			WriteLn("stelem.r8");
		}
		else
		{
			WriteLn("stelem.ref");
		}
	}
	else if(dynamic_cast<Symbols::Variable*>(id->symbol))
	{
		Symbols::Variable* v = dynamic_cast<Symbols::Variable*>(id->symbol);

		string accessor = v->IsArgument() ? "starg" : "stloc";

		if(v->GetAddress() < 4)
		{
			WriteLn(accessor + "." + to_string(v->GetAddress()));
		}
		else
		{
			WriteLn(accessor + " " + v->Name());
		}
	}
	else if(dynamic_cast<Symbols::Attribute*>(id->symbol))
	{
		Symbols::Attribute* a = dynamic_cast<Symbols::Attribute*>(id->symbol);
		
		WriteLn((a->IsStatic() ? "stsfld " : "stfld ") + ILTypeName(a->Type()) + " " + 
		        ILTypeName(a->GetParent()) + "::" + a->Name());
	}
}

ILGenerator::ILGenerator(string _fileName)
	: module(_fileName)
	, anidation(0)
{
	retLabels = 0;
	labels = 0;
	lastReturnAddress = 0;
	actualClass = 0;

	if(_fileName.find_last_of('/') != string::npos)
	{
		module = _fileName.substr(_fileName.find_last_of('/') + 1);
	}
	file.open(_fileName + ".il");
}

ILGenerator::~ILGenerator()
{
	file.close();
}

VISIT(ILGenerator, ProgramNode)
{
	WriteLn(".assembly extern mscorlib {}");

	WriteLn(".assembly " + module + " {}");
	
	WriteLn(".module " + module + (Compiler::Dll() ? ".dll" : ".exe"));
	
	COLLECTION_ACCEPT(_node->classes);
}


VISIT(ILGenerator, InterfaceNode)
{
	actualClass = dynamic_cast<Types::Class*>(_node->GetType());

	WriteLn(".class interface public abstract auto ansi " + _node->name);
	WriteLn("{");
	
	anidation++;
	COLLECTION_ACCEPT(_node->members);
	anidation--;

	WriteLn("}");
}

VISIT(ILGenerator, PrototypeNode)
{
	WriteLn(".method public hidebysig newslot virtual abstract instance");
	Write("\t" + ILTypeName(_node->returnType) + " " + _node->name + "(");

	if(!_node->argumentTypes.empty())
	{
		for(size_t i = 0; i < _node->argumentTypes.size(); ++i)
		{
			file << ILTypeName(_node->argumentTypes[i]);
			if( i != _node->argumentTypes.size() - 1)
			{
				file << ", ";
			}
		}
	}

	file << ") cil managed {}" << endl;
}


VISIT(ILGenerator, ClassNode)
{
	actualClass = dynamic_cast<Types::Class*>(_node->GetType());

	string extends = actualClass->GetParent() ? actualClass->GetParent()->Name() : "[mscorlib]System.Object";
	WriteLn(string(".class public auto ansi beforefieldinit ") + _node->name + " extends " + extends);

	if(!_node->interfaces.empty())
	{
		Write("\timplements ");
		for(size_t i = 0; i < _node->interfaces.size(); ++i)
		{
			file << ILTypeName(_node->interfaces[i]);
			if(i != _node->interfaces.size() - 1)
			{
				file << ", ";
			} 
		}
	}

	WriteLn("{");

	anidation++;

	WriteLn("//ATTRIBUTES");
	bool hasStaticAttributes = false;
	for(auto n : _node->members)
	{
		AST::AttributeNode* a = dynamic_cast<AST::AttributeNode*>(n);
		if(a)
		{
			if(a->isStatic)
				hasStaticAttributes = true;
			n->Accept(this);
		}
	}

	if(hasStaticAttributes)
	{
		WriteLn(".method private hidebysig specialname rtspecialname static"); 
		WriteLn("\tvoid .cctor() cil managed");
		WriteLn("{");
		anidation++;
		WriteLn(".maxstack 16");
		for(auto n : _node->members)
		{
			AST::AttributeNode* a = dynamic_cast<AST::AttributeNode*>(n);
			if(a)
			{
				if(a->isStatic && a->init)
				{
					Symbols::Attribute* as = actualClass->GetAttribute(a->name);
					a->init->Accept(this);
					WriteLn("stsfld " + ILTypeName(as->Type()) + " " + actualClass->Name() + "::" + as->Name());
				}
			}
		}
		WriteLn("ret");
		anidation--;
		WriteLn("}");
	}

	WriteLn("");
	WriteLn("//METHODS");
	for(auto n : _node->members)
	{
		if(dynamic_cast<AST::MethodNode*>(n))
		{
			n->Accept(this);
		}
	}

	anidation--;
	WriteLn("}");
}

VISIT(ILGenerator, AttributeNode)
{
	WriteLn(".field " + 
		AccessName(_node->access) + " " + 
		(_node->isStatic ? "static " : " ") +
		ILTypeName(_node->type) + " " + 
		_node->name);
}

VISIT(ILGenerator, MethodNode)
{
	string methodName = _node->name;
	string methodAtts = string(" hidebysig ") + (_node->isStatic ? "static" : "virtual instance");

	//
	// Is constructor?
	//
	if(_node->name == actualClass->Name())
	{
		methodName = ".ctor";
		methodAtts = " hidebysig specialname rtspecialname instance";
	}

	Symbols::table.Set();

	for(auto argument : _node->symbol->GetArguments())
	{
		Symbols::table.Add(argument);
	}

	WriteLn(".method " + AccessName(_node->access) + methodAtts);	
	WriteLn("\t" + ILTypeName(_node->returnType) + " " + methodName +
		"(" + Arguments(_node) + ") cil managed");

	WriteLn("{");
	anidation++;
	if(IsMain(_node))
		WriteLn(".entrypoint");
	WriteLn(".maxstack 64");
	WriteLn(Locals(anidation, _node->returnType, _node->body));
	_node->body->Accept(this);
	file << Return(_node->returnType, lastReturnAddress) << endl;
	anidation--;
	WriteLn("}");

	Symbols::table.Reset();
}


VISIT(ILGenerator, WriteStatementNode)
{
	_node->expr->Accept(this);

	WriteLn("call void class [mscorlib]System.Console::Write(" + ILTypeName(_node->expr) + ")");
}

VISIT(ILGenerator, ReadStatementNode)
{
	_node->slot->Accept(this);
	
	WriteLn("call string class [mscorlib]System.Console::ReadLine()");

	Types::Type* t = _node->slot->GetType();
	
	if(Types::Type::IsBool(*t))
	{
		WriteLn("call bool [mscorlib]System.Boolean::Parse(string)");
	}
	else if(Types::Type::IsChar(*t))
	{
		WriteLn("call char [mscorlib]System.Char::Parse(string)");
	}
	else if(Types::Type::IsInt(*t))
	{
		WriteLn("call int32 [mscorlib]System.Int32::Parse(string)");
	}
	if(Types::Type::IsReal(*t))
	{
		WriteLn("call float64 [mscorlib]System.Double::Parse(string)");
	}

	AST::SlotNode* slot = dynamic_cast<AST::SlotNode*>(_node->slot);

	GenerateStore(slot);
}

VISIT(ILGenerator, IfElseStatementNode)
{
	int localLabel = labels++;
	string labelIf   = string("IF")    + to_string(localLabel);
	string labelElse = string("ELSE")  + to_string(localLabel);
	string labelEnd  = string("ENDIF") + to_string(localLabel);
	
	_node->condition->Accept(this);
	if(_node->elseBody)
		WriteLn("brfalse " + labelElse);
	else
		WriteLn("brfalse " + labelEnd);

	Label(labelIf);
	_node->ifBody->Accept(this);
	
	if(_node->elseBody)
	{
		WriteLn("br " + labelEnd);
		Label(labelElse);
		_node->elseBody->Accept(this);
	}

	Label(labelEnd);
}

VISIT(ILGenerator, WhileStatementNode)
{
	int localLabel = labels++;
	string labelCond = string("WHILECOND") + to_string(localLabel);
	string labelBody = string("WHILE")     + to_string(localLabel);

	WriteLn("br " + labelCond);
	Label(labelBody);
	_node->body->Accept(this);
	Label(labelCond);
	_node->condition->Accept(this);
	WriteLn("brtrue " + labelBody);
}

VISIT(ILGenerator, ForStatementNode)
{
	int localLabel = labels++;
	string labelCond = string("FORCOND") + to_string(localLabel);
	string labelBody = string("FOR")     + to_string(localLabel);

	if(_node->init)
		_node->init->Accept(this);
	
	WriteLn("br " + labelCond);
	Label(labelBody);
	_node->body->Accept(this);
	if(_node->update)
		_node->update->Accept(this);
	Label(labelCond);
	_node->condition->Accept(this);
	WriteLn("brtrue " + labelBody);
}

VISIT(ILGenerator, ReturnStatementNode)
{
	string labelRet = string("RET") + to_string(retLabels);

	if(_node->expr)
	{
		_node->expr->Accept(this);
	
		WriteLn("stloc " + to_string(lastReturnAddress));
	}

	WriteLn("br " + labelRet);
}

VISIT(ILGenerator, VariableNode)
{
	if(_node->init)
	{
		_node->init->Accept(this);

		Symbols::Variable* v = _node->symbol;

		string accessor = "stloc";

		if(v->GetAddress() < 4)
		{
			WriteLn(accessor + "." + to_string(v->GetAddress()));
		}
		else
		{
			WriteLn(accessor + " " + v->Name());
		}
	}
}

VISIT(ILGenerator, NullExprNode)
{
	WriteLn("ldnull");
}

VISIT(ILGenerator, BoolCteExprNode)
{
	if(_node->value)
		WriteLn("ldc.i4.1");
	else
		WriteLn("ldc.i4.0");
}

VISIT(ILGenerator, CharCteExprNode)
{
	if(_node->value >= 0 && _node->value <= 8)
		WriteLn("ldc.i4." + to_string(_node->value));
	else
		WriteLn("ldc.i4 " + to_string(_node->value));
}

VISIT(ILGenerator, IntCteExprNode)
{
	if(_node->value == -1)
		WriteLn("ldc.i4.m1");
	else if(_node->value >= 0 && _node->value <= 8)
		WriteLn("ldc.i4." + to_string(_node->value));
	else
		WriteLn("ldc.i4 " + to_string(_node->value));
}

VISIT(ILGenerator, RealCteExprNode)
{
	WriteLn("ldc.r8 " + to_string(_node->value));
}

VISIT(ILGenerator, StringCteExprNode)
{
	WriteLn("ldstr \"" + _node->value + "\"");
}

VISIT(ILGenerator, GreaterExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("cgt");
}

VISIT(ILGenerator, LesserExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("clt");
}

VISIT(ILGenerator, EqualExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("ceq");
}

VISIT(ILGenerator, NotEqualExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("ceq");
	WriteLn("ldc.i4.0");
	WriteLn("ceq");
}

VISIT(ILGenerator, AndExprNode)
{
	string label1 = string("IL_") + to_string(labels++);
	string label2 = string("IL_") + to_string(labels++);

	_node->leftExpr->Accept(this);
	WriteLn("brfalse.s " + label1);
	_node->rightExpr->Accept(this);
	WriteLn("br.s " + label2);
	WriteLn(label1 + ": ldc.i4.0");
	WriteLn(label2 + ":");
}

VISIT(ILGenerator, OrExprNode)
{
	string label1 = string("IL_") + to_string(labels++);
	string label2 = string("IL_") + to_string(labels++);

	_node->leftExpr->Accept(this);
	WriteLn("brtrue.s " + label1);
	_node->rightExpr->Accept(this);
	WriteLn("br.s " + label2);
	WriteLn(label1 + ": ldc.i4.1");
	WriteLn(label2 + ":");
}

VISIT(ILGenerator, PlusExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("add");
}

VISIT(ILGenerator, MinusExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("sub");
}

VISIT(ILGenerator, MulExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("mul");
}

VISIT(ILGenerator, DivExprNode)
{
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);
	WriteLn("div");
}

VISIT(ILGenerator, AssignmentExprNode)
{
	AST::SlotNode* slot = dynamic_cast<AST::SlotNode*>(_node->leftExpr);
	
	_node->leftExpr->Accept(this);
	_node->rightExpr->Accept(this);

	GenerateStore(slot);
}

VISIT(ILGenerator, NotExprNode)
{
	_node->expr->Accept(this);
	WriteLn("ldc.i4.0");
	WriteLn("ceq");
}

VISIT(ILGenerator, MinusUnaryExprNode)
{
	_node->expr->Accept(this);
	WriteLn("neg");
}

VISIT(ILGenerator, CastExprNode)
{
	_node->expr->Accept(this);
	
	Types::Type* t = _node->GetType();
	if(Types::Type::IsChar(*t) || Types::Type::IsInt(*t))
	{
		WriteLn("conv.i4");
	}
	else if(Types::Type::IsReal(*t))
	{
		WriteLn("conv.r8");
	}
	else
	{
		WriteLn("castclass " + ILTypeName(_node->type));
	}
}

VISIT(ILGenerator, NewExprNode)
{
	COLLECTION_ACCEPT(_node->exprs);
	
	WriteLn("newobj instance void " + CTSTypeName(_node->type) +
		"::.ctor(" + Arguments(_node->exprs) + ")");
}

VISIT(ILGenerator, NewArrayExprNode)
{
	_node->exprs[0]->Accept(this);

	WriteLn("newarr " + ILTypeName(_node->type) + Types::Array::Brackets(_node->exprs.size() - 1));
}

VISIT(ILGenerator, IdentifierSlotNode)
{
	if(!_node->symbol)
	{
		//
		// class name
		//
		return;
	}

	bool generateWrite = false;
	
	AST::SlotNode* parent = dynamic_cast<AST::SlotNode*>(_node->GetParent());

	if(dynamic_cast<AST::ReadStatementNode*>(parent->GetParent()))
	{
		generateWrite = true;
	}

	if(dynamic_cast<AST::AssignmentExprNode*>(parent->GetParent()))
	{
		AST::AssignmentExprNode* grandpa = dynamic_cast<AST::AssignmentExprNode*>(parent->GetParent());
		if(grandpa->leftExpr == parent)
			generateWrite = true;
	}

	bool first = false;
	bool last = false;
	for(int i = 0; i < parent->exprs.size(); ++i)
	{
		if(parent->exprs[i] == _node)
		{
			first = (i == 0);
			last  = generateWrite && (i == parent->exprs.size() - 1);
			break;
		}
	}


	if(dynamic_cast<Symbols::Variable*>(_node->symbol))
	{
		Symbols::Variable* v = dynamic_cast<Symbols::Variable*>(_node->symbol);

		if(!last || !_node->indexes.empty())
		{
			string accessor = v->IsArgument() ? "ldarg" : "ldloc";

			if(v->GetAddress() < 4)
			{
				WriteLn(accessor + "." + to_string(v->GetAddress()));
			}
			else
			{
				WriteLn(accessor + " " + v->Name());
			}
		}
	}

	if(dynamic_cast<Symbols::Attribute*>(_node->symbol))
	{
		Symbols::Attribute* a = dynamic_cast<Symbols::Attribute*>(_node->symbol);
		
		//
		// Load "this"
		//
		if(first && !a->IsStatic())
		{
			WriteLn("ldarg.0");
		}

		if(!last || !_node->indexes.empty())
		{
			string accessor = a->IsStatic() ? "ldsfld " : "ldfld ";

			WriteLn(accessor + ILTypeName(a->Type()) + " " + 
		        a->GetParent()->Name() + "::" + a->Name());
		}
	}

	if(dynamic_cast<Symbols::Method*>(_node->symbol))
	{
		Symbols::Method* m = dynamic_cast<Symbols::Method*>(_node->symbol);

		//
		// Load "this"
		//
		if(first && !m->IsStatic())
		{
			WriteLn("ldarg.0");
		}

		COLLECTION_ACCEPT(_node->arguments);

		Types::Method* mt = dynamic_cast<Types::Method*>(m->Type());
	
		string args = "(";
		vector<Types::Type*> arguments = mt->GetArguments();
		for(int i = 0; i < arguments.size(); ++i)
		{
			args += ILTypeName(arguments[i]);
			if(i != arguments.size() - 1)
				args += ", ";
		}
		args += ")";

		WriteLn((m->IsStatic() ? "call " : "callvirt instance ") + 
			ILTypeName(mt->GetReturnType()) + " " + 
			ILTypeName(m->GetParent()) + "::" + m->Name() + args); 
	}

	if(!_node->indexes.empty())
	{
		for(size_t i = 0; i < _node->indexes.size() - 1; ++i)
		{
			_node->indexes[i]->Accept(this);
			WriteLn("ldelem.ref");
		}
		_node->indexes[_node->indexes.size() - 1]->Accept(this);
	
		if(!last)
		{
			Types::Type* t = _node->GetType();

			if(Types::Type::IsPrimitive(*t) && !Types::Type::IsReal(*t))
			{
				WriteLn("ldelem.i4");
			}
			else if(Types::Type::IsReal(*t))
			{
				WriteLn("ldelem.r8");
			}
			else
			{
				WriteLn("ldelem.ref");
			}
		}
	}
}
