#include "code_generation.h"
#include "il_generator.h"

#include <compiler.h>

using namespace CodeGeneration;

void CodeGeneration::Parse(AST::Node* _program)
{
	ILGenerator il(Compiler::Assembly());
	_program->Accept(&il);
}
