#ifndef __MAIN_VISITOR_H__
#define __MAIN_VISITOR_H__

#include <ast/visitor.h>

namespace Semantics
{
	class MainVisitor : public AST::Visitor
	{
		int mainMethods;

	public:
		MainVisitor();
		
		WILL_VISIT(AST::ProgramNode);
		WILL_VISIT(AST::MethodNode);
	};
}

#endif
