#include "main_visitor.h"

#include <ast/structure_nodes.h>
#include <errors/handler.h>

using namespace Semantics;
using namespace AST;

MainVisitor::MainVisitor()
	: mainMethods(0)
{
}

VISIT(MainVisitor, ProgramNode)
{
	COLLECTION_ACCEPT(_node->classes)

	if(mainMethods == 0)
	{
		ErrorHandler::SemanticError("No method public static int main(string[]) defined", 0);
	}

	if(mainMethods > 1)
	{
		ErrorHandler::SemanticError("More than one main method defined", 0);
	}
}

VISIT(MainVisitor, MethodNode)
{
	Symbols::Method* s = dynamic_cast<Symbols::Method*>(_node->symbol);
	Types::Method*   t = dynamic_cast<Types::Method*>(s->Type());

	if( s->IsStatic()                               && 
		s->GetAccess() == Symbols::Access::Public   &&
		Types::Type::IsVoid(*t->GetReturnType())    && 
	   (s->Name() == "main" || s->Name() == "Main") &&
	    t->GetArguments().size() == 1               &&
	    t->GetArguments()[0]->Name() == "1string"	   
	)
	{
		mainMethods++;
	}
}
