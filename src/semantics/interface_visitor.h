#ifndef __INTERFACE_VISITOR_H__
#define __INTERFACE_VISITOR_H__

#include <ast/visitor.h>

namespace Semantics
{
	class InterfaceVerifierVisitor : public AST::Visitor
	{
	public:
		WILL_VISIT(AST::ClassNode);
	};
};

#endif