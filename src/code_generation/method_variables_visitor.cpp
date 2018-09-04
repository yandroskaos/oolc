#include "method_variables_visitor.h"
#include "il_generator.h"
#include <ast/statement_nodes.h>

#include <types/types.h>
#include <utils/conversion.h>

using namespace CodeGeneration;
using namespace AST;

string MethodVariablesVisitor::ILTypeName(string _type)
{
	return ILGenerator::ILTypeName(_type);
}

string MethodVariablesVisitor::AddAnidation(int _anidation)
{
	string result = "";
	
	for(int i = 0; i < _anidation; ++i)
		result += "\t";
	
	return result;
}

MethodVariablesVisitor::MethodVariablesVisitor(int _anidation, string _returnType)
	: anidation(_anidation)
	, returnType(_returnType)
{
	variables = "";
	firstVariable = true;
	addresses = 0;
}

VISIT(MethodVariablesVisitor, VariableNode)
{
	if(firstVariable)
	{
		variables += " ";
		firstVariable = false;
	}
	else
	{
		variables += ", ";
	}

	variables += "[" + to_string(addresses++) + "]\t" + 
		ILTypeName(_node->type) + " " + _node->name + "\n" + 
		AddAnidation(anidation);
}


bool MethodVariablesVisitor::HasVariables()
{
	if(returnType != "void")
		return true;

	return !firstVariable;
}

string MethodVariablesVisitor::Line()
{
	if(returnType == "void")
		return variables;

	string ret = "[" + to_string(addresses) + "]\t" + 
		ILTypeName(returnType) + " CS$00000003$00000000\n" + 
		AddAnidation(anidation);

	if (variables == "")
		return ret;

	return variables + "," + ret;
}

int MethodVariablesVisitor::ReturnAddress()
{
	return addresses;
}