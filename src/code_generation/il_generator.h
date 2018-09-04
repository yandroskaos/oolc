#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include <fstream>
#include <string>
using namespace std;

#include <ast/visitor.h>
#include <ast/node.h>
#include <types/types.h>
#include <symbols/symbols.h>

namespace CodeGeneration
{
	class ILGenerator : public AST::Visitor
	{
	public:
		static string CTSTypeName  (Types::Type* _type);
		static string CTSTypeName  (string       _type);
		static string CTSTypeName  (AST::Node*   _node);

		static string ILTypeName  (Types::Type* _type);
		static string ILTypeName  (string       _type);
		static string ILTypeName  (AST::Node*   _node);

	private:
		bool IsMain(AST::MethodNode* _node);
		string AccessName(Symbols::Access _access);

		string Arguments(AST::MethodNode*      _method);
		string Arguments(AST::Collection const& _call);

		ofstream file;
		string module;
		int anidation;

		string Anidate(int _anidation);
		void Write(string _line);
		void WriteLn(string _line);

		int lastReturnAddress;
		string Locals(int _anidation, string _returnType, AST::Node* _block);
		string Return(string _returnType, int _address);

		int labels;
		int retLabels;
		void Label(string _label);
		
		Types::Class* actualClass;

		void GenerateStore(AST::SlotNode* _node);

	public:
		ILGenerator(string _fileName);
		~ILGenerator();

		WILL_VISIT(AST::ProgramNode);
		WILL_VISIT(AST::InterfaceNode);
		WILL_VISIT(AST::PrototypeNode);
		WILL_VISIT(AST::ClassNode);
		WILL_VISIT(AST::AttributeNode);
		WILL_VISIT(AST::MethodNode);

		WILL_VISIT(AST::WriteStatementNode);
		WILL_VISIT(AST::ReadStatementNode);
		WILL_VISIT(AST::IfElseStatementNode);
		WILL_VISIT(AST::WhileStatementNode);
		WILL_VISIT(AST::ForStatementNode);
		WILL_VISIT(AST::ReturnStatementNode);
		WILL_VISIT(AST::VariableNode);

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
		WILL_VISIT(AST::IdentifierSlotNode);
	};
}

#endif
