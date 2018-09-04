#include <ast/expression_nodes.h>

using namespace AST;

BoolCteExprNode::BoolCteExprNode(bool _value)
	: value(_value)
{}

CharCteExprNode::CharCteExprNode(char _value)
	: value(_value)
{}

IntCteExprNode::IntCteExprNode(int _value)
	: value(_value)
{}

RealCteExprNode::RealCteExprNode(double _value)
	: value(_value)
{}

StringCteExprNode::StringCteExprNode(string _value)
	: value(_value)
{}

BinaryOperatorExprNode::BinaryOperatorExprNode(Node* _leftExpr, Node* _rightExpr) 
	: leftExpr(_leftExpr), rightExpr(_rightExpr)
{
	LINK(this, leftExpr);
	LINK(this, rightExpr);
}

GreaterExprNode::GreaterExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

LesserExprNode::LesserExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

EqualExprNode::EqualExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

NotEqualExprNode::NotEqualExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

AndExprNode::AndExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

OrExprNode::OrExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

PlusExprNode::PlusExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

MinusExprNode::MinusExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

MulExprNode::MulExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

DivExprNode::DivExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

AssignmentExprNode::AssignmentExprNode(Node* _leftExpr, Node* _rightExpr)
	: BinaryOperatorExprNode(_leftExpr, _rightExpr)
{}

UnaryOperatorExprNode::UnaryOperatorExprNode(Node* _expr) 
	: expr(_expr)
{
	LINK(this, expr);
}

NotExprNode::NotExprNode(Node* _expr) 
	: UnaryOperatorExprNode(_expr)
{}

MinusUnaryExprNode::MinusUnaryExprNode(Node* _expr) 
	: UnaryOperatorExprNode(_expr)
{}

CastExprNode::CastExprNode(string _type, Node* _expr) 
	: type(_type), expr(_expr)
{
	LINK(this, expr);
}

ACCEPT_VISITOR(NullExprNode)
ACCEPT_VISITOR(BoolCteExprNode)
ACCEPT_VISITOR(CharCteExprNode)
ACCEPT_VISITOR(IntCteExprNode)
ACCEPT_VISITOR(RealCteExprNode)
ACCEPT_VISITOR(StringCteExprNode)
ACCEPT_VISITOR(GreaterExprNode)
ACCEPT_VISITOR(LesserExprNode)
ACCEPT_VISITOR(EqualExprNode)
ACCEPT_VISITOR(NotEqualExprNode)
ACCEPT_VISITOR(AndExprNode)
ACCEPT_VISITOR(OrExprNode)
ACCEPT_VISITOR(PlusExprNode)
ACCEPT_VISITOR(MinusExprNode)
ACCEPT_VISITOR(MulExprNode)
ACCEPT_VISITOR(DivExprNode)
ACCEPT_VISITOR(AssignmentExprNode)
ACCEPT_VISITOR(NotExprNode)
ACCEPT_VISITOR(MinusUnaryExprNode)
ACCEPT_VISITOR(CastExprNode)
ACCEPT_VISITOR(NewExprNode)
ACCEPT_VISITOR(NewArrayExprNode)
ACCEPT_VISITOR(SlotNode)
ACCEPT_VISITOR(ThisSlotNode)
ACCEPT_VISITOR(IdentifierSlotNode)
