#include "handler.h"
#include <compiler.h>

#include <iostream>
using namespace std;

//#define ERROR_FILE "./Errors.txt"

//ofstream ErrorHandler::output(ERROR_FILE);
multiset<Error, ErrorCompare> ErrorHandler::errors;

void ErrorHandler::LexicalError(const string& _error, int _lineNumber)
{
	errors.insert(Error{ErrorKind::Lexical, _lineNumber, _error});
    //output << "Lexical error (" << _lineNumber << ") ==> " << _error.c_str() << endl;
	Fatal();
}

void ErrorHandler::SyntaxError(const string& _error, int _lineNumber)
{
	errors.insert(Error{ErrorKind::Syntax, _lineNumber, _error});
	//output << "Syntax error (" << _lineNumber << ") ==> " << _error.c_str() << endl;
	Fatal();
}

void ErrorHandler::SemanticError(const string& _error, int _lineNumber)
{
	errors.insert(Error{ErrorKind::Semantic, _lineNumber, _error});
	//output << "Semantic error (" << _lineNumber << ") ==> " << _error.c_str() << endl;
}

void ErrorHandler::CodeGenerationError(const string& _error, int _lineNumber)
{
	errors.insert(Error{ErrorKind::CodeGeneration, _lineNumber, _error});
	//output << "Code generation error (" << _lineNumber << ") ==> " << _error.c_str() << endl;
}

void ErrorHandler::Warning(const string& _warning, int _lineNumber)
{
	if(Compiler::Warnings())
	{
		errors.insert(Error{ErrorKind::Warning, _lineNumber, _warning});
		// output << "Warning (" << _lineNumber << ") ==> " << _warning.c_str() << endl;
	}
}

void ErrorHandler::Print()
{
	for(auto error : errors)
	{
		if(error.kind == ErrorKind::Warning)
			cout << "Warning ";
		cout << "[" << error.line << "] " << error.what << endl;
	}
}

void ErrorHandler::Fatal()
{
	throw new domain_error("Can't continue");
}

bool ErrorHandler::AreThereErrors()
{
	for(auto error : errors)
	{
		if(error.kind != ErrorKind::Warning)
			return true;
	}

	return false;
}
