/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */


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



# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tokens.h".  */
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

/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   746

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  260

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,     2,     2,     2,     2,     2,
      45,    46,    37,    35,    47,    36,    40,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      34,    28,    33,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    29,    30,    31,    32,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   106,   111,   119,   123,   131,   135,   140,
     149,   154,   162,   167,   176,   180,   185,   191,   196,   206,
     210,   215,   224,   228,   233,   241,   250,   257,   257,   264,
     271,   271,   282,   290,   295,   300,   305,   314,   320,   329,
     338,   343,   351,   361,   367,   376,   386,   390,   399,   403,
     411,   416,   424,   429,   434,   439,   444,   449,   457,   465,
     465,   474,   485,   490,   501,   506,   515,   522,   528,   528,
     534,   534,   541,   541,   547,   547,   553,   553,   563,   563,
     573,   573,   583,   583,   593,   593,   603,   603,   613,   613,
     623,   623,   633,   633,   639,   645,   650,   659,   664,   673,
     679,   685,   691,   697,   703,   710,   715,   715,   721,   721,
     727,   727,   733,   733,   739,   739,   745,   745,   751,   751,
     757,   757,   763,   763,   769,   769,   775,   775,   781,   781,
     787,   787,   794,   794,   800,   806,   811,   811,   820,   827,
     832,   840,   846,   852,   858
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_CTE", "STRING_CTE", "IDENTIFIER",
  "REAL_CTE", "CHAR_CTE", "BOOL_CTE", "ILTHIS", "ILNULL", "IF", "ELSE",
  "WHILE", "FOR", "READ", "WRITE", "RETURN", "CLASS", "INTERFACE",
  "EXTENDS", "IMPLEMENTS", "NEW", "PUBLIC", "PROTECTED", "PRIVATE",
  "STATIC", "CAST", "'='", "OR", "AND", "EQ", "NE", "'>'", "'<'", "'+'",
  "'-'", "'*'", "'/'", "'!'", "'.'", "NEG", "PREC", "'['", "']'", "'('",
  "')'", "','", "'{'", "'}'", "';'", "$accept", "R_protection", "R_static",
  "R_access", "R_type", "R_brackets_decl", "R_brackets_def",
  "R_argument_decl_list", "R_argument_def_list", "R_argument_call_list",
  "R_decl", "R_identifiers", "$@1", "$@2", "R_program", "R_classes",
  "R_interface", "R_interface_header", "R_interface_body", "R_prototype",
  "R_class", "R_class_header", "R_extends", "R_implements",
  "R_interface_list", "R_class_body", "R_attributes", "R_constructor",
  "$@3", "R_method", "R_code", "R_statements", "R_statement", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "$@16", "R_else", "R_expresion", "$@17", "$@18", "$@19", "$@20",
  "$@21", "$@22", "$@23", "$@24", "$@25", "$@26", "$@27", "$@28", "$@29",
  "$@30", "$@31", "R_slots", "R_slot", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    61,   283,
     284,   285,   286,    62,    60,    43,    45,    42,    47,    33,
      46,   287,   288,    91,    93,    40,    41,    44,   123,   125,
      59
};
# endif

#define YYPACT_NINF -98

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-98)))

#define YYTABLE_NINF -60

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      44,     0,     8,    42,    44,   -98,    17,   -98,    24,   -98,
     -98,   -98,   -98,   -98,    -3,    63,    49,    40,   -98,    87,
      43,    -2,   -98,   -98,    91,    54,    56,    61,   -98,   117,
     -98,   -98,   -98,    81,   -20,   -98,    85,   118,    20,   125,
     -98,   -98,    36,   126,   -17,   -98,   -98,    86,   117,   -98,
     -98,   -98,   -98,   -98,   -24,   128,    90,   -98,   -98,   -98,
     -98,   126,   -98,   135,    93,   -21,   -36,   117,   -98,   -98,
     -98,   -98,   117,   119,   141,   -98,    39,   -98,    48,   451,
     121,   102,   117,   104,   -98,   -98,    -5,   -98,   -98,   -98,
     -98,   -98,   148,   -98,   -98,   -98,   451,   708,   -13,   -98,
     127,   226,   -98,   226,   451,   451,   111,   114,   130,   451,
     451,   532,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   155,   451,    -4,   -98,   -98,   116,   -98,
     -98,   123,   226,   -98,   171,   129,   226,   -98,    19,   147,
     676,    52,   708,   451,   111,   132,   117,   -98,   -98,   -98,
     451,   451,   451,   451,   451,   451,   451,   451,   451,   451,
     451,   -98,   708,   426,   134,   145,   251,     7,   451,   -98,
     451,   178,   169,   -27,   -98,   -98,   -98,   -98,   -98,   114,
     451,   692,   451,   165,   489,   175,   133,   133,    -1,    -1,
      83,    83,   -98,   -98,   708,   451,   451,   276,    77,   -32,
     468,   478,   -98,   -98,   111,   708,   -98,    79,   154,   550,
     568,   326,   500,   301,   -98,   -98,   -98,   -98,   451,   226,
     226,   -98,   586,   351,   376,   510,   604,   189,   -98,   226,
     -98,   -98,   622,   -98,   640,   401,   -98,   226,   -98,   -98,
     226,   226,   -98,   226,   -98,   -98,   658,   -98,   -98,   -98,
     226,   -98,   226,   226,   -98,   -98,   -98,   -98,   226,   -98
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    32,    34,     0,    33,    46,    45,
      39,     1,    36,    35,     0,     0,    48,     8,    38,     0,
       0,     0,    40,    47,     0,     0,     0,     9,    25,    14,
      37,    41,    50,    49,     5,    10,     0,    15,     0,     0,
       6,    44,     0,     0,     5,    11,    16,     0,     0,    51,
       2,     3,     4,     7,     8,     0,     0,    52,    53,    54,
      43,     0,    42,    17,     0,    26,     0,    19,    55,    56,
      57,    18,    19,     0,     0,    58,     0,    20,     0,     0,
      29,     0,     0,     0,   102,   104,   141,   103,   101,   100,
     138,    99,     0,   130,   128,   126,     0,    28,   135,   139,
       0,    62,    21,    62,     0,    22,   144,   132,     0,     0,
       0,     0,   116,   114,   110,   112,   106,   108,   118,   120,
     122,   124,   136,     0,     0,   141,    72,    74,     0,    70,
      68,    92,     0,    67,     0,     0,    63,    64,     0,     0,
       0,     0,    23,     0,   134,     0,     0,   129,   127,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   140,    31,     0,     0,     0,     0,     0,     0,    94,
       0,     0,    26,     0,    61,    65,    96,    60,    12,   142,
       0,     0,    22,     0,   117,   115,   111,   113,   107,   109,
     119,   121,   123,   125,   137,     0,     0,     0,     0,     0,
       0,     0,    66,    95,   143,    24,    13,     0,     0,     0,
       0,     0,     0,     0,    71,    69,    93,   133,     0,     0,
       0,    90,     0,     0,     0,     0,     0,    97,    75,     0,
      88,    86,     0,    84,     0,     0,   131,     0,    73,    91,
       0,     0,    82,     0,    80,    78,     0,    98,    89,    87,
       0,    85,     0,     0,    76,    83,    81,    79,     0,    77
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -98,   -98,   -98,   158,    76,   -98,   -97,   -98,   131,    22,
     -39,    82,   -98,   -98,   -98,   -98,   211,   -98,   -98,   197,
     215,   -98,   -98,   -98,   -98,   -98,   159,   160,   -98,   163,
     122,   106,   -78,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -79,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,    78,   124
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    53,    42,    43,   134,    27,   106,    38,    76,   141,
      20,    66,    73,   100,     3,     4,     5,     6,    21,    22,
       7,     8,    16,    25,    33,    44,    57,    58,    64,    59,
     135,   136,   137,   168,   167,   164,   165,   258,   253,   252,
     250,   243,   241,   240,   229,   170,   238,   138,   154,   155,
     152,   153,   151,   150,   156,   157,   158,   159,   110,   109,
     108,   145,   160,    98,    99
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      97,    -8,    17,    17,    56,     9,    40,   -27,   123,    40,
     144,    74,    86,    10,    75,   122,    90,   111,   214,    26,
      74,   -59,    56,   203,   -25,   140,   142,   123,    77,    41,
     147,   148,    60,    77,   118,   119,   120,   121,   104,   163,
     105,   105,    11,   102,    15,   162,    18,    30,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   175,    50,
      51,    52,     1,     2,   181,    14,    47,    48,    23,   176,
      24,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   204,    26,   140,    81,    82,   198,    29,   200,
      19,   201,    28,   175,    83,    82,    32,    19,   179,   180,
      35,   205,    34,   142,    36,    37,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   209,   210,   212,    55,
     120,   121,    17,    46,    63,   217,   180,   213,    39,    45,
      49,    54,   222,    65,   225,    67,    62,    55,    72,   226,
      71,   227,   228,    19,   232,   234,    80,    79,    19,   -30,
     101,   239,   103,   107,   143,   124,   246,   104,    19,   247,
      86,   166,   248,   249,   146,   251,   116,   117,   118,   119,
     120,   121,   255,   169,   256,   257,   172,   182,   174,   195,
     259,    84,    85,   125,    87,    88,    89,    90,    91,   126,
     196,   127,   128,   129,   130,   131,   177,   -27,   208,   218,
      92,   237,    61,    78,   207,    93,   114,   115,   116,   117,
     118,   119,   120,   121,    94,    12,   173,    95,    31,    13,
      68,    69,   183,    96,    70,   139,   132,   202,   133,    84,
      85,   125,    87,    88,    89,    90,    91,   126,   171,   127,
     128,   129,   130,   131,     0,   199,     0,   161,    92,     0,
       0,     0,     0,    93,    84,    85,    86,    87,    88,    89,
      90,    91,    94,     0,     0,    95,     0,     0,     0,     0,
       0,    96,     0,    92,   132,     0,   133,     0,    93,    84,
      85,    86,    87,    88,    89,    90,    91,    94,     0,     0,
      95,     0,     0,     0,     0,     0,    96,     0,    92,     0,
       0,   197,     0,    93,    84,    85,    86,    87,    88,    89,
      90,    91,    94,     0,     0,    95,     0,     0,     0,     0,
       0,    96,     0,    92,     0,     0,   211,     0,    93,    84,
      85,    86,    87,    88,    89,    90,    91,    94,     0,     0,
      95,     0,     0,     0,     0,     0,    96,     0,    92,     0,
       0,   224,     0,    93,    84,    85,    86,    87,    88,    89,
      90,    91,    94,     0,     0,    95,     0,     0,     0,     0,
       0,    96,   221,    92,     0,     0,     0,     0,    93,    84,
      85,    86,    87,    88,    89,    90,    91,    94,     0,     0,
      95,     0,     0,     0,     0,     0,    96,   231,    92,     0,
       0,     0,     0,    93,    84,    85,    86,    87,    88,    89,
      90,    91,    94,     0,     0,    95,     0,     0,     0,     0,
       0,    96,   233,    92,     0,     0,     0,     0,    93,    84,
      85,    86,    87,    88,    89,    90,    91,    94,     0,     0,
      95,     0,     0,     0,     0,     0,    96,   245,    92,     0,
       0,     0,     0,    93,    84,    85,    86,    87,    88,    89,
      90,    91,    94,     0,     0,    95,     0,     0,     0,     0,
      35,    96,     0,    92,     0,     0,     0,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,    94,     0,     0,
      95,     0,     0,     0,     0,     0,    96,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,   215,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   216,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
     223,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     235,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,     0,   149,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,     0,     0,     0,   219,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,     0,
       0,     0,     0,     0,   220,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,     0,     0,     0,     0,
       0,     0,   230,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,     0,     0,     0,
     236,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,     0,   242,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,     0,     0,     0,   244,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,     0,
       0,     0,     0,     0,   254,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,     0,     0,     0,     0,
     178,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,   206,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121
};

static const yytype_int16 yycheck[] =
{
      79,     5,     5,     5,    43,     5,    26,    28,    40,    26,
     107,    47,     5,     5,    50,    28,     9,    96,    50,    43,
      47,    45,    61,    50,    45,   104,   105,    40,    67,    49,
     109,   110,    49,    72,    35,    36,    37,    38,    43,    43,
      45,    45,     0,    82,    20,   124,    49,    49,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   136,    23,
      24,    25,    18,    19,   143,    48,    46,    47,     5,    50,
      21,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   179,    43,   163,    46,    47,   166,    45,   168,
      14,   170,     5,   171,    46,    47,     5,    21,    46,    47,
      44,   180,    48,   182,    43,    29,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   195,   196,   197,    43,
      37,    38,     5,     5,    48,    46,    47,    50,    47,    44,
       5,     5,   211,     5,   213,    45,    50,    61,    45,   218,
       5,   219,   220,    67,   223,   224,     5,    28,    72,    28,
      48,   229,    48,     5,    43,    28,   235,    43,    82,   237,
       5,    45,   240,   241,    34,   243,    33,    34,    35,    36,
      37,    38,   250,    50,   252,   253,     5,    45,    49,    45,
     258,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      45,    13,    14,    15,    16,    17,    49,    28,    33,    45,
      22,    12,    44,    72,   182,    27,    31,    32,    33,    34,
      35,    36,    37,    38,    36,     4,   134,    39,    21,     4,
      61,    61,   146,    45,    61,   103,    48,    49,    50,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   132,    13,
      14,    15,    16,    17,    -1,   167,    -1,   123,    22,    -1,
      -1,    -1,    -1,    27,     3,     4,     5,     6,     7,     8,
       9,    10,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    22,    48,    -1,    50,    -1,    27,     3,
       4,     5,     6,     7,     8,     9,    10,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    22,    -1,
      -1,    50,    -1,    27,     3,     4,     5,     6,     7,     8,
       9,    10,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    22,    -1,    -1,    50,    -1,    27,     3,
       4,     5,     6,     7,     8,     9,    10,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    22,    -1,
      -1,    50,    -1,    27,     3,     4,     5,     6,     7,     8,
       9,    10,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    22,    -1,    -1,    -1,    -1,    27,     3,
       4,     5,     6,     7,     8,     9,    10,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    22,    -1,
      -1,    -1,    -1,    27,     3,     4,     5,     6,     7,     8,
       9,    10,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    22,    -1,    -1,    -1,    -1,    27,     3,
       4,     5,     6,     7,     8,     9,    10,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    22,    -1,
      -1,    -1,    -1,    27,     3,     4,     5,     6,     7,     8,
       9,    10,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      44,    45,    -1,    22,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    50,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    50,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      44,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    44,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    65,    66,    67,    68,    71,    72,     5,
       5,     0,    67,    71,    48,    20,    73,     5,    49,    55,
      61,    69,    70,     5,    21,    74,    43,    56,     5,    45,
      49,    70,     5,    75,    48,    44,    43,    55,    58,    47,
      26,    49,    53,    54,    76,    44,     5,    46,    47,     5,
      23,    24,    25,    52,     5,    55,    61,    77,    78,    80,
      49,    54,    50,    55,    79,     5,    62,    45,    77,    78,
      80,     5,    45,    63,    47,    50,    59,    61,    59,    28,
       5,    46,    47,    46,     3,     4,     5,     6,     7,     8,
       9,    10,    22,    27,    36,    39,    45,    98,   114,   115,
      64,    48,    61,    48,    43,    45,    57,     5,   111,   110,
     109,    98,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    28,    40,    28,     5,    11,    13,    14,    15,
      16,    17,    48,    50,    55,    81,    82,    83,    98,    81,
      98,    60,    98,    43,    57,   112,    34,    98,    98,    46,
     104,   103,   101,   102,    99,   100,   105,   106,   107,   108,
     113,   115,    98,    43,    86,    87,    45,    85,    84,    50,
      96,    82,     5,    62,    49,    83,    50,    49,    44,    46,
      47,    98,    45,    55,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    45,    45,    50,    98,   114,
      98,    98,    49,    50,    57,    98,    44,    60,    33,    98,
      98,    50,    98,    50,    50,    50,    50,    46,    45,    46,
      46,    46,    98,    50,    50,    98,    98,    83,    83,    95,
      46,    46,    98,    46,    98,    50,    46,    12,    97,    83,
      94,    93,    46,    92,    46,    46,    98,    83,    83,    83,
      91,    83,    90,    89,    46,    83,    83,    83,    88,    83
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    52,    53,    53,    54,    55,    55,
      56,    56,    57,    57,    58,    58,    58,    58,    58,    59,
      59,    59,    60,    60,    60,    61,    62,    63,    62,    62,
      64,    62,    65,    66,    66,    66,    66,    67,    67,    68,
      69,    69,    70,    71,    71,    72,    73,    73,    74,    74,
      75,    75,    76,    76,    76,    76,    76,    76,    77,    79,
      78,    80,    81,    81,    82,    82,    83,    83,    84,    83,
      85,    83,    86,    83,    87,    83,    88,    83,    89,    83,
      90,    83,    91,    83,    92,    83,    93,    83,    94,    83,
      95,    83,    96,    83,    83,    83,    83,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    99,    98,   100,    98,
     101,    98,   102,    98,   103,    98,   104,    98,   105,    98,
     106,    98,   107,    98,   108,    98,   109,    98,   110,    98,
     111,    98,   112,    98,    98,    98,   113,    98,   114,   114,
     114,   115,   115,   115,   115
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     0,     1,     2,     1,     2,
       2,     3,     3,     4,     0,     1,     2,     3,     4,     0,
       1,     3,     0,     1,     3,     2,     1,     0,     4,     3,
       0,     6,     1,     1,     1,     2,     2,     4,     3,     2,
       1,     2,     5,     6,     5,     2,     0,     2,     0,     2,
       1,     3,     2,     2,     2,     3,     3,     3,     3,     0,
       8,     7,     0,     1,     1,     2,     3,     1,     0,     4,
       0,     4,     0,     7,     0,     6,     0,    10,     0,     9,
       0,     9,     0,     9,     0,     8,     0,     8,     0,     8,
       0,     7,     0,     4,     2,     3,     2,     0,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     3,     0,     3,
       0,     8,     0,     6,     3,     1,     0,     4,     1,     1,
       3,     1,     4,     5,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    {
		RULE("R_protection -> PUBLIC");
		AST::Builder::SetAccess(Symbols::Access::Public);
	}

    break;

  case 3:

    {
		RULE("R_protection -> PROTECTED");
		AST::Builder::SetAccess(Symbols::Access::Protected);
	}

    break;

  case 4:

    {
		RULE("R_protection -> PRIVATE");
		AST::Builder::SetAccess(Symbols::Access::Private);
	}

    break;

  case 5:

    {
		RULE("R_static -> <EMPTY>");
		AST::Builder::SetStatic(false);
	}

    break;

  case 6:

    {
		RULE("R_static -> STATIC");
		AST::Builder::SetStatic(true);
	}

    break;

  case 8:

    {
		RULE("R_type -> IDENTIFIER");
		(yyval.identifier) = (yyvsp[0].identifier);
	}

    break;

  case 9:

    {
		RULE("R_type -> IDENTIFIER R_brackets_decl");
		*(yyvsp[-1].identifier) = to_string((yyvsp[0].intValue)) + *(yyvsp[-1].identifier);
		(yyval.identifier) = (yyvsp[-1].identifier);
	}

    break;

  case 10:

    {
		RULE("R_brackets_decl -> []");
		(yyval.intValue) = 1;
	}

    break;

  case 11:

    {
		RULE("R_brackets_decl -> R_brackets_decl []");
		(yyval.intValue) = (yyvsp[-2].intValue) + 1;
	}

    break;

  case 12:

    {
		RULE("R_brackets_def -> [ R_expresion ]");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[-1].node));
	}

    break;

  case 13:

    {
		RULE("R_brackets_def -> R_brackets_def [ R_expresion ]");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-3].collection), (yyvsp[-1].node));
	}

    break;

  case 14:

    {
		RULE("R_argument_decl_list -> <EMPTY>");
		(yyval.collection) = 0;
	}

    break;

  case 15:

    {
		RULE("R_argument_decl_list -> R_type");
		(yyval.collection) = AST::Builder::BuildCollection(new Parsing::StringNode((yyvsp[0].identifier)));
	}

    break;

  case 16:

    {
		RULE("R_argument_decl_list -> R_type IDENTIFIER");
		(yyval.collection) = AST::Builder::BuildCollection(new Parsing::StringNode((yyvsp[-1].identifier)));
		delete (yyvsp[0].identifier);
	}

    break;

  case 17:

    {
		RULE("R_argument_decl_list -> R_argument_decl_list , R_type");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), new Parsing::StringNode((yyvsp[0].identifier)));
	}

    break;

  case 18:

    {
		RULE("R_argument_decl_list -> R_argument_decl_list , R_type IDENTIFIER");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-3].collection), new Parsing::StringNode((yyvsp[-1].identifier)));
		delete (yyvsp[0].identifier);
	}

    break;

  case 19:

    {
		RULE("R_argument_def_list -> <EMPTY>");
		(yyval.collection) = 0;
	}

    break;

  case 20:

    {
		RULE("R_argument_def_list -> R_decl");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 21:

    {
		RULE("R_argument_def_list -> R_argument_def_list , R_decl");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), (yyvsp[0].node));
	}

    break;

  case 22:

    {
		RULE("R_argument_call_list -> <EMPTY>");
		(yyval.collection) = 0;
	}

    break;

  case 23:

    {
		RULE("R_argument_call_list -> R_expresion");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 24:

    {
		RULE("R_argument_call_list -> R_argument_call_list , R_expresion");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), (yyvsp[0].node));
	}

    break;

  case 25:

    {
		RULE("R_decl -> R_type IDENTIFIER");
		(yyval.node) = new Parsing::DeclarationNode((yyvsp[-1].identifier), (yyvsp[0].identifier));
		Parser::PushLine();
	}

    break;

  case 26:

    {
		RULE("R_identifiers -> IDENTIFIER");
		Parsing::InitNode* n = new Parsing::InitNode((yyvsp[0].identifier), nullptr);
		n->SetLine(Scanner::GetLineNumber());
		(yyval.collection) = AST::Builder::BuildCollection(n);
	}

    break;

  case 27:

    {Parser::PushLine();}

    break;

  case 28:

    {
		RULE("R_identifiers -> IDENTIFIER = R_expresion");
		Parsing::InitNode* n = new Parsing::InitNode((yyvsp[-3].identifier), (yyvsp[0].node));
		n->SetLine(Parser::PopLine());
		(yyval.collection) = AST::Builder::BuildCollection(n);
	}

    break;

  case 29:

    {
		RULE("R_identifiers -> R_identifiers , IDENTIFIER");
		Parsing::InitNode* n = new Parsing::InitNode((yyvsp[0].identifier), nullptr);
		n->SetLine(Scanner::GetLineNumber());
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), n);
	}

    break;

  case 30:

    {Parser::PushLine();}

    break;

  case 31:

    {
		RULE("R_identifiers -> R_identifiers , IDENTIFIER = R_expresion");
		Parsing::InitNode* n = new Parsing::InitNode((yyvsp[-3].identifier), (yyvsp[0].node));
		n->SetLine(Parser::PopLine());
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-5].collection), n);
	}

    break;

  case 32:

    {
		RULE("R_program -> R_classes");
		(yyval.node) = AST::Builder::Program((yyvsp[0].collection));
	}

    break;

  case 33:

    {
		RULE("R_classes -> R_class");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 34:

    {
		RULE("R_classes -> R_interface");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 35:

    {
		RULE("R_classes -> R_classes R_class");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-1].collection), (yyvsp[0].node));
	}

    break;

  case 36:

    {
		RULE("R_classes -> R_classes R_interface");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-1].collection), (yyvsp[0].node));
	}

    break;

  case 37:

    {
		RULE("R_interface -> R_interface_header { R_interface_body }");
		(yyval.node) = AST::Builder::Interface((yyvsp[-3].identifier), (yyvsp[-1].collection));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 38:

    {
		RULE("R_interface -> R_interface_header { }");
		(yyval.node) = AST::Builder::Interface((yyvsp[-2].identifier), nullptr);
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 39:

    {
		RULE("R_interface_header -> INTERFACE IDENTIFIER");
		(yyval.identifier) = (yyvsp[0].identifier);
		Parser::PushLine();
	}

    break;

  case 40:

    { 
		RULE("R_interface_body -> R_prototype");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 41:

    {
		RULE("R_interface_body -> R_interface_body R_prototype");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-1].collection), (yyvsp[0].node));
	}

    break;

  case 42:

    {
		RULE("R_prototype -> R_decl ( R_argument_decl_list ) ;");
		(yyval.node) = AST::Builder::Prototype((yyvsp[-4].node), (yyvsp[-2].collection));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 43:

    {
		RULE("R_class -> R_class_header R_extends R_implements { R_class_body }");
		(yyval.node) = AST::Builder::Class((yyvsp[-5].identifier), (yyvsp[-4].identifier), (yyvsp[-3].collection), (yyvsp[-1].collection));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 44:

    {
		RULE("R_class -> R_class_header R_extends R_implements { }");
		(yyval.node) = AST::Builder::Class((yyvsp[-4].identifier), (yyvsp[-3].identifier), (yyvsp[-2].collection), nullptr);
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 45:

    {
		RULE("R_class_header -> CLASS IDENTIFIER");
		(yyval.identifier) = (yyvsp[0].identifier);
		Parser::PushLine();
	}

    break;

  case 46:

    {
		RULE("R_extends -> <EMPTY>");
		(yyval.identifier) = nullptr;
	}

    break;

  case 47:

    {
		RULE("R_extends -> EXTENDS IDENTIFIER");
		(yyval.identifier) = (yyvsp[0].identifier);
	}

    break;

  case 48:

    {
		RULE("R_implements -> <EMPTY>");
		(yyval.collection) = nullptr;
	}

    break;

  case 49:

    {
		RULE("R_implements -> IMPLEMENTS R_interface_list");
		(yyval.collection) = (yyvsp[0].collection);
	}

    break;

  case 50:

    {
		RULE("R_interface_list -> IDENTIFIER");
		(yyval.collection) = AST::Builder::BuildCollection(new Parsing::StringNode{(yyvsp[0].identifier)});
	}

    break;

  case 51:

    {
		RULE("R_interface_list -> R_interface_list , IDENTIFIER");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), new Parsing::StringNode{(yyvsp[0].identifier)});
	}

    break;

  case 52:

    {
		RULE("R_class_body -> R_access R_attributes");
		(yyval.collection) = (yyvsp[0].collection);
	}

    break;

  case 53:

    {
		RULE("R_class_body -> R_access R_constructor");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 54:

    {
		RULE("R_class_body -> R_access R_method");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 55:

    {
		RULE("R_class_body -> R_class_body R_access R_attributes");
		(yyval.collection) = AST::Builder::MergeCollection((yyvsp[-2].collection), (yyvsp[0].collection));
	}

    break;

  case 56:

    {
		RULE("R_class_body -> R_class_body R_access R_constructor");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), (yyvsp[0].node));
	}

    break;

  case 57:

    {
		RULE("R_class_body -> R_class_body R_access R_method");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), (yyvsp[0].node));
	}

    break;

  case 58:

    {
		RULE("R_attributes -> R_type R_identifiers ;");
		(yyval.collection) = AST::Builder::Attributes((yyvsp[-2].identifier), (yyvsp[-1].collection));
	}

    break;

  case 59:

    {Parser::PushLine();}

    break;

  case 60:

    {
		RULE("R_constructor -> IDENTIFIER ( R_argument_def_list ) { R_code }");
		(yyval.node) = AST::Builder::Constructor((yyvsp[-7].identifier), (yyvsp[-4].collection), (yyvsp[-1].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 61:

    {
		RULE("R_method -> R_decl ( R_argument_def_list ) { R_code } ");
		(yyval.node) = AST::Builder::Method((yyvsp[-6].node), (yyvsp[-4].collection), (yyvsp[-1].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 62:

    {
		RULE("R_code -> <EMPTY>");
		(yyval.node) = new AST::BlockStatementNode();
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 63:

    {
		RULE("R_code -> R_statements");
		int line = (yyvsp[0].collection)->at(0)->GetLine();
		(yyval.node) = AST::Builder::MakeBlock((yyvsp[0].collection));
		(yyval.node)->SetLine(line);
	}

    break;

  case 64:

    {
		RULE("R_statements -> R_statement");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 65:

    {
		RULE("R_statements -> R_statements R_statement");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-1].collection), (yyvsp[0].node));
	}

    break;

  case 66:

    {
		RULE("R_statement -> { R_statements }");
		int line = (yyvsp[-1].collection)->at(0)->GetLine();
		(yyval.node) = AST::Builder::MakeBlock((yyvsp[-1].collection));
		(yyval.node)->SetLine(line);
	}

    break;

  case 67:

    {
		RULE("R_statement -> ;");
		(yyval.node) = new AST::EmptyStatementNode();
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 68:

    {Parser::PushLine();}

    break;

  case 69:

    {
		RULE("R_statement -> WRITE R_expresion ;");
		(yyval.node) = new AST::WriteStatementNode((yyvsp[-1].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 70:

    {Parser::PushLine();}

    break;

  case 71:

    {
		RULE("R_statement -> READ R_slots ;");
		AST::Node* slot = AST::Builder::CreateSlot((yyvsp[-1].collection));
		(yyval.node) = new AST::ReadStatementNode(slot);
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 72:

    {Parser::PushLine();}

    break;

  case 73:

    {
		RULE("R_statement -> IF ( R_expresion ) R_statement R_else");
		(yyval.node) = new AST::IfElseStatementNode((yyvsp[-3].node), AST::Builder::ForceBlock((yyvsp[-1].node)), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 74:

    {Parser::PushLine();}

    break;

  case 75:

    {
		RULE("R_statement -> WHILE ( R_expresion ) R_statement");
		(yyval.node) = new AST::WhileStatementNode((yyvsp[-2].node), AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 76:

    {Parser::PushLine();}

    break;

  case 77:

    {
		RULE("R_statement -> FOR ( R_expresion ; R_expresion ; R_expresion ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			(yyvsp[-7].node), 
			(yyvsp[-5].node),
			(yyvsp[-3].node),
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 78:

    {Parser::PushLine();}

    break;

  case 79:

    {
		RULE("R_statement -> FOR ( R_expresion ; R_expresion ;  ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			(yyvsp[-6].node), 
			(yyvsp[-4].node),
			nullptr,
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 80:

    {Parser::PushLine();}

    break;

  case 81:

    {
		RULE("R_statement -> FOR ( R_expresion ;  ; R_expresion ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			(yyvsp[-6].node), 
			nullptr,
			(yyvsp[-3].node),
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 82:

    {Parser::PushLine();}

    break;

  case 83:

    {
		RULE("R_statement -> FOR ( ; R_expresion ; R_expresion ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			nullptr, 
			(yyvsp[-5].node),
			(yyvsp[-3].node),
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 84:

    {Parser::PushLine();}

    break;

  case 85:

    {
		RULE("R_statement -> FOR ( R_expresion ;  ;  ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			(yyvsp[-5].node), 
			nullptr,
			nullptr,
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 86:

    {Parser::PushLine();}

    break;

  case 87:

    {
		RULE("R_statement -> FOR (  ; R_expresion ;  ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			nullptr, 
			(yyvsp[-4].node),
			nullptr,
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 88:

    {Parser::PushLine();}

    break;

  case 89:

    {
		RULE("R_statement -> FOR (  ;  ; R_expresion ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			nullptr, 
			nullptr,
			(yyvsp[-3].node),
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 90:

    {Parser::PushLine();}

    break;

  case 91:

    {
		RULE("R_statement -> FOR (  ;  ;  ) R_statement");
		(yyval.node) = new AST::ForStatementNode(
			nullptr, 
			nullptr,
			nullptr,
			AST::Builder::ForceBlock((yyvsp[0].node)));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 92:

    {Parser::PushLine();}

    break;

  case 93:

    {
		RULE("R_statement -> RETURN R_expresion ; ");
		(yyval.node) = new AST::ReturnStatementNode((yyvsp[-1].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 94:

    {
		RULE("R_statement -> RETURN ;");
		(yyval.node) = new AST::ReturnStatementNode(nullptr);
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 95:

    {
		RULE("R_statement -> R_type R_identifiers ;");
		(yyval.node) = AST::Builder::Variables((yyvsp[-2].identifier), (yyvsp[-1].collection));
	}

    break;

  case 96:

    {
		RULE("R_statement -> R_expresion ;");
		(yyval.node) = new AST::ExpressionStatementNode((yyvsp[-1].node));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 97:

    {
		RULE("R_else -> <EMPTY>");
		(yyval.node) = nullptr;
	}

    break;

  case 98:

    {
		RULE("R_else -> ELSE R_statement");
		(yyval.node) = AST::Builder::ForceBlock((yyvsp[0].node));
	}

    break;

  case 99:

    {
		RULE("R_expresion -> ILNULL");
		(yyval.node) = new AST::NullExprNode();
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 100:

    {
		RULE("R_expresion -> BOOL_CTE");
		(yyval.node) = new AST::BoolCteExprNode((yyvsp[0].boolValue));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 101:

    {
		RULE("R_expresion -> CHAR_CTE");
		(yyval.node) = new AST::CharCteExprNode((yyvsp[0].charValue));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 102:

    {
		RULE("R_expresion -> INT_CTE");
		(yyval.node) = new AST::IntCteExprNode((yyvsp[0].intValue));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 103:

    {
		RULE("R_expresion -> REAL_CTE");
		(yyval.node) = new AST::RealCteExprNode((yyvsp[0].realValue));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 104:

    {
		RULE("R_expresion -> STRING_CTE");
		(yyval.node) = new AST::StringCteExprNode(*(yyvsp[0].identifier));
		delete (yyvsp[0].identifier);
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 105:

    {
		RULE("R_expresion -> ( R_expresion )");
		(yyval.node) = (yyvsp[-1].node);
	}

    break;

  case 106:

    {Parser::PushLine();}

    break;

  case 107:

    {
		RULE("R_expresion -> R_expresion > R_expresion");
		(yyval.node) = new AST::GreaterExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 108:

    {Parser::PushLine();}

    break;

  case 109:

    {
		RULE("R_expresion -> R_expresion < R_expresion");
		(yyval.node) = new AST::LesserExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 110:

    {Parser::PushLine();}

    break;

  case 111:

    {
		RULE("R_expresion -> R_expresion EQ R_expresion");
		(yyval.node) = new AST::EqualExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 112:

    {Parser::PushLine();}

    break;

  case 113:

    {
		RULE("R_expresion -> R_expresion NE R_expresion");
		(yyval.node) = new AST::NotEqualExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 114:

    {Parser::PushLine();}

    break;

  case 115:

    {
		RULE("R_expresion -> R_expresion AND R_expresion");
		(yyval.node) = new AST::AndExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 116:

    {Parser::PushLine();}

    break;

  case 117:

    {
		RULE("R_expresion -> R_expresion OR R_expresion");
		(yyval.node) = new AST::OrExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 118:

    {Parser::PushLine();}

    break;

  case 119:

    {
		RULE("R_expresion -> R_expresion + R_expresion");
		(yyval.node) = new AST::PlusExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 120:

    {Parser::PushLine();}

    break;

  case 121:

    {
		RULE("R_expresion -> R_expresion - R_expresion");
		(yyval.node) = new AST::MinusExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 122:

    {Parser::PushLine();}

    break;

  case 123:

    {
		RULE("R_expresion -> R_expresion * R_expresion");
		(yyval.node) = new AST::MulExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 124:

    {Parser::PushLine();}

    break;

  case 125:

    {
		RULE("R_expresion -> R_expresion / R_expresion");
		(yyval.node) = new AST::DivExprNode((yyvsp[-3].node), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 126:

    {Parser::PushLine();}

    break;

  case 127:

    {
		RULE("R_expresion -> ! R_expresion");
		(yyval.node) = new AST::NotExprNode((yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 128:

    {Parser::PushLine();}

    break;

  case 129:

    {
		RULE("R_expresion -> - R_expresion");
		(yyval.node) = new AST::MinusUnaryExprNode((yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 130:

    {Parser::PushLine();}

    break;

  case 131:

    {
		RULE("R_expresion -> CAST < R_type > ( R_expresion )");
		(yyval.node) = new AST::CastExprNode(*(yyvsp[-4].identifier), (yyvsp[-1].node));
		delete (yyvsp[-4].identifier);
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 132:

    {Parser::PushLine();}

    break;

  case 133:

    {
		RULE("R_expresion -> NEW IDENTIFIER ( R_argument_call_list )");
		(yyval.node) = AST::Builder::NewExpression((yyvsp[-4].identifier), (yyvsp[-1].collection));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 134:

    {
		RULE("R_expresion -> NEW IDENTIFIER R_brackets_def");
		(yyval.node) = AST::Builder::NewArrayExpression((yyvsp[-1].identifier), (yyvsp[0].collection));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 135:

    {
		RULE("R_expresion -> R_slots");
		(yyval.node) = AST::Builder::CreateSlot((yyvsp[0].collection));
	}

    break;

  case 136:

    {Parser::PushLine();}

    break;

  case 137:

    {
		RULE("R_expresion -> R_slots = R_expresion");
		(yyval.node) = new AST::AssignmentExprNode(AST::Builder::CreateSlot((yyvsp[-3].collection)), (yyvsp[0].node));
		(yyval.node)->SetLine(Parser::PopLine());
	}

    break;

  case 138:

    {
		RULE("R_slots -> ILTHIS");
		AST::ThisSlotNode* n = new AST::ThisSlotNode();
		n->SetLine(Scanner::GetLineNumber());
		(yyval.collection) = AST::Builder::BuildCollection(n);
	}

    break;

  case 139:

    {
		RULE("R_slots -> R_slot");
		(yyval.collection) = AST::Builder::BuildCollection((yyvsp[0].node));
	}

    break;

  case 140:

    {
		RULE("R_slots -> R_slots . R_slot");
		(yyval.collection) = AST::Builder::AddCollection((yyvsp[-2].collection), (yyvsp[0].node));
	}

    break;

  case 141:

    {
		RULE("R_slot -> IDENTIFIER");
		(yyval.node) = AST::Builder::IdentifierSlot((yyvsp[0].identifier), false, nullptr, nullptr);
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 142:

    {
		RULE("R_slot -> IDENTIFIER ( R_argument_call_list )");
		(yyval.node) = AST::Builder::IdentifierSlot((yyvsp[-3].identifier), true, (yyvsp[-1].collection), nullptr);
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 143:

    {
		RULE("R_slot -> IDENTIFIER ( R_argument_call_list ) R_brackets_def");
		(yyval.node) = AST::Builder::IdentifierSlot((yyvsp[-4].identifier), true, (yyvsp[-2].collection), (yyvsp[0].collection));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;

  case 144:

    {
		RULE("R_slot -> IDENTIFIER R_brackets_def");
		(yyval.node) = AST::Builder::IdentifierSlot((yyvsp[-1].identifier), false, nullptr, (yyvsp[0].collection));
		(yyval.node)->SetLine(Scanner::GetLineNumber());
	}

    break;



      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}



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
