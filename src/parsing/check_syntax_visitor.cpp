#include "check_syntax_visitor.h"

#include <errors/handler.h>

#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>

#define IS(Type, Node) true//(dynamic_cast<Type*>(Node))
#define BAD_NODE(X)    (string("Incorrect son node type in ") + string(#X))

#define CHECK_PARENT(P, N)     \
	if(N->GetParent() != P)    \
	{						   \
		ErrorHandler::Fatal(); \
	}

using namespace Parsing;
using namespace AST;

VISIT(CheckSyntaxVisitor, ProgramNode)
{
	for(auto node : _node->classes)
	{
		if(!IS(ClassNode, node) && 
		   !IS(InterfaceNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(ProgramNode), node->GetLine());
		}
		
		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, InterfaceNode)
{
	for(auto node : _node->members)
	{
		if(!IS(PrototypeNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(InterfaceNode), node->GetLine());
		}
		
		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, PrototypeNode)
{
}

VISIT(CheckSyntaxVisitor, ClassNode)
{
	for(auto node : _node->members)
	{
		if(!IS(AttributeNode, node) && 
		   !IS(ConstructorNode, node) && 
		   !IS(MethodNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(ClassNode), node->GetLine());
		}
		
		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, AttributeNode)
{
	if(_node->init)
	{
		if(!IS(ExpressionNode, _node->init))
		{
			ErrorHandler::SyntaxError(BAD_NODE(AttributeNode), _node->init->GetLine());
		}

		//_node->init->SetParent(_node);
		CHECK_PARENT(_node, _node->init);

        _node->init->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, MethodNode)
{
	/*
	if(_node->argumentTypes.size() != _node->argumentNames.size())
	{
		ErrorHandler::SyntaxError("Different sizes between types and names in method " + _node->name, _node->GetLineNumber());
	}
	*/

	if(!IS(BlockStatementNode, _node->body))
	{
		ErrorHandler::SyntaxError(BAD_NODE(MethodNode), _node->body->GetLine());
	}

	//_node->body->SetParent(_node);
	CHECK_PARENT(_node, _node->body);

	_node->body->Accept(this);
}

VISIT(CheckSyntaxVisitor, EmptyStatementNode)
{
}

VISIT(CheckSyntaxVisitor, WriteStatementNode)
{
	if(!IS(ExpressionNode, _node->expr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(WriteStatementNode), _node->expr->GetLine());
	}

	//_node->expr->SetParent(_node);
	CHECK_PARENT(_node, _node->expr);

	_node->expr->Accept(this);
}

VISIT(CheckSyntaxVisitor, ReadStatementNode)
{
	if(!IS(SlotNode, _node->slot))
	{
		ErrorHandler::SyntaxError(BAD_NODE(ReadStatementNode), _node->slot->GetLine());
	}

	//_node->slot->SetParent(_node);
	CHECK_PARENT(_node, _node->slot);

	_node->slot->Accept(this);
}

VISIT(CheckSyntaxVisitor, BlockStatementNode)
{
	for(auto node : _node->statements)
	{
		if(!IS(StatementNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(BlockStatementNode), node->GetLine());
		}
		
		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, IfElseStatementNode)
{
	if(!IS(ExpressionNode, _node->condition))
	{
		ErrorHandler::SyntaxError(BAD_NODE(IfElseStatementNode), _node->condition->GetLine());
	}

	//_node->condition->SetParent(_node);
	CHECK_PARENT(_node, _node->condition);
	_node->condition->Accept(this);

	if(!IS(BlockStatementNode, _node->ifBody))
	{
		ErrorHandler::SyntaxError(BAD_NODE(IfElseStatementNode), _node->ifBody->GetLine());
	}

	//_node->ifBody->SetParent(_node);
	CHECK_PARENT(_node, _node->ifBody);

	_node->ifBody->Accept(this);

	if(_node->elseBody)
	{
		if(!IS(BlockStatementNode, _node->elseBody))
		{
			ErrorHandler::SyntaxError(BAD_NODE(IfElseStatementNode), _node->elseBody->GetLine());
		}

		//_node->elseBody->SetParent(_node);
		CHECK_PARENT(_node, _node->elseBody);

		_node->elseBody->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, WhileStatementNode)
{
	if(!IS(ExpressionNode, _node->condition))
	{
		ErrorHandler::SyntaxError(BAD_NODE(WhileStatementNode), _node->condition->GetLine());
	}

	//_node->condition->SetParent(_node);
	CHECK_PARENT(_node, _node->condition);

	_node->condition->Accept(this);

	if(!IS(BlockStatementNode, _node->body))
	{
		ErrorHandler::SyntaxError(BAD_NODE(WhileStatementNode), _node->body->GetLine());
	}

	//_node->body->SetParent(_node);
	CHECK_PARENT(_node, _node->body);

	_node->body->Accept(this);
}

VISIT(CheckSyntaxVisitor, ForStatementNode)
{
	if(_node->init)
	{
		if(!IS(ExpressionNode, _node->init))
		{
			ErrorHandler::SyntaxError(BAD_NODE(ForStatementNode), _node->init->GetLine());
		}

		//_node->init->SetParent(_node);
		CHECK_PARENT(_node, _node->init);

		_node->init->Accept(this);
	}

	if(_node->condition)
	{
		if(!IS(ExpressionNode, _node->condition))
		{
			ErrorHandler::SyntaxError(BAD_NODE(ForStatementNode), _node->condition->GetLine());
		}

		//_node->condition->SetParent(_node);
		CHECK_PARENT(_node, _node->condition);

		_node->condition->Accept(this);
	}

	if(_node->update)
	{
		if(!IS(ExpressionNode, _node->update))
		{
			ErrorHandler::SyntaxError(BAD_NODE(ForStatementNode), _node->update->GetLine());
		}

		//_node->update->SetParent(_node);
		CHECK_PARENT(_node, _node->update);

		_node->update->Accept(this);
	}

	if(!IS(BlockStatementNode, _node->body))
	{
		ErrorHandler::SyntaxError(BAD_NODE(WhileStatementNode), _node->body->GetLine());
	}

	//_node->body->SetParent(_node);
	CHECK_PARENT(_node, _node->body);

	_node->body->Accept(this);
}

VISIT(CheckSyntaxVisitor, ReturnStatementNode)
{
	if(_node->expr)
	{
		if(!IS(ExpressionNode, _node->expr))
		{
			ErrorHandler::SyntaxError(BAD_NODE(ReturnStatementNode), _node->expr->GetLine());
		}

		//_node->expr->SetParent(_node);
		CHECK_PARENT(_node, _node->expr);

		_node->expr->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, VariableNode)
{
	if(_node->init)
	{
		if(!IS(ExpressionNode, _node->init))
		{
			ErrorHandler::SyntaxError(BAD_NODE(VariableNode), _node->init->GetLine());
		}

		//_node->init->SetParent(_node);
		CHECK_PARENT(_node, _node->init);

		_node->init->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, VariableBlockNode)
{
	for(auto node : _node->variables)
	{
		if(!IS(VariableNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(VariableBlockNode), node->GetLine());
		}
		
		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, ExpressionStatementNode)
{
	if(!IS(ExpressionNode, _node->expr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(ExpressionStatementNode), _node->expr->GetLine());
	}

	//_node->expr->SetParent(_node);
	CHECK_PARENT(_node, _node->expr);

	_node->expr->Accept(this);
}

VISIT(CheckSyntaxVisitor, NullExprNode)
{
}

VISIT(CheckSyntaxVisitor, BoolCteExprNode)
{
}

VISIT(CheckSyntaxVisitor, CharCteExprNode)
{
}

VISIT(CheckSyntaxVisitor, IntCteExprNode)
{
}

VISIT(CheckSyntaxVisitor, RealCteExprNode)
{
}

VISIT(CheckSyntaxVisitor, StringCteExprNode)
{
}

VISIT(CheckSyntaxVisitor, GreaterExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(GreaterExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(GreaterExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);

	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, LesserExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(LesserExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(LesserExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, EqualExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(EqualExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(EqualExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);

	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, NotEqualExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(NotEqualExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(NotEqualExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, AndExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(AndExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(AndExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, OrExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(OrExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(OrExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, PlusExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(PlusExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(PlusExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, MinusExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(MinusExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(MinusExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, MulExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(MulExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(MulExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, DivExprNode)
{
	if(!IS(ExpressionNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(DivExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(DivExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, AssignmentExprNode)
{
	if(!IS(SlotNode, _node->leftExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(AssignmentExprNode), _node->leftExpr->GetLine());
	}

	//_node->leftExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->leftExpr);

	_node->leftExpr->Accept(this);

	if(!IS(ExpressionNode, _node->rightExpr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(AssignmentExprNode), _node->rightExpr->GetLine());
	}

	//_node->rightExpr->SetParent(_node);
	CHECK_PARENT(_node, _node->rightExpr);
	
	_node->rightExpr->Accept(this);
}

VISIT(CheckSyntaxVisitor, NotExprNode)
{
	if(!IS(ExpressionNode, _node->expr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(NotExprNode), _node->expr->GetLine());
	}

	//_node->expr->SetParent(_node);
	CHECK_PARENT(_node, _node->expr);

	_node->expr->Accept(this);
}

VISIT(CheckSyntaxVisitor, MinusUnaryExprNode)
{
	if(!IS(ExpressionNode, _node->expr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(MinusUnaryExprNode), _node->expr->GetLine());
	}

	//_node->expr->SetParent(_node);
	CHECK_PARENT(_node, _node->expr);

	_node->expr->Accept(this);
}

VISIT(CheckSyntaxVisitor, CastExprNode)
{
	if(!IS(ExpressionNode, _node->expr))
	{
		ErrorHandler::SyntaxError(BAD_NODE(CastExprNode), _node->expr->GetLine());
	}

	//_node->expr->SetParent(_node);
	CHECK_PARENT(_node, _node->expr);

	_node->expr->Accept(this);
}

VISIT(CheckSyntaxVisitor, NewExprNode)
{
	for(auto node : _node->exprs)
	{
		if(!IS(ExpressionNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(NewExprNode), node->GetLine());
		}

		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, NewArrayExprNode)
{
	for(auto node : _node->exprs)
	{
		if(!IS(ExpressionNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(NewExprNode), node->GetLine());
		}

		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, SlotNode)
{
	for(auto node : _node->exprs)
	{
		if(!IS(ExpressionNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(SlotNode), node->GetLine());
		}

		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}

VISIT(CheckSyntaxVisitor, ThisSlotNode)
{
}

VISIT(CheckSyntaxVisitor, IdentifierSlotNode)
{
	for(auto node : _node->arguments)
	{
		if(!IS(ExpressionNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(SlotNode), node->GetLine());
		}

		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}

	for(auto node : _node->indexes)
	{
		if(!IS(ExpressionNode, node))
		{
			ErrorHandler::SyntaxError(BAD_NODE(SlotNode), node->GetLine());
		}

		//node->SetParent(_node);
		CHECK_PARENT(_node, node);

		node->Accept(this);
	}
}
