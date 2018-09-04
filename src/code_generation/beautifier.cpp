#include "beautifier.h"

#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>

using namespace CodeGeneration;

void Beautifier::FeedLine()
{
	for(int i = 0; i < anidation; i++)
		file << "    ";
}

void Beautifier::Write(string _info, bool _feedLine)
{
	if(_feedLine)
		FeedLine();
	file << _info;
}

void Beautifier::WriteLn(string _info, bool _feedLine)
{
	Write(_info, _feedLine);
	file << endl;
}

string Beautifier::Access(Symbols::Access _access)
{
	switch(_access)
	{
		case Symbols::Access::Public    : return "public";
		case Symbols::Access::Protected : return "protected";
		case Symbols::Access::Private   : return "private";
	}
	return "";
}

void Beautifier::StringList(vector<string>& _list)
{
	size_t n = _list.size();

	if(n)
	{
		for(size_t i = 0; i < n - 1; ++i)
		{
			Write(_list[i]);
			Write(", ");
		}

		Write(_list[n - 1]);
	}
}

void Beautifier::MixedStringList(vector<string>& _list1, vector<string>& _list2)
{
	size_t n = _list1.size();
	
	if(n)
	{
		for(size_t i = 0; i < n - 1; ++i)
		{
			Write(_list1[i]);
			Write(" ");
			Write(_list2[i]);
			Write(", ");
		}

		Write(_list1[n - 1]);
		Write(" ");
		Write(_list2[n - 1]);
	}
}

void Beautifier::CallList(AST::Collection& _call)
{
	size_t n = _call.size();

	if(n)
	{
		for(size_t i = 0; i < n - 1; ++i)
		{
			_call[i]->Accept(this);
			Write(", ");
		}
		_call[n - 1]->Accept(this);
	}
}

void Beautifier::InitList(vector<string>& _names, vector<AST::Collection>& _calls)
{
	size_t n = _names.size();

	if(n)
	{
		for(size_t i = 0; i < n - 1; ++i)
		{
			Write(_names[i]);
			Write("(");
			CallList(_calls[i]);
			Write("), ");
		}

		Write(_names[n - 1]);
		Write("(");
		CallList(_calls[n - 1]);
		Write(")");
	}
}

Beautifier::Beautifier(const string& _fileName)
	: anidation(0)
{
	file.open(_fileName);
}

Beautifier::~Beautifier()
{
	file.close();
}

VISIT(Beautifier, AST::ProgramNode)
{
	COLLECTION_ACCEPT(_node->classes);
}

VISIT(Beautifier, AST::InterfaceNode)
{
	Write("interface ", true);
	WriteLn(_node->name);
	WriteLn("{", true);
	anidation++;
	COLLECTION_ACCEPT(_node->members);
	anidation--;
	WriteLn("}", true);
	WriteLn("");
}

VISIT(Beautifier, AST::PrototypeNode)
{
	Write(_node->returnType, true);
	Write(" ");
	Write(_node->name);
	Write("(");
	StringList(_node->argumentTypes);
	Write(")");
	WriteLn(";");
	WriteLn("");
}

VISIT(Beautifier, AST::ClassNode)
{
	Write("class ", true);
	Write(_node->name);
	if(_node->parent != "")
	{
		Write(" extends ");
		Write(_node->parent);
	}
	if(_node->interfaces.size())
	{
		Write(" implements ");
		StringList(_node->interfaces);
	}
	WriteLn("");
	WriteLn("{", true);
	anidation++;
	COLLECTION_ACCEPT(_node->members);
	anidation--;
	WriteLn("}", true);
	WriteLn("");
}

VISIT(Beautifier, AST::AttributeNode)
{
	if(_node->isStatic)
	{
		Write("static ", true);
	}
	Write(Access(_node->access), !_node->isStatic);
	Write(" ");
	Write(_node->type);
	Write(" ");
	Write(_node->name);
	if(_node->init)
	{
		Write(" = ");
		_node->init->Accept(this);
	}
	WriteLn(";");
	WriteLn("");
}

VISIT(Beautifier, AST::MethodNode)
{
	if(_node->isStatic)
	{
		Write("static ", true);
	}
	Write(Access(_node->access), !_node->isStatic);
	if(_node->name != dynamic_cast<AST::ClassNode*>(_node->GetParent())->name)
	{
		Write(" ");
		Write(_node->returnType);
	}
	Write(" ");
	Write(_node->name);
	Write("(");
	MixedStringList(_node->argumentTypes, _node->argumentNames);
	Write(")");
	WriteLn("");
	_node->body->Accept(this);
	WriteLn("");
}

VISIT(Beautifier, AST::EmptyStatementNode)
{
	WriteLn(";");
}

VISIT(Beautifier, AST::WriteStatementNode)
{
	Write("write ", true);
	_node->expr->Accept(this);
	WriteLn(";");
}

VISIT(Beautifier, AST::ReadStatementNode)
{
	Write("read ", true);
	_node->slot->Accept(this);
	WriteLn(";");
}

VISIT(Beautifier, AST::BlockStatementNode)
{
	WriteLn("{", true);
	anidation++;
	COLLECTION_ACCEPT(_node->statements);
	anidation--;
	WriteLn("}", true);
}

VISIT(Beautifier, AST::IfElseStatementNode)
{
	Write("if (", true);
	_node->condition->Accept(this);
	WriteLn(")");
	_node->ifBody->Accept(this);
	if(_node->elseBody)
	{
		WriteLn("else", true);
		_node->elseBody->Accept(this);
	}
}

VISIT(Beautifier, AST::WhileStatementNode)
{
	Write("while (", true);
	_node->condition->Accept(this);
	WriteLn(")");
	_node->body->Accept(this);
}

VISIT(Beautifier, AST::ForStatementNode)
{
	Write("for (", true);
	if(_node->init)
		_node->init->Accept(this);
	Write("; ");
	if(_node->condition)
		_node->condition->Accept(this);
	Write("; ");
	if(_node->update)
		_node->update->Accept(this);
	WriteLn(")");
	_node->body->Accept(this);
}

VISIT(Beautifier, AST::ReturnStatementNode)
{
	Write("return", true);
	if(_node->expr)
	{
		Write(" ");
		_node->expr->Accept(this);
	}
	WriteLn(";");
}

VISIT(Beautifier, AST::VariableBlockNode)
{
	COLLECTION_ACCEPT(_node->variables);
}

VISIT(Beautifier, AST::VariableNode)
{
	Write(_node->type, true);
	Write(" ");
	Write(_node->name);
	if(_node->init)
	{
		Write(" = ");
		_node->init->Accept(this);
	}
	WriteLn(";");
}

VISIT(Beautifier, AST::ExpressionStatementNode)
{
	Write("", true);
	_node->expr->Accept(this);
	WriteLn(";");
}

VISIT(Beautifier, AST::NullExprNode)
{
	Write("null");
}

VISIT(Beautifier, AST::BoolCteExprNode)
{
	if(_node->value)
		Write("true");
	else
		Write("false");
}

VISIT(Beautifier, AST::CharCteExprNode)
{
	Write(to_string(_node->value));
}

VISIT(Beautifier, AST::IntCteExprNode)
{
	Write(to_string(_node->value));
}

VISIT(Beautifier, AST::RealCteExprNode)
{
	Write(to_string(_node->value));
}

VISIT(Beautifier, AST::StringCteExprNode)
{
	Write("\"");
	Write(_node->value);
	Write("\"");
}

VISIT(Beautifier, AST::GreaterExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" > ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::LesserExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" < ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::EqualExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" == ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::NotEqualExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" != ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::AndExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" && ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::OrExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" || ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::PlusExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" + ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::MinusExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" - ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::MulExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" * ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::DivExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" / ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::AssignmentExprNode)
{
	_node->leftExpr->Accept(this);
	Write(" = ");
	_node->rightExpr->Accept(this);
}

VISIT(Beautifier, AST::NotExprNode)
{
	Write("!");
	_node->expr->Accept(this);
}

VISIT(Beautifier, AST::MinusUnaryExprNode)
{
	Write("-");
	_node->expr->Accept(this);
}

VISIT(Beautifier, AST::CastExprNode)
{
	Write("cast<");
	Write(_node->type);
	Write(">(");
	_node->expr->Accept(this);
	Write(")");
}

VISIT(Beautifier, AST::NewExprNode)
{
	Write("new ");
	Write(_node->type);
	Write("(");
	CallList(_node->exprs);
	Write(")");
}

VISIT(Beautifier, AST::NewArrayExprNode)
{
	Write("new ");
	Write(_node->type);
	for(auto e : _node->exprs)
	{
		Write("[");
		e->Accept(this);
		Write("]");
	}
}

VISIT(Beautifier, AST::SlotNode)
{
	//COLLECTION_ACCEPT(_node->exprs);

	size_t n = _node->exprs.size();

	if(n)
	{
		for(size_t i = 0; i < n - 1; ++i)
		{
			_node->exprs[i]->Accept(this);
			Write(".");
		}
		_node->exprs[n - 1]->Accept(this);
	}
}

VISIT(Beautifier, AST::ThisSlotNode)
{
	Write("this");
}

VISIT(Beautifier, AST::IdentifierSlotNode)
{
	Write(_node->identifier);
	if(_node->methodInvocation)
	{
		Write("(");
		CallList(_node->arguments);
		Write(")");
	}
	for(auto e : _node->indexes)
	{
		Write("[");
		e->Accept(this);
		Write("]");
	}
}
