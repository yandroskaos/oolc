#include <ast/statement_nodes.h>

using namespace AST;

WriteStatementNode::WriteStatementNode(Node* _expr) 
    : expr(_expr)
{
	LINK(this, expr);
}

ReadStatementNode::ReadStatementNode(Node* _slot) 
    : slot(_slot)
{
	LINK(this, slot);
}

IfElseStatementNode::IfElseStatementNode(Node* _condition, Node* _ifBody, Node* _elseBody) 
	: condition(_condition), ifBody(_ifBody), elseBody(_elseBody) 
{
	LINK(this, condition);
	LINK(this, ifBody);
	LINK(this, elseBody);
}

WhileStatementNode::WhileStatementNode(Node* _condition, Node* _body) 
	: condition(_condition), body(_body) 
{
	LINK(this, condition);
	LINK(this, body);
}

ForStatementNode::ForStatementNode(Node* _init, Node* _condition, Node* _update, Node* _body) 
	: init(_init), condition(_condition), update(_update), body(_body) 
{
	LINK(this, init);
	LINK(this, condition);
	LINK(this, update);
	LINK(this, body);
}

ReturnStatementNode::ReturnStatementNode(Node* _expr) 
	: expr(_expr) 
{
	LINK(this, expr);
}

ExpressionStatementNode::ExpressionStatementNode(Node* _expr) 
	: expr(_expr)
{
	LINK(this, expr);
}

ACCEPT_VISITOR(EmptyStatementNode)
ACCEPT_VISITOR(WriteStatementNode)
ACCEPT_VISITOR(ReadStatementNode)
ACCEPT_VISITOR(BlockStatementNode)
ACCEPT_VISITOR(IfElseStatementNode)
ACCEPT_VISITOR(WhileStatementNode)
ACCEPT_VISITOR(ForStatementNode)
ACCEPT_VISITOR(ReturnStatementNode)
ACCEPT_VISITOR(VariableNode)
ACCEPT_VISITOR(VariableBlockNode)
ACCEPT_VISITOR(ExpressionStatementNode)
