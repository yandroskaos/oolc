#include "semantics.h"
#include "types_builder_visitor.h"
#include "types_decorator_visitor.h"
#include "return_visitor.h"
#include "interface_visitor.h"
#include "main_visitor.h"

#include <parsing/check_syntax_visitor.h>
#include <compiler.h>

#include <errors/handler.h>

void Semantics::Parse(AST::Node* _program)
{
	Parsing::CheckSyntaxVisitor csv;
	_program->Accept(&csv);

	if(ErrorHandler::AreThereErrors())
		return;

	TypesBuilderVisitor tbv;
	_program->Accept(&tbv);

	if(ErrorHandler::AreThereErrors())
		return;

	TypesDecoratorVisitor tdv;
	_program->Accept(&tdv);

	ReturnVisitor rv;
	_program->Accept(&rv);

	InterfaceVerifierVisitor ivv;
	_program->Accept(&ivv);

	if(!Compiler::Dll())
	{
		MainVisitor mv;
		_program->Accept(&mv);
	}
}


