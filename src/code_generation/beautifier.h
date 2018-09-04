#ifndef __BEAUTIFIER_H__
#define __BEAUTIFIER_H__

#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include <ast/visitor.h>
#include <ast/node.h>
#include <symbols/symbols.h>

namespace CodeGeneration
{
	class Beautifier : public AST::Visitor
	{
		ofstream file;
		int anidation;

		void FeedLine();
		void Write(string _info, bool _feedLine = false);
		void WriteLn(string _info, bool _feedLine = false);

		string Access(Symbols::Access _access);
		void StringList(vector<string>& _list);
		void MixedStringList(vector<string>& _list1, vector<string>& _list2);
		void CallList(AST::Collection& _call);
		void InitList(vector<string>& _names, vector<AST::Collection>& _calls);
		
	public:
		Beautifier(const string& _fileName);
		~Beautifier();

		WILL_VISIT(AST::ProgramNode);
		WILL_VISIT(AST::InterfaceNode);
		WILL_VISIT(AST::PrototypeNode);
		WILL_VISIT(AST::ClassNode);
		WILL_VISIT(AST::AttributeNode);
		WILL_VISIT(AST::MethodNode);

		WILL_VISIT(AST::EmptyStatementNode);
		WILL_VISIT(AST::WriteStatementNode);
		WILL_VISIT(AST::ReadStatementNode);
		WILL_VISIT(AST::BlockStatementNode);
		WILL_VISIT(AST::IfElseStatementNode);
		WILL_VISIT(AST::WhileStatementNode);
		WILL_VISIT(AST::ForStatementNode);
		WILL_VISIT(AST::ReturnStatementNode);
		WILL_VISIT(AST::VariableBlockNode);
		WILL_VISIT(AST::VariableNode);
		WILL_VISIT(AST::ExpressionStatementNode);

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