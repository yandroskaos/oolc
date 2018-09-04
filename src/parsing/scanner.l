%{
#include <errors/handler.h>
#include <utils/conversion.h>
#include <ast/node.h>
#include "tokens.h"
#include "scanner.h"

#ifdef _DEBUG
	#define SHOW_TOKEN(X)   Scanner::ShowToken(X)
#else
	#define SHOW_TOKEN(X)   X
#endif

%}

%start comment_some_lines
%start comment_one_line
%start string_cte
 
%%

"/*"							BEGIN comment_some_lines;
<comment_some_lines>"*/"		BEGIN 0;
<comment_some_lines>[\n]		Scanner::NewLine();
<comment_some_lines>[^\n"*/"]*	;
<comment_some_lines>["//"]		;
"//"							BEGIN comment_one_line;
<comment_one_line>[^"\n"]*		;
<comment_one_line>[\n]			{BEGIN 0; Scanner::NewLine();}
<string_cte>\"					{
									BEGIN 0;
									yylval.identifier = new string(Scanner::GetStringConstant());
									return SHOW_TOKEN(STRING_CTE);
								}
<string_cte>[\n]				Scanner::Error("New line found in an string constant -> " + Scanner::GetStringConstant());
<string_cte>[^\n"]*				Scanner::AddStringConstant(yytext);
\"								{
									BEGIN string_cte;
									Scanner::NewStringConstant();
								}
\n								Scanner::NewLine();
[ \t\r]*						;

"&&" 					return SHOW_TOKEN(AND);
"||" 					return SHOW_TOKEN(OR);
"==" 					return SHOW_TOKEN(EQ);
"!=" 					return SHOW_TOKEN(NE);
true					{yylval.boolValue = true;            return SHOW_TOKEN(BOOL_CTE);}
false					{yylval.boolValue = false;           return SHOW_TOKEN(BOOL_CTE);}
\'.\'					{yylval.charValue = yytext[1];       return SHOW_TOKEN(CHAR_CTE);}
[0-9]+					{yylval.intValue  = to_int(yytext);  return SHOW_TOKEN(INT_CTE);}
[0-9]+"."[0-9]+   		{yylval.realValue = to_real(yytext); return SHOW_TOKEN(REAL_CTE);}
[a-zA-Z][a-zA-Z_0-9]* 	{
							int word = Scanner::SearchReservedWord(yytext);
							if(word)
								return SHOW_TOKEN(word);

							yylval.identifier = new string(yytext);
							return SHOW_TOKEN(IDENTIFIER);
						}
"["						return SHOW_TOKEN(yytext[0]);
"]"						return SHOW_TOKEN(yytext[0]);
[:{}();.,]				return SHOW_TOKEN(yytext[0]);
[!+-><=]				return SHOW_TOKEN(yytext[0]);
"*"						return SHOW_TOKEN(yytext[0]);
"/"						return SHOW_TOKEN(yytext[0]);

.						Scanner::Error("Unknown token -> " + to_string(yytext[0]));

%%

int yywrap()
{
	return 1;
}

int Scanner::lineNumber = 1;
string Scanner::stringConstant = "";
map<string, int> Scanner::reservedWords;


void Scanner::Init(const string& _fileName)
{
	yyin = fopen(_fileName.c_str(), "r");
	if(!yyin)
		Error("File " + _fileName + " cannot be opened!");

	lineNumber = 1;
    stringConstant = "";
	reservedWords.clear();

    reservedWords.insert(pair<string, int>("if",         IF));
    reservedWords.insert(pair<string, int>("else",       ELSE));
    reservedWords.insert(pair<string, int>("while",      WHILE));
    reservedWords.insert(pair<string, int>("for",        FOR));
    reservedWords.insert(pair<string, int>("class",      CLASS));
    reservedWords.insert(pair<string, int>("interface",  INTERFACE));
    reservedWords.insert(pair<string, int>("extends",    EXTENDS));
    reservedWords.insert(pair<string, int>("implements", IMPLEMENTS));
    reservedWords.insert(pair<string, int>("new",        NEW));
    reservedWords.insert(pair<string, int>("this",       ILTHIS));
    reservedWords.insert(pair<string, int>("read",       READ));
    reservedWords.insert(pair<string, int>("write",      WRITE));
    reservedWords.insert(pair<string, int>("return",     RETURN));
    reservedWords.insert(pair<string, int>("public",     PUBLIC));
    reservedWords.insert(pair<string, int>("protected",  PROTECTED));
    reservedWords.insert(pair<string, int>("private",    PRIVATE));
    reservedWords.insert(pair<string, int>("static",     STATIC));
    reservedWords.insert(pair<string, int>("null",       ILNULL));
    reservedWords.insert(pair<string, int>("cast",       CAST));
}

int Scanner::SearchReservedWord(const string& _identifier)
{
	map<string, int>::iterator i = reservedWords.find(_identifier);
	
    if(i != reservedWords.end())
		return i->second;
	
    return 0;
}

void Scanner::NewStringConstant()
{
	stringConstant = "";
}

void Scanner::AddStringConstant(const char* _text)
{
	stringConstant += _text;
}

string Scanner::GetStringConstant()
{
	return stringConstant;
}

void Scanner::NewLine()
{
	lineNumber++;
}

int Scanner::GetLineNumber()
{
	return lineNumber;
}

void Scanner::Error(const string& _error)
{
	ErrorHandler::LexicalError(_error, lineNumber);
}

#ifdef _DEBUG

#include <fstream>
ofstream t("tokens.txt");
ostream& Scanner::out = t;

int Scanner::ShowToken(int _token)
{
	switch(_token)
	{
        //
	    // Reserved words and types
        //
	    case IF			:out << "if"         << endl; break;
	    case ELSE		:out << "else"       << endl; break;
	    case WHILE		:out << "while"      << endl; break;
	    case FOR		:out << "for"        << endl; break;
	    case CAST		:out << "cast"       << endl; break;
	    case CLASS		:out << "class"      << endl; break;
	    case INTERFACE	:out << "interface"  << endl; break;
	    case EXTENDS	:out << "extends"    << endl; break;
	    case IMPLEMENTS	:out << "implements" << endl; break;
	    case NEW		:out << "new"        << endl; break;
	    case ILTHIS		:out << "this"       << endl; break;
	    case READ		:out << "read"       << endl; break;
	    case WRITE		:out << "write"      << endl; break;
	    case RETURN		:out << "return"     << endl; break;
	    case PUBLIC		:out << "public"     << endl; break;
	    case PROTECTED	:out << "protected"  << endl; break;
	    case PRIVATE	:out << "private"    << endl; break;
	    case STATIC		:out << "static"     << endl; break;
	    case ILNULL		:out << "null"       << endl; break;
        //
	    // Constants and operators
        //
	    case BOOL_CTE	:out << "BOOL_CTE("   << yylval.boolValue           << ")" << endl;	break;
	    case CHAR_CTE	:out << "CHAR_CTE("   << yylval.charValue           << ")" << endl;	break;
	    case INT_CTE	:out << "INT_CTE("    << yylval.intValue            << ")" << endl;	break;
	    case REAL_CTE	:out << "REAL_CTE("   << yylval.realValue           << ")" << endl;	break;
	    case STRING_CTE	:out << "STRING_CTE(" << yylval.identifier->c_str() << ")" << endl;	break;
	    case IDENTIFIER	:out << "IDENTIFIER(" << yylval.identifier->c_str() << ")" << endl;	break;
	    case AND		:out << "&&" << endl; break;
	    case OR			:out << "||" << endl; break;
	    case EQ			:out << "==" << endl; break;
	    case NE			:out << "!=" << endl; break;
	    //
        // One-char tokens
        //
	    case '['		:out << "[" << endl; break;
	    case ']'		:out << "]" << endl; break;
	    case ':'		:out << ":" << endl; break;
	    case '{'		:out << "{" << endl; break;
	    case '}'		:out << "}" << endl; break;
	    case '('		:out << "(" << endl; break;
	    case ')'		:out << ")" << endl; break;
	    case ';'		:out << ";" << endl; break;
	    case '.'		:out << "." << endl; break;
	    case ','		:out << "," << endl; break;
	    case '!'		:out << "!" << endl; break;
	    case '+'		:out << "+" << endl; break;
	    case '-'		:out << "-" << endl; break;
	    case '>'		:out << ">" << endl; break;
	    case '<'		:out << "<" << endl; break;
	    case '='		:out << "=" << endl; break;
	    case '/'		:out << "/" << endl; break;
	    case '*'		:out << "*" << endl; break;
	    //
        // EOF
        //
        case 0			:break;
        //
        // Error
        //
	    default : Scanner::Error("Unknown Token provided by Lex = " + to_string(_token));
	}
	return _token;
}

#endif
