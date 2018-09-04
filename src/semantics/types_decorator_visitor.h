#ifndef __TYPES_DECORATOR_VISITOR_H__
#define __TYPES_DECORATOR_VISITOR_H__

#include <stack>
using namespace std;

#include <ast/visitor.h>
#include <ast/node.h>
#include <ast/expression_nodes.h>

#include <symbols/symbols.h>

#include <types/types.h>

namespace Semantics
{
	class TypesDecoratorVisitor : public AST::Visitor
	{
		void InsertCast(string _type, AST::Node* _parent, AST::Node*& _son, int _line);
		void CheckAssignment(Types::Type* _tl, Types::Type* _tr, AST::Node* _parent, AST::Node* _son);
		
		void CheckBooleanExpresion     (AST::BinaryOperatorExprNode* _node);
		void CheckEqualityExpresion    (AST::BinaryOperatorExprNode* _node);
		void CheckRelationalExpresion  (AST::BinaryOperatorExprNode* _node);
		void CheckAritmethicalExpresion(AST::BinaryOperatorExprNode* _node);

		Types::Method* CreateMethodType(AST::Collection const& _arguments);
		bool FindMethod    (Types::Method* _methodType, vector<Symbols::Method*> _methodList, Symbols::Method*& _methodWanted);
		void CastMethodCall(Types::Method* _methodType, AST::Collection& _arguments, AST::Node* _parent, int _lineNumber);

		Types::Class*    actualClass;
		Symbols::Method* actualMethod;
		int actualVariableAddress;

		stack<stack<Types::Type*>> contexts;
		bool                       accessMustBeStatic;
		void         SlotContextSet();
		void         SlotContextReset();
		bool         SlotContextEmpty();
		Types::Type* SlotContextLastType();
		void         SlotContextPush(Types::Type* _type);
		bool         SlotContextError();
		void         SlotContextSetError();
		bool         SlotContextAnidated();
	public:
		TypesDecoratorVisitor();

        //
		// Program Structure Nodes
        //
		WILL_VISIT(AST::ClassNode);
		WILL_VISIT(AST::AttributeNode);
		WILL_VISIT(AST::MethodNode);

        //
		// Statement Nodes
        //
		WILL_VISIT(AST::BlockStatementNode);
		WILL_VISIT(AST::WriteStatementNode);
		WILL_VISIT(AST::ReadStatementNode);
		WILL_VISIT(AST::IfElseStatementNode);
		WILL_VISIT(AST::WhileStatementNode);
		WILL_VISIT(AST::ForStatementNode);
		WILL_VISIT(AST::VariableNode);

        //
		// Expresion Nodes
        //
		WILL_VISIT(AST::NullExprNode);
		WILL_VISIT(AST::BoolCteExprNode);
		WILL_VISIT(AST::CharCteExprNode);
		WILL_VISIT(AST::IntCteExprNode);
		WILL_VISIT(AST::RealCteExprNode);
		WILL_VISIT(AST::StringCteExprNode);
		WILL_VISIT(AST::GreaterExprNode);
		WILL_VISIT(AST::LesserExprNode);
		WILL_VISIT(AST::EqualExprNode);
		WILL_VISIT(AST::NotEqualExprNode);
		WILL_VISIT(AST::AndExprNode);
		WILL_VISIT(AST::OrExprNode);
		WILL_VISIT(AST::PlusExprNode);
		WILL_VISIT(AST::MinusExprNode);
		WILL_VISIT(AST::MulExprNode);
		WILL_VISIT(AST::DivExprNode);
		WILL_VISIT(AST::AssignmentExprNode);
		WILL_VISIT(AST::NotExprNode);
		WILL_VISIT(AST::MinusUnaryExprNode);
		WILL_VISIT(AST::CastExprNode);
		WILL_VISIT(AST::NewExprNode);
		WILL_VISIT(AST::NewArrayExprNode);
		WILL_VISIT(AST::SlotNode);
		WILL_VISIT(AST::ThisSlotNode);
		WILL_VISIT(AST::IdentifierSlotNode);
	};
}

#endif
