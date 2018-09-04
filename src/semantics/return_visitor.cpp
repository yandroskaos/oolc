#include "return_visitor.h"

#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>

#include <errors/handler.h>

using namespace Semantics;
using namespace AST;

void ReturnVisitor::Reset()
{
	expectedReturnType = nullptr;
	inConstructor = false;
	returnFound = false;
	anidation = 0;
	returnFoundNotAnidated = false;
}

ReturnVisitor::ReturnVisitor()
{
	Reset();
}

VISIT(ReturnVisitor, MethodNode)
{
	Reset();
	expectedReturnType = Types::table[_node->returnType];

	//
	// If method name is a type, this is a constructor
	// Also it has been previously verified it matches the enclosing
	// class in other visitor, so there's no problem
	//
	inConstructor = Types::table[_node->name] != 0;

	_node->body->Accept(this);

	if(_node->returnType != "void")
	{
		if(!returnFound)
		{
			ErrorHandler::SemanticError("Method " + _node->name + " has no return expression", _node->GetLine());
		}
		else if(!returnFoundNotAnidated)
		{
			ErrorHandler::Warning("Method " + _node->name + ": not all control paths return a value", _node->GetLine());
		}
	}
}

VISIT(ReturnVisitor, BlockStatementNode)
{
	anidation++;

	COLLECTION_ACCEPT(_node->statements)
	
	anidation--;
}

VISIT(ReturnVisitor, ReturnStatementNode)
{
	returnFound = true;

	if(anidation == 1)
		returnFoundNotAnidated = true;

	if(inConstructor && _node->expr)
	{
		ErrorHandler::SemanticError("Return expression statement inside constructor", _node->GetLine());
		return;
	}

	if(_node->expr && Types::Type::IsVoid(*expectedReturnType))
	{
		ErrorHandler::SemanticError("Return expression in a void method", _node->GetLine());
	}
	
	if(!_node->expr && !Types::Type::IsVoid(*expectedReturnType))
	{
		ErrorHandler::SemanticError("Return void expression in a method with expected type " + expectedReturnType->Name(), _node->GetLine());
	}
	
	if(_node->expr && !Types::Type::IsVoid(*expectedReturnType))
	{
		Types::Type* returnType = _node->expr->GetType();
		
		if(*expectedReturnType != *returnType)
		{
			if(returnType->ImplicitCastTo(*expectedReturnType))
			{
				if(!Types::Type::IsNull(*returnType))
				{
					AST::CastExprNode* cast = new AST::CastExprNode(expectedReturnType->Name(), _node->expr);
					cast->SetType(Types::table[expectedReturnType->Name()]);
					_node->expr->SetParent(cast);
					_node->expr = cast;
					cast->SetParent(_node);
			
					ErrorHandler::Warning("Compiler is inserting an implicit cast from " + 
						_node->expr->GetType()->Name() + 
						" to " + 
						expectedReturnType->Name(), _node->GetLine());
				}
			}
			else
			{
				ErrorHandler::SemanticError("Expected return type is " + expectedReturnType->Name() + ", found " + returnType->Name(), _node->GetLine());
			}
		}
	}
}
