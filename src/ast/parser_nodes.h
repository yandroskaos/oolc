#ifndef __PARSER_NODES_H__
#define __PARSER_NODES_H__

#include <ast/node.h>

namespace Parsing
{
	struct StringNode : public AST::Node
	{
		string* info;

		StringNode(string* _info);
	};

	struct DeclarationNode : public AST::Node
	{
		string* type;
		string* name;

		DeclarationNode(string* _type, string* _name);
	};

	struct InitNode : public AST::Node
	{
		string*    name;
		AST::Node* expr;

		InitNode(string* _name, AST::Node* _expr); 
	};
};

#endif
