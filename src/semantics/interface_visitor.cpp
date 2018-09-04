#include "interface_visitor.h"

#include <ast/structure_nodes.h>
#include <types/types.h>
#include <errors/handler.h>

using namespace Semantics;
using namespace AST;

VISIT(InterfaceVerifierVisitor, ClassNode)
{
	Types::Class* classType = dynamic_cast<Types::Class*>(Types::table[_node->name]);

	for(auto interfaceName : _node->interfaces)
	{
		Types::Interface* interfaceType = dynamic_cast<Types::Interface*>(Types::table[interfaceName]);

		//
		// Methods
		//
		Types::Class::Methods methods = interfaceType->GetAllMethods();
		
		for(auto overload : methods)
		{
			string methodName = overload.first;

			vector<Symbols::Method*> classOverloadMethod = classType->GetMethod(methodName);
			if(classOverloadMethod.empty())
			{
				ErrorHandler::SemanticError("Class " + _node->name + " does not override method " + methodName + " from interface " + interfaceType->Name(), _node->GetLine());
				continue;
			}
			
			for(auto interfaceMethod : overload.second)
			{
				bool implemented = false;

				for(auto classMethod : classOverloadMethod)
				{
					if(*classMethod->Type() == *interfaceMethod->Type())
					{
						if(interfaceMethod->GetAccess() != Symbols::Access::Public)
						{
							ErrorHandler::SemanticError("Class " + _node->name + " does not correctly set public access when implementing " + interfaceMethod->Name() + " " + interfaceMethod->Type()->Name() + " from interface " + interfaceType->Name(), _node->GetLine());
						}
						else
						{
							implemented = true;
						}
						break;
					}
				}

				if(!implemented)
				{
					ErrorHandler::SemanticError("Class " + _node->name + " does not implement method " + interfaceMethod->Name() + " " + interfaceMethod->Type()->Name() + " from interface " + interfaceType->Name(), _node->GetLine());
				}				
			}
		}
	}
}


