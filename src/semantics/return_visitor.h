#ifndef __RETURN_VISITOR_H__
#define __RETURN_VISITOR_H__

#include <ast/visitor.h>
#include <types/types.h>

namespace Semantics
{
	class ReturnVisitor : public AST::Visitor
	{
		Types::Type* expectedReturnType;
		bool         inConstructor;
		bool         returnFound;
		int          anidation;
		bool         returnFoundNotAnidated;

		void Reset();
	public:
		ReturnVisitor();

		WILL_VISIT(AST::MethodNode);

		WILL_VISIT(AST::BlockStatementNode);
		WILL_VISIT(AST::ReturnStatementNode);
	};
}

#endif