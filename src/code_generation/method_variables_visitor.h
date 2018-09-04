#ifndef __METHOD_VARIABLES_VISITOR_H__
#define __METHOD_VARIABLES_VISITOR_H__

#include <string>
using namespace std;

#include <ast/visitor.h>

namespace CodeGeneration
{
	class MethodVariablesVisitor : public AST::Visitor
	{
		int anidation;
		string returnType;

		string variables;
		bool firstVariable;		
		int addresses;

		string ILTypeName(string _type);
		string AddAnidation(int _anidation);
	public:
		MethodVariablesVisitor(int _anidation, string _returnType);

		WILL_VISIT(AST::VariableNode);

		bool   HasVariables();
		string Line();
		int    ReturnAddress();
	};
}

#endif
