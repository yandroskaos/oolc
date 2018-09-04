#ifndef __PROGRAM_STRUCTURE_NODES_H__
#define __PROGRAM_STRUCTURE_NODES_H__

#include <ast/node.h>
#include <symbols/symbols.h>

namespace AST
{
	struct ProgramNode : public Node
	{
        CAN_BE_VISITED;

        string     name;
		Collection classes;
	};

	struct InterfaceNode : public Node
	{
        CAN_BE_VISITED;

        string     name;
		Collection members;
	};

	struct PrototypeNode : public Node
	{
        CAN_BE_VISITED;

        string         returnType;
        string         name;
		vector<string> argumentTypes;

		Symbols::Method* symbol;
	};

	struct ClassNode : public Node
	{
        CAN_BE_VISITED;

		string         name;
		string         parent;
		vector<string> interfaces;
		Collection     members;
	};

	struct AttributeNode : public Node
	{
        CAN_BE_VISITED;

        bool            isStatic;
        Symbols::Access access;
        string          type;
		string          name;
		Node*           init;

		Symbols::Attribute* symbol;
	};

	struct MethodNode : public Node
	{
        CAN_BE_VISITED;

        bool            isStatic;
        Symbols::Access access;
        string          returnType;
		string          name;
		vector<string>  argumentTypes;
		vector<string>  argumentNames;
		Node*           body;

		Symbols::Method* symbol;
	};
}

#endif
