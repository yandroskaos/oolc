#ifndef __STATEMENTS_NODES_H__
#define __STATEMENTS_NODES_H__

#include <ast/node.h>
#include <symbols/symbols.h>

namespace AST
{
	struct BlockStatementNode : public Node
	{
        CAN_BE_VISITED;

		Collection statements;
	};

	struct EmptyStatementNode : public Node
	{
        CAN_BE_VISITED;
	};

	struct WriteStatementNode : public Node
	{
        CAN_BE_VISITED;

		Node* expr;

		WriteStatementNode(Node* _expr);
	};

	struct ReadStatementNode : public Node
	{
        CAN_BE_VISITED;

		Node* slot;

		ReadStatementNode(Node* _slot);
	};

	struct IfElseStatementNode : public Node
	{
        CAN_BE_VISITED;

		Node* condition;
		Node* ifBody;
		Node* elseBody;

		IfElseStatementNode(Node* _condition, Node* _ifBody, Node* _elseBody); 
	};

	struct WhileStatementNode : public Node
	{
        CAN_BE_VISITED;

		Node* condition;
		Node* body;

		WhileStatementNode(Node* _condition, Node* _body); 
	};

	struct ForStatementNode : public Node
	{
        CAN_BE_VISITED;

		Node* init;
		Node* condition;
		Node* update;
		Node* body;

		ForStatementNode(Node* _init, Node* _condition, Node* _update, Node* _body); 
	};

	struct ReturnStatementNode : public Node
	{
        CAN_BE_VISITED;

		Node* expr;

		ReturnStatementNode(Node* _expr); 
	};

	struct VariableNode : public Node
	{
        CAN_BE_VISITED;

		string type;
		string name;
		Node*  init;

		Symbols::Variable* symbol;
	};

	struct VariableBlockNode : public Node
	{
        CAN_BE_VISITED;

		Collection variables;
	};

	struct ExpressionStatementNode : public Node
	{
        CAN_BE_VISITED;

		Node* expr;

		ExpressionStatementNode(Node* _expr); 
	};

};

#endif
