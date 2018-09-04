/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_HOME_PABLO_DOCUMENTS_CODE_OOLC_SRC_PARSING_TOKENS_H_INCLUDED
# define YY_YY_HOME_PABLO_DOCUMENTS_CODE_OOLC_SRC_PARSING_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_CTE = 258,
    STRING_CTE = 259,
    IDENTIFIER = 260,
    REAL_CTE = 261,
    CHAR_CTE = 262,
    BOOL_CTE = 263,
    ILTHIS = 264,
    ILNULL = 265,
    IF = 266,
    ELSE = 267,
    WHILE = 268,
    FOR = 269,
    READ = 270,
    WRITE = 271,
    RETURN = 272,
    CLASS = 273,
    INTERFACE = 274,
    EXTENDS = 275,
    IMPLEMENTS = 276,
    NEW = 277,
    PUBLIC = 278,
    PROTECTED = 279,
    PRIVATE = 280,
    STATIC = 281,
    CAST = 282,
    OR = 283,
    AND = 284,
    EQ = 285,
    NE = 286,
    NEG = 287,
    PREC = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{


	bool             boolValue;
	char             charValue;
 	int              intValue;
	double           realValue;
	string*          identifier;
	AST::Node*       node;
	AST::Collection* collection;


};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_PABLO_DOCUMENTS_CODE_OOLC_SRC_PARSING_TOKENS_H_INCLUDED  */
