#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__

#include <string>
#include <set>
#include <fstream>
using namespace std;

enum class ErrorKind
{
	Warning,
	Lexical,
	Syntax,
	Semantic,
	CodeGeneration
};

struct Error
{
	ErrorKind kind;
	int       line;
	string    what;
};

struct ErrorCompare
{
	bool operator()(Error const& a, Error const& b)
	{
		return a.line < b.line;
	}
};

class ErrorHandler
{
	//static ofstream output;
	static multiset<Error, ErrorCompare> errors;

public:
	static void LexicalError       (const string& _error,   int _lineNumber);
	static void SyntaxError        (const string& _error,   int _lineNumber);
	static void SemanticError      (const string& _error,   int _lineNumber);
	static void CodeGenerationError(const string& _error,   int _lineNumber);
	static void Warning            (const string& _warning, int _lineNumber);
	static void Print              ();
	static void Fatal              ();
	static bool AreThereErrors     ();
};

#endif
