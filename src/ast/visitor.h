#ifndef __VISITOR_H__
#define __VISITOR_H__

#define WILL_VISIT(X) \
    void Visit(X* _node) override

#define VISIT(X, Y) \
    void X::Visit(Y* _node)

namespace AST
{
    //
    // AST Nodes
    //
	struct ProgramNode;
	struct InterfaceNode;
	struct PrototypeNode;
	struct ClassNode;
	struct AttributeNode;
	struct MethodNode;

	struct BlockStatementNode;
	struct EmptyStatementNode;
	struct WriteStatementNode;
	struct ReadStatementNode;
	struct IfElseStatementNode;
	struct WhileStatementNode;
	struct ForStatementNode;
	struct ReturnStatementNode;
	struct VariableNode;
	struct VariableBlockNode;
	struct ExpressionStatementNode;
	
	struct NullExprNode;
	struct BoolCteExprNode;
	struct CharCteExprNode;
	struct IntCteExprNode;
	struct RealCteExprNode;
	struct StringCteExprNode;
	struct GreaterExprNode;
	struct LesserExprNode;
	struct EqualExprNode;
	struct NotEqualExprNode;
	struct AndExprNode;
	struct OrExprNode;
	struct PlusExprNode;
	struct MinusExprNode;
	struct MulExprNode;
	struct DivExprNode;
	struct AssignmentExprNode;
	struct NotExprNode;
	struct MinusUnaryExprNode;
	struct CastExprNode;
	struct NewExprNode;
	struct NewArrayExprNode;
	struct SlotNode;
	struct ThisSlotNode;
	struct IdentifierSlotNode;

	class Visitor
	{
	public:
        virtual ~Visitor() = default;

        //
		// Program Structure Nodes
        //
        virtual void Visit(ProgramNode*     _node);
        virtual void Visit(InterfaceNode*   _node);
        virtual void Visit(PrototypeNode*   _node);
		virtual void Visit(ClassNode*       _node);
		virtual void Visit(AttributeNode*   _node);
		virtual void Visit(MethodNode*      _node);

        //
		// Statement Nodes
        //
		virtual void Visit(BlockStatementNode*           _node);
		virtual void Visit(EmptyStatementNode*           _node);
		virtual void Visit(WriteStatementNode*           _node);
		virtual void Visit(ReadStatementNode*            _node);
		virtual void Visit(IfElseStatementNode*          _node);
		virtual void Visit(WhileStatementNode*           _node);
		virtual void Visit(ForStatementNode*             _node);
		virtual void Visit(ReturnStatementNode*          _node);
		virtual void Visit(VariableNode*                 _node);
		virtual void Visit(VariableBlockNode*            _node);
		virtual void Visit(ExpressionStatementNode*      _node);

        //
		// Expresion Nodes
        //
		virtual void Visit(NullExprNode*            _node);
		virtual void Visit(BoolCteExprNode*         _node);
		virtual void Visit(CharCteExprNode*         _node);
		virtual void Visit(IntCteExprNode*          _node);
		virtual void Visit(RealCteExprNode*         _node);
		virtual void Visit(StringCteExprNode*       _node);
		virtual void Visit(GreaterExprNode*         _node);
		virtual void Visit(LesserExprNode*          _node);
		virtual void Visit(EqualExprNode*           _node);
		virtual void Visit(NotEqualExprNode*        _node);
		virtual void Visit(AndExprNode*             _node);
		virtual void Visit(OrExprNode*              _node);
		virtual void Visit(PlusExprNode*            _node);
		virtual void Visit(MinusExprNode*           _node);
		virtual void Visit(MulExprNode*             _node);
		virtual void Visit(DivExprNode*             _node);
		virtual void Visit(AssignmentExprNode*      _node);
		virtual void Visit(NotExprNode*             _node);
		virtual void Visit(MinusUnaryExprNode*      _node);
		virtual void Visit(CastExprNode*            _node);
		virtual void Visit(NewExprNode*             _node);
		virtual void Visit(NewArrayExprNode*        _node);
		virtual void Visit(SlotNode*                _node);
		virtual void Visit(ThisSlotNode*            _node);
		virtual void Visit(IdentifierSlotNode*      _node);
	};
};

#endif
