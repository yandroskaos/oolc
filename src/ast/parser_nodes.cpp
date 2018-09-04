#include "parser_nodes.h"

using namespace Parsing;

StringNode::StringNode(string* _info) 
    : info(_info)
{}

DeclarationNode::DeclarationNode(string* _type, string* _name) 
	: type(_type), name(_name)
{}

InitNode::InitNode(string* _name, AST::Node* _expr) 
	: name(_name), expr(_expr)
{}
