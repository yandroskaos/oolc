#ifndef __TYPES_BUILDER_VISITOR_H__
#define __TYPES_BUILDER_VISITOR_H__

#include <ast/visitor.h>
#include <types/types.h>

namespace Semantics
{
	class TypesBuilderVisitor : public AST::Visitor
	{
	public:
		WILL_VISIT(AST::ProgramNode);
	};

	class TypesInserterVisitor : public AST::Visitor
	{
		void CheckDoesNotExists(string _type, int _line);
	public:
		WILL_VISIT(AST::InterfaceNode);
		WILL_VISIT(AST::ClassNode);
	};

	class TypesConstructorVisitor : public AST::Visitor
	{
		Types::Class* actualClass;

	public:
		TypesConstructorVisitor();
		WILL_VISIT(AST::InterfaceNode);
		WILL_VISIT(AST::PrototypeNode);
		WILL_VISIT(AST::ClassNode);
		WILL_VISIT(AST::AttributeNode);
		WILL_VISIT(AST::MethodNode);
	};
};

#endif