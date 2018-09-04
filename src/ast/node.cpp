#include <ast/node.h>

using namespace AST;

//
// Node
//
Node::Node()
    : parent(0), line(0)
{
}

Node::~Node() = default;

void Node::SetParent(Node* _newParent)
{
	parent = _newParent;
}

Node* Node::GetParent()
{
	return parent;
}

void Node::SetLine(int _line)
{
	line = _line;
}

int Node::GetLine()
{
	return line;
}

void Node::SetType(Types::Type* _type)
{
	type = _type;
}

Types::Type* Node::GetType()
{
	return type;
}

void Node::Accept(Visitor* _visitor)
{
}
