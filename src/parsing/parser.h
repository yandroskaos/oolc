#include <string>
#include <stack>
#include <iostream>
using namespace std;

#define _DEBUG

class Parser
{
	static stack<int> lines;

	static void Init(const string& _fileName);

#ifdef _DEBUG
	static ostream& out;
#endif

public:
	static void Parse(const string& _fileName);

	static int  PopLine();
	static void PushLine();
	static void Error(const string& _error);
	
#ifdef _DEBUG
	static void Rule(const string& _ruleName);
#endif
};
