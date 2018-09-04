#include <iostream>
#include "compiler.h"
#include <ast/node.h>
#include <ast/builder.h>
#include <parsing/parser.h>
#include <semantics/semantics.h>
#include <code_generation/code_generation.h>
//#include <code_generation/beautifier.h>
#include <errors/handler.h>

bool ParseParameters(int argc, char* argv[], string& _fileName, bool& _isDll, bool& _disableWarnings);
void Usage(const string& _executableName);

int main(int argc, char* argv[])
{
	try
	{
		string fileName      = "";
		bool isDll           = false;
		bool disableWarnings = false;

		if(ParseParameters(argc, argv, fileName, isDll, disableWarnings))
		{
			Compiler::Init(fileName, isDll, disableWarnings);

			Parser::Parse(fileName);
			
			AST::Node* program = AST::Builder::GetProgram();

			Semantics::Parse(program);

			if(ErrorHandler::AreThereErrors())
			{
				ErrorHandler::Print();
				ErrorHandler::Fatal();
			}

			CodeGeneration::Parse(program);

			//CodeGeneration::Beautifier beautifier(fileName + "_beautified.txt");
			//program->Accept(&beautifier);
		}
		else
		{
			Usage(argv[0]);
		}
	}
	catch(std::exception* _ex)
	{
		cout << _ex->what() << endl;
	}
	catch(...)
	{
		cout << "Hard crash!" << endl;
	}

	return 0;
}


string Compiler::ms_fileName = "";
bool   Compiler::ms_isDll    = false;
bool   Compiler::ms_warnings = true;

void Compiler::Init(const string& _fileName, bool _isDll, bool _disableWarnings)
{
	ms_fileName = _fileName.substr(0, _fileName.find_first_of('.'));;
	ms_isDll    = _isDll;
	ms_warnings = !_disableWarnings;
} 

string Compiler::Module()
{
	return ms_fileName + (ms_isDll ? ".dll" : ".exe");
}

string Compiler::Assembly()
{
	return ms_fileName;
}

string Compiler::Namespace()
{
	return ms_fileName;
}

bool Compiler::Dll()
{
	return ms_isDll;
}

bool Compiler::Warnings()
{
	return ms_warnings;
}


bool ParseParameters(int argc, char* argv[], string& _fileName, bool& _isDll, bool& _disableWarnings)
{
	if(argc < 2 || argc > 4)
		return false;

	_fileName        = "";
	_isDll           = false;
	_disableWarnings = false;

	for (int i = 1; i < argc; ++i)
	{
		string parameter = argv[i];

		if(parameter == "-dll")
		{
			_isDll = true;
		}
		else if(parameter == "-dw")
		{
			_disableWarnings = true;
		}
		else if(_fileName == "")
		{
			_fileName = parameter;
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Usage(const string& _executableName)
{
	cout << "USE: "<< _executableName << " inputFile [-dll] [-dw]" << endl;
	cout << "\t" << "-dll -> File will be assembled as dll instead of exe" << endl;
	cout << "\t" << "-dw  -> disable warnings" << endl;
}
