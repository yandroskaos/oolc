%{
#include <string>
#include <vector>
using namespace std;

#include <utils/conversion.h>
#include <symbols/symbols.h>
#include <errors/handler.h>
#include <ast/node.h>
#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>
#include <ast/parser_nodes.h>
#include <ast/builder.h>
#include "parser.h"
#include "scanner.h"

extern int yylex(void);
int yyparse();
int yyerror(char* _error);

#ifdef _DEBUG
	#define RULE(_ruleName) Parser::Rule(_ruleName)
#else
	#define RULE(_ruleName)
#endif
%}

%union
{
	bool             boolValue;
	char             charValue;
 	int              intValue;
	double           realValue;
	string*          identifier;
	AST::Node*       node;
	AST::Collection* collection;
}

%token <intValue>	   	INT_CTE
%token <identifier>		STRING_CTE IDENTIFIER
%token <realValue>      REAL_CTE
%token <charValue>  	CHAR_CTE
%token <boolValue>		BOOL_CTE
%token ILTHIS ILNULL
%token IF ELSE WHILE FOR READ WRITE RETURN
%token CLASS INTERFACE EXTENDS IMPLEMENTS NEW
%token PUBLIC PROTECTED PRIVATE STATIC CAST

%right '='
%left OR
%left AND
%left EQ NE
%left '>' '<'
%left '+' '-'
%left '*' '/'
%right '!'
%left '.'
%left NEG	
%nonassoc PREC
%left '[' ']'
%left '(' ')'
%nonassoc ELSE

%type<identifier> R_type
%type<intValue>   R_brackets_decl
%type<collection> R_brackets_def		//ExpressioNode
%type<collection> R_argument_decl_list 	//Parsing::StringNode
%type<collection> R_argument_def_list  	//Parsing::DeclarationNode
%type<collection> R_argument_call_list	//ExpressionNode
%type<node>       R_decl				//Parsing::DeclarationNode
%type<collection> R_identifiers			//Parsing::InitNode
%type<node>       R_program				//ProgramNode
%type<collection> R_classes				//ClassNode | InterfaceNode
%type<node>       R_interface			//InterfaceNode
%type<identifier> R_interface_header
%type<collection> R_interface_body		//PrototypeNode
%type<node>       R_prototype	        //PrototypeNode
%type<node>       R_class				//ClassNode
%type<identifier> R_class_header
%type<collection> R_interface_list		//Parsing::StringNode
%type<collection> R_implements			//Parsing::StringNode
%type<identifier> R_extends
%type<collection> R_class_body			//ClassAttributeNode | ClassConstructorNode | ClassMethodNode | ClassPropertyNode
%type<collection> R_attributes			//AttributeNode
%type<node>       R_constructor			//ConstructorNode
%type<node>       R_method				//MethodNode
%type<node>       R_code				//BlockStatementNode
%type<collection> R_statements			//BlockStatementNode
%type<node>       R_statement			//AnyStatementNode
%type<node>       R_else				//BlockStatementNode
%type<node>       R_expresion			//ExpressionNode
%type<collection> R_slots				//AnySlotNode
%type<node>       R_slot				//AnySlotNode

%start R_program

%%

R_protection:
	PUBLIC
	{
		RULE("R_protection -> PUBLIC");
		AST::Builder::SetAccess(Symbols::Access::Public);
	}
|	PROTECTED
	{
		RULE("R_protection -> PROTECTED");
		AST::Builder::SetAccess(Symbols::Access::Protected);
	}
|	PRIVATE
	{
		RULE("R_protection -> PRIVATE");
		AST::Builder::SetAccess(Symbols::Access::Private);
	}
;

R_static:
	{
		RULE("R_static -> <EMPTY>");
		AST::Builder::SetStatic(false);
	}
|	STATIC
	{
		RULE("R_static -> STATIC");
		AST::Builder::SetStatic(true);
	}
;

R_access: 
	R_static R_protection
;

R_type:
	IDENTIFIER
	{
		RULE("R_type -> IDENTIFIER");
		$$ = $1;
	}
|	IDENTIFIER R_brackets_decl
	{
		RULE("R_type -> IDENTIFIER R_brackets_decl");
		*$1 = to_string($2) + *$1;
		$$ = $1;
	}
;

R_brackets_decl:
	'[' ']'
	{
		RULE("R_brackets_decl -> []");
		$$ = 1;
	}
|	R_brackets_decl '[' ']'
	{
		RULE("R_brackets_decl -> R_brackets_decl []");
		$$ = $1 + 1;
	}
;

R_brackets_def:
	'[' R_expresion ']'
	{
		RULE("R_brackets_def -> [ R_expresion ]");
		$$ = AST::Builder::BuildCollection($2);
	}
|	R_brackets_def '[' R_expresion ']'
	{
		RULE("R_brackets_def -> R_brackets_def [ R_expresion ]");
		$$ = AST::Builder::AddCollection($1, $3);
	}
;

R_argument_decl_list:
	/*EMPTY*/
	{
		RULE("R_argument_decl_list -> <EMPTY>");
		$$ = 0;
	}
|	R_type
	{
		RULE("R_argument_decl_list -> R_type");
		$$ = AST::Builder::BuildCollection(new Parsing::StringNode($1));
	}
|	R_type IDENTIFIER
	{
		RULE("R_argument_decl_list -> R_type IDENTIFIER");
		$$ = AST::Builder::BuildCollection(new Parsing::StringNode($1));
		delete $2;
	}
|	R_argument_decl_list ',' R_type
	{
		RULE("R_argument_decl_list -> R_argument_decl_list , R_type");
		$$ = AST::Builder::AddCollection($1, new Parsing::StringNode($3));
	}
|	R_argument_decl_list ',' R_type IDENTIFIER
	{
		RULE("R_argument_decl_list -> R_argument_decl_list , R_type IDENTIFIER");
		$$ = AST::Builder::AddCollection($1, new Parsing::StringNode($3));
		delete $4;
	}
;

R_argument_def_list:
	/*EMPTY*/
	{
		RULE("R_argument_def_list -> <EMPTY>");
		$$ = 0;
	}
|	R_decl
	{
		RULE("R_argument_def_list -> R_decl");
		$$ = AST::Builder::BuildCollection($1);
	}
|	R_argument_def_list ',' R_decl
	{
		RULE("R_argument_def_list -> R_argument_def_list , R_decl");
		$$ = AST::Builder::AddCollection($1, $3);
	}
;

R_argument_call_list:
	/*EMPTY*/
	{
		RULE("R_argument_call_list -> <EMPTY>");
		$$ = 0;
	}
|	R_expresion
	{
		RULE("R_argument_call_list -> R_expresion");
		$$ = AST::Builder::BuildCollection($1);
	}
|	R_argument_call_list ',' R_expresion
	{
		RULE("R_argument_call_list -> R_argument_call_list , R_expresion");
		$$ = AST::Builder::AddCollection($1, $3);
	}
;

R_decl:
	R_type IDENTIFIER
	{
		RULE("R_decl -> R_type IDENTIFIER");
		$$ = new Parsing::DeclarationNode($1, $2);
		Parser::PushLine();
	}
;

R_identifiers:
	IDENTIFIER
	{
		RULE("R_identifiers -> IDENTIFIER");
		Parsing::InitNode* n = new Parsing::InitNode($1, nullptr);
		n->SetLine(Scanner::GetLineNumber());
		$$ = AST::Builder::BuildCollection(n);
	}
|	IDENTIFIER {Parser::PushLine();} '=' R_expresion
	{
		RULE("R_identifiers -> IDENTIFIER = R_expresion");
		Parsing::InitNode* n = new Parsing::InitNode($1, $4);
		n->SetLine(Parser::PopLine());
		$$ = AST::Builder::BuildCollection(n);
	}
|	R_identifiers ',' IDENTIFIER
	{
		RULE("R_identifiers -> R_identifiers , IDENTIFIER");
		Parsing::InitNode* n = new Parsing::InitNode($3, nullptr);
		n->SetLine(Scanner::GetLineNumber());
		$$ = AST::Builder::AddCollection($1, n);
	}
|	R_identifiers ',' IDENTIFIER {Parser::PushLine();} '=' R_expresion
	{
		RULE("R_identifiers -> R_identifiers , IDENTIFIER = R_expresion");
		Parsing::InitNode* n = new Parsing::InitNode($3, $6);
		n->SetLine(Parser::PopLine());
		$$ = AST::Builder::AddCollection($1, n);
	}
;

/*------------------------------------------------------------*/
R_program:
	R_classes
	{
		RULE("R_program -> R_classes");
		$$ = AST::Builder::Program($1);
	}
;

R_classes:
	R_class
	{
		RULE("R_classes -> R_class");
		$$ = AST::Builder::BuildCollection($1);
	}
|	R_interface
	{
		RULE("R_classes -> R_interface");
		$$ = AST::Builder::BuildCollection($1);
	}
|	R_classes R_class
	{
		RULE("R_classes -> R_classes R_class");
		$$ = AST::Builder::AddCollection($1, $2);
	}
|	R_classes R_interface
	{
		RULE("R_classes -> R_classes R_interface");
		$$ = AST::Builder::AddCollection($1, $2);
	}
;

/*------------------------------------------------------------*/
R_interface:
	R_interface_header '{' R_interface_body '}'
	{
		RULE("R_interface -> R_interface_header { R_interface_body }");
		$$ = AST::Builder::Interface($1, $3);
		$$->SetLine(Parser::PopLine());
	}
|	R_interface_header '{' '}'
	{
		RULE("R_interface -> R_interface_header { }");
		$$ = AST::Builder::Interface($1, nullptr);
		$$->SetLine(Parser::PopLine());
	}
;

R_interface_header:
	INTERFACE IDENTIFIER
	{
		RULE("R_interface_header -> INTERFACE IDENTIFIER");
		$$ = $2;
		Parser::PushLine();
	}
;

R_interface_body:
	R_prototype
	{ 
		RULE("R_interface_body -> R_prototype");
		$$ = AST::Builder::BuildCollection($1);
	}
|	R_interface_body R_prototype
	{
		RULE("R_interface_body -> R_interface_body R_prototype");
		$$ = AST::Builder::AddCollection($1, $2);
	}
;

R_prototype:
	R_decl '(' R_argument_decl_list ')' ';'
	{
		RULE("R_prototype -> R_decl ( R_argument_decl_list ) ;");
		$$ = AST::Builder::Prototype($1, $3);
		$$->SetLine(Parser::PopLine());
	}
;

/*------------------------------------------------------------*/
R_class:
	R_class_header R_extends R_implements '{' R_class_body '}'
	{
		RULE("R_class -> R_class_header R_extends R_implements { R_class_body }");
		$$ = AST::Builder::Class($1, $2, $3, $5);
		$$->SetLine(Parser::PopLine());
	}
|	R_class_header R_extends R_implements '{' '}'
	{
		RULE("R_class -> R_class_header R_extends R_implements { }");
		$$ = AST::Builder::Class($1, $2, $3, nullptr);
		$$->SetLine(Parser::PopLine());
	}
;

R_class_header:
	CLASS IDENTIFIER
	{
		RULE("R_class_header -> CLASS IDENTIFIER");
		$$ = $2;
		Parser::PushLine();
	}
;

R_extends:
	/*EMPTY*/
	{
		RULE("R_extends -> <EMPTY>");
		$$ = nullptr;
	}
|	EXTENDS IDENTIFIER
	{
		RULE("R_extends -> EXTENDS IDENTIFIER");
		$$ = $2;
	}
;

R_implements:
	/*EMPTY*/
	{
		RULE("R_implements -> <EMPTY>");
		$$ = nullptr;
	}
|	IMPLEMENTS R_interface_list
	{
		RULE("R_implements -> IMPLEMENTS R_interface_list");
		$$ = $2;
	}
;

R_interface_list:
	IDENTIFIER
	{
		RULE("R_interface_list -> IDENTIFIER");
		$$ = AST::Builder::BuildCollection(new Parsing::StringNode{$1});
	}
|	R_interface_list ',' IDENTIFIER
	{
		RULE("R_interface_list -> R_interface_list , IDENTIFIER");
		$$ = AST::Builder::AddCollection($1, new Parsing::StringNode{$3});
	}
;

R_class_body:
	R_access R_attributes
	{
		RULE("R_class_body -> R_access R_attributes");
		$$ = $2;
	}
|	R_access R_constructor
	{
		RULE("R_class_body -> R_access R_constructor");
		$$ = AST::Builder::BuildCollection($2);
	}
|	R_access R_method
	{
		RULE("R_class_body -> R_access R_method");
		$$ = AST::Builder::BuildCollection($2);
	}
|	R_class_body R_access R_attributes
	{
		RULE("R_class_body -> R_class_body R_access R_attributes");
		$$ = AST::Builder::MergeCollection($1, $3);
	}
|	R_class_body R_access R_constructor
	{
		RULE("R_class_body -> R_class_body R_access R_constructor");
		$$ = AST::Builder::AddCollection($1, $3);
	}
|	R_class_body R_access R_method
	{
		RULE("R_class_body -> R_class_body R_access R_method");
		$$ = AST::Builder::AddCollection($1, $3);
	}
;

R_attributes:
	R_type R_identifiers ';'
	{
		RULE("R_attributes -> R_type R_identifiers ;");
		$$ = AST::Builder::Attributes($1, $2);
	}
;

R_constructor:
	IDENTIFIER {Parser::PushLine();} '(' R_argument_def_list ')' '{' R_code '}'
	{
		RULE("R_constructor -> IDENTIFIER ( R_argument_def_list ) { R_code }");
		$$ = AST::Builder::Constructor($1, $4, $7);
		$$->SetLine(Parser::PopLine());
	}
;

R_method:
	R_decl '(' R_argument_def_list ')' '{' R_code '}'
	{
		RULE("R_method -> R_decl ( R_argument_def_list ) { R_code } ");
		$$ = AST::Builder::Method($1, $3, $6);
		$$->SetLine(Parser::PopLine());
	}
;

/*------------------------------------------------------------*/
R_code: 
	/*EMPTY*/
	{
		RULE("R_code -> <EMPTY>");
		$$ = new AST::BlockStatementNode();
		$$->SetLine(Scanner::GetLineNumber());
	}
|	R_statements
	{
		RULE("R_code -> R_statements");
		int line = $1->at(0)->GetLine();
		$$ = AST::Builder::MakeBlock($1);
		$$->SetLine(line);
	}
;

/*---------------------------------------------------------------------------------------------------------------------*/
R_statements:
	R_statement
	{
		RULE("R_statements -> R_statement");
		$$ = AST::Builder::BuildCollection($1);
	}
|	R_statements R_statement
	{
		RULE("R_statements -> R_statements R_statement");
		$$ = AST::Builder::AddCollection($1, $2);
	}
;

/*---------------------------------------------------------------------------------------------------------------------*/
R_statement:
	'{' R_statements '}'
	{
		RULE("R_statement -> { R_statements }");
		int line = $2->at(0)->GetLine();
		$$ = AST::Builder::MakeBlock($2);
		$$->SetLine(line);
	}
|	';'
	{
		RULE("R_statement -> ;");
		$$ = new AST::EmptyStatementNode();
		$$->SetLine(Scanner::GetLineNumber());
	}
|	WRITE {Parser::PushLine();} R_expresion ';'
	{
		RULE("R_statement -> WRITE R_expresion ;");
		$$ = new AST::WriteStatementNode($3);
		$$->SetLine(Parser::PopLine());
	}
|	READ {Parser::PushLine();} R_slots ';'
	{
		RULE("R_statement -> READ R_slots ;");
		AST::Node* slot = AST::Builder::CreateSlot($3);
		$$ = new AST::ReadStatementNode(slot);
		$$->SetLine(Parser::PopLine());
	}
|	IF {Parser::PushLine();} '(' R_expresion ')' R_statement R_else %prec PREC
	{
		RULE("R_statement -> IF ( R_expresion ) R_statement R_else");
		$$ = new AST::IfElseStatementNode($4, AST::Builder::ForceBlock($6), $7);
		$$->SetLine(Parser::PopLine());
	}
|	WHILE {Parser::PushLine();} '(' R_expresion ')' R_statement
	{
		RULE("R_statement -> WHILE ( R_expresion ) R_statement");
		$$ = new AST::WhileStatementNode($4, AST::Builder::ForceBlock($6));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' R_expresion ';' R_expresion ';' R_expresion ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR ( R_expresion ; R_expresion ; R_expresion ) R_statement");
		$$ = new AST::ForStatementNode(
			$3, 
			$5,
			$7,
			AST::Builder::ForceBlock($10));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' R_expresion ';' R_expresion ';' ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR ( R_expresion ; R_expresion ;  ) R_statement");
		$$ = new AST::ForStatementNode(
			$3, 
			$5,
			nullptr,
			AST::Builder::ForceBlock($9));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' R_expresion ';' ';' R_expresion ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR ( R_expresion ;  ; R_expresion ) R_statement");
		$$ = new AST::ForStatementNode(
			$3, 
			nullptr,
			$6,
			AST::Builder::ForceBlock($9));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' ';' R_expresion ';' R_expresion ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR ( ; R_expresion ; R_expresion ) R_statement");
		$$ = new AST::ForStatementNode(
			nullptr, 
			$4,
			$6,
			AST::Builder::ForceBlock($9));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' R_expresion ';' ';' ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR ( R_expresion ;  ;  ) R_statement");
		$$ = new AST::ForStatementNode(
			$3, 
			nullptr,
			nullptr,
			AST::Builder::ForceBlock($8));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' ';' R_expresion ';' ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR (  ; R_expresion ;  ) R_statement");
		$$ = new AST::ForStatementNode(
			nullptr, 
			$4,
			nullptr,
			AST::Builder::ForceBlock($8));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' ';' ';' R_expresion ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR (  ;  ; R_expresion ) R_statement");
		$$ = new AST::ForStatementNode(
			nullptr, 
			nullptr,
			$5,
			AST::Builder::ForceBlock($8));
		$$->SetLine(Parser::PopLine());
	}
|	FOR '(' ';' ';' ')' {Parser::PushLine();} R_statement
	{
		RULE("R_statement -> FOR (  ;  ;  ) R_statement");
		$$ = new AST::ForStatementNode(
			nullptr, 
			nullptr,
			nullptr,
			AST::Builder::ForceBlock($7));
		$$->SetLine(Parser::PopLine());
	}
|	RETURN {Parser::PushLine();} R_expresion ';' 
	{
		RULE("R_statement -> RETURN R_expresion ; ");
		$$ = new AST::ReturnStatementNode($3);
		$$->SetLine(Parser::PopLine());
	}
|	RETURN ';'
	{
		RULE("R_statement -> RETURN ;");
		$$ = new AST::ReturnStatementNode(nullptr);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	R_type R_identifiers ';'
	{
		RULE("R_statement -> R_type R_identifiers ;");
		$$ = AST::Builder::Variables($1, $2);
	}
|	R_expresion ';'
	{
		RULE("R_statement -> R_expresion ;");
		$$ = new AST::ExpressionStatementNode($1);
		$$->SetLine(Scanner::GetLineNumber());
	}
;

R_else:
	/*EMPTY*/ %prec PREC
	{
		RULE("R_else -> <EMPTY>");
		$$ = nullptr;
	}
|	ELSE R_statement
	{
		RULE("R_else -> ELSE R_statement");
		$$ = AST::Builder::ForceBlock($2);
	}
;

/*---------------------------------------------------------------------------------------------------------------------*/
R_expresion:
	ILNULL
	{
		RULE("R_expresion -> ILNULL");
		$$ = new AST::NullExprNode();
		$$->SetLine(Scanner::GetLineNumber());
	}
|	BOOL_CTE
	{
		RULE("R_expresion -> BOOL_CTE");
		$$ = new AST::BoolCteExprNode($1);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	CHAR_CTE
	{
		RULE("R_expresion -> CHAR_CTE");
		$$ = new AST::CharCteExprNode($1);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	INT_CTE 
	{
		RULE("R_expresion -> INT_CTE");
		$$ = new AST::IntCteExprNode($1);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	REAL_CTE
	{
		RULE("R_expresion -> REAL_CTE");
		$$ = new AST::RealCteExprNode($1);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	STRING_CTE
	{
		RULE("R_expresion -> STRING_CTE");
		$$ = new AST::StringCteExprNode(*$1);
		delete $1;
		$$->SetLine(Scanner::GetLineNumber());
	}
|	'(' R_expresion ')'
	{
		RULE("R_expresion -> ( R_expresion )");
		$$ = $2;
	}
|	R_expresion '>' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion > R_expresion");
		$$ = new AST::GreaterExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion '<' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion < R_expresion");
		$$ = new AST::LesserExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion EQ {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion EQ R_expresion");
		$$ = new AST::EqualExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion NE {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion NE R_expresion");
		$$ = new AST::NotEqualExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion AND {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion AND R_expresion");
		$$ = new AST::AndExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion OR {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion OR R_expresion");
		$$ = new AST::OrExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion '+' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion + R_expresion");
		$$ = new AST::PlusExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion '-' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion - R_expresion");
		$$ = new AST::MinusExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion '*' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion * R_expresion");
		$$ = new AST::MulExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	R_expresion '/' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_expresion / R_expresion");
		$$ = new AST::DivExprNode($1, $4);
		$$->SetLine(Parser::PopLine());
	}
|	'!' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> ! R_expresion");
		$$ = new AST::NotExprNode($3);
		$$->SetLine(Parser::PopLine());
	}
|	'-' {Parser::PushLine();} R_expresion %prec NEG
	{
		RULE("R_expresion -> - R_expresion");
		$$ = new AST::MinusUnaryExprNode($3);
		$$->SetLine(Parser::PopLine());
	}
|	CAST {Parser::PushLine();} '<' R_type '>' '(' R_expresion ')'
	{
		RULE("R_expresion -> CAST < R_type > ( R_expresion )");
		$$ = new AST::CastExprNode(*$4, $7);
		delete $4;
		$$->SetLine(Parser::PopLine());
	}
|	NEW IDENTIFIER {Parser::PushLine();} '(' R_argument_call_list ')'
	{
		RULE("R_expresion -> NEW IDENTIFIER ( R_argument_call_list )");
		$$ = AST::Builder::NewExpression($2, $5);
		$$->SetLine(Parser::PopLine());
	}
|	NEW IDENTIFIER R_brackets_def
	{
		RULE("R_expresion -> NEW IDENTIFIER R_brackets_def");
		$$ = AST::Builder::NewArrayExpression($2, $3);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	R_slots
	{
		RULE("R_expresion -> R_slots");
		$$ = AST::Builder::CreateSlot($1);
	}
|	R_slots '=' {Parser::PushLine();} R_expresion
	{
		RULE("R_expresion -> R_slots = R_expresion");
		$$ = new AST::AssignmentExprNode(AST::Builder::CreateSlot($1), $4);
		$$->SetLine(Parser::PopLine());
	}
;

R_slots:
	ILTHIS
	{
		RULE("R_slots -> ILTHIS");
		AST::ThisSlotNode* n = new AST::ThisSlotNode();
		n->SetLine(Scanner::GetLineNumber());
		$$ = AST::Builder::BuildCollection(n);
	}
|	R_slot
	{
		RULE("R_slots -> R_slot");
		$$ = AST::Builder::BuildCollection($1);
	}
|	R_slots '.' R_slot
	{
		RULE("R_slots -> R_slots . R_slot");
		$$ = AST::Builder::AddCollection($1, $3);
	}
;

R_slot:
	IDENTIFIER
	{
		RULE("R_slot -> IDENTIFIER");
		$$ = AST::Builder::IdentifierSlot($1, false, nullptr, nullptr);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	IDENTIFIER '(' R_argument_call_list ')'
	{
		RULE("R_slot -> IDENTIFIER ( R_argument_call_list )");
		$$ = AST::Builder::IdentifierSlot($1, true, $3, nullptr);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	IDENTIFIER '(' R_argument_call_list ')' R_brackets_def
	{
		RULE("R_slot -> IDENTIFIER ( R_argument_call_list ) R_brackets_def");
		$$ = AST::Builder::IdentifierSlot($1, true, $3, $5);
		$$->SetLine(Scanner::GetLineNumber());
	}
|	IDENTIFIER R_brackets_def
	{
		RULE("R_slot -> IDENTIFIER R_brackets_def");
		$$ = AST::Builder::IdentifierSlot($1, false, nullptr, $2);
		$$->SetLine(Scanner::GetLineNumber());
	}
;

%%

int yyerror(char* _error)
{
	Parser::Error(_error);
	return 0;
}

stack<int> Parser::lines;

void Parser::Init(const string& _fileName)
{
	//lines.clear();
	while(!lines.empty())
		lines.pop();

	Scanner::Init(_fileName);
}

void Parser::Parse(const string& _fileName)
{
	Init(_fileName);
	yyparse();
}
	
int Parser::PopLine()
{
	int line = lines.top();
	lines.pop();

	return line;
}

void Parser::PushLine()
{
	lines.push(Scanner::GetLineNumber());
}

void Parser::Error(const string& _error)
{
	ErrorHandler::SyntaxError(_error, Scanner::GetLineNumber());
}

#ifdef _DEBUG
#include <fstream>
ofstream r("rules.txt");
ostream& Parser::out = r;

void Parser::Rule(const string& _ruleName)
{
	out << "Reducing using rule " << _ruleName.c_str() << std::endl;
}

#endif
