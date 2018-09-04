#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <string>
using namespace std;

class Compiler
{
	static string ms_fileName;
	static bool   ms_isDll;
	static bool   ms_warnings;

public:
	static void Init(const string& _fileName, bool _isDll, bool _enableWarnings);

	static string Module();
	static string Assembly();
	static string Namespace();
	static bool   Dll();
	static bool   Warnings();
};

#endif