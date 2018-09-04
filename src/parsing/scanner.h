#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <map>
#include <string>
#include <iostream>
using namespace std;

#define _DEBUG

class Scanner
{
	static int lineNumber;
	static string stringConstant;
	static map<string, int> reservedWords;

#ifdef _DEBUG
	static ostream& out;
#endif

public:
	static void   Init(const string& _fileName);
	
    static int    SearchReservedWord(const string& _identifier);
	
    static void   NewStringConstant();
	static void   AddStringConstant(const char* _text);
	static string GetStringConstant();
	
    static void   NewLine();
	static int    GetLineNumber();
	
    static void   Error(const string& _error);
	
#ifdef _DEBUG
	static int ShowToken(int _token);
#endif
};

//
// int yylex();
//

#endif
