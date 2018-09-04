#ifndef __EXPRESSION_NODES_H__
#define __EXPRESSION_NODES_H__

#include <ast/node.h>
#include <symbols/symbols.h>

namespace AST
{
	struct NullExprNode : public Node
	{
        	CAN_BE_VISITED;
	};

	struct BoolCteExprNode : public Node
	{
	        CAN_BE_VISITED;

		bool value;

		BoolCteExprNode(bool _value);
	};

	struct CharCteExprNode : public Node
	{
	        CAN_BE_VISITED;

		char value;

		CharCteExprNode(char _value);
	};
	
	struct IntCteExprNode : public Node
	{
	        CAN_BE_VISITED;

		int value;

		IntCteExprNode(int _value);
	};
	
	struct RealCteExprNode : public Node
	{
	        CAN_BE_VISITED;

		double value;

		RealCteExprNode(double _value);
	};

	struct StringCteExprNode : public Node
	{
	        CAN_BE_VISITED;

		string value;

		StringCteExprNode(string _value);
	};

	struct BinaryOperatorExprNode : public Node
	{
		Node* leftExpr;
		Node* rightExpr;

		BinaryOperatorExprNode(Node* _leftExpr, Node* _rightExpr); 
	};

	struct GreaterExprNode : public BinaryOperatorExprNode
	{
        	CAN_BE_VISITED;

		GreaterExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct LesserExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		LesserExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct EqualExprNode : public BinaryOperatorExprNode
	{
        	CAN_BE_VISITED;

		EqualExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct NotEqualExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		NotEqualExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct AndExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		AndExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct OrExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		OrExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct PlusExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		PlusExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct MinusExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		MinusExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct MulExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		MulExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct DivExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		DivExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct AssignmentExprNode : public BinaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		AssignmentExprNode(Node* _leftExpr, Node* _rightExpr);
	};

	struct UnaryOperatorExprNode : public Node
	{
		Node* expr;

		UnaryOperatorExprNode(Node* _expr);
	};

	struct NotExprNode : public UnaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		NotExprNode(Node* _expr);
	};

	struct MinusUnaryExprNode : public UnaryOperatorExprNode
	{
	        CAN_BE_VISITED;

		MinusUnaryExprNode(Node* _expr);
	};

	struct CastExprNode : public Node
	{
        	CAN_BE_VISITED;

		string type;
		Node*  expr;

		CastExprNode(string _type, Node* _expr); 
	};
	
	struct NewExprNode : public Node
	{
	        CAN_BE_VISITED;

		string     type;
		Collection exprs;
	};

	struct NewArrayExprNode : public Node
	{
        	CAN_BE_VISITED;

	        string     type;
		Collection exprs;
	};

	struct SlotNode : public Node
	{
        	CAN_BE_VISITED;
		
		bool isLeftValue;
		Collection exprs;
	};

	struct ThisSlotNode : public Node
	{
	        CAN_BE_VISITED;
	};

	struct IdentifierSlotNode : public Node
	{
        	CAN_BE_VISITED;

		string     identifier;
		bool       methodInvocation;
		Collection arguments;
		Collection indexes;

		Symbols::Symbol* symbol;
	};
};

#endif
