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
#line 1 "lab9algol.y" /* yacc.c:339  */


/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 26 integer registers, named 'a' thru 'z'
 *
 */

/* This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
   The return type via yylval is integer 

   When we need to make yylval more complicated, we need to define a pointer type for yylval 
   and to instruct YACC to use a new type so that we can pass back better values
 
   The registers are based on 0, so we substract 'a' from each single letter we get.

   based on context, we have YACC do the correct memmory look up or the storage depending
   on position

   Shaun Cooper
    January 2015

   problems  fix unary minus, fix parenthesis, add multiplication
   problems  make it so that verbose is on and off with an input argument instead of compiled in
*/
/*
 *name of code: lab7algol.y
 *purpose of code: Implement the rules for Algol-C using AST tree
 *author's name: Jessica Stein
 *date: 4/28/2022
 *algorithm description:
        *input: strings of code
        *output: Valid code will return "done parsing" and the print routine at the end of the written program and invalid code will return "syntax error" and the line number where the first error is spotted, and the program will exit.
        *assumptions about input: none
*/


	/* begin specs */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ast.h"
#include "emit.h"
#include "symtable.h"
#include "y.tab.h"
#include <string.h>

struct ASTNode * Program=NULL;//gloabal var of tree

int yylex();/*initialize lex*/
extern int lineno;/*keeps track of line number*/
extern int mydebug;/*debugs program*/
int level=0; /*static scope level*/
int offset=0; /*offset from activation record*/
int goffset=0; /*offset from main activation, used to hold where we are when we jump into and out of function*/
int maxoffset;
int val=1;
#define FUNCTION_MIN_SIZE 2
/*
 * Pre: when program is parsing strings of code will be passed to yyerror
 * Post: if an error is found the location of that error will be returned
*/
void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  fprintf(stderr, "%s on line %d\n", s, lineno); /*prints line number of error*/
}



#line 139 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    T_NUM = 258,
    T_ID = 259,
    T_QUOTED_STRING = 260,
    T_INT = 261,
    T_VOID = 262,
    T_BOOLEAN = 263,
    T_END = 264,
    T_BEGIN = 265,
    T_OF = 266,
    T_IF = 267,
    T_THEN = 268,
    T_ELSE = 269,
    T_READ = 270,
    T_RETURN = 271,
    T_WRITE = 272,
    T_WHILE = 273,
    T_DO = 274,
    T_AND = 275,
    T_OR = 276,
    T_TRUE = 277,
    T_FALSE = 278,
    T_NOT = 279,
    T_MULTIPLY = 280,
    T_DIVIDE = 281,
    T_ADD = 282,
    T_SUBTRACT = 283,
    T_LE = 284,
    T_LT = 285,
    T_GT = 286,
    T_GE = 287,
    T_EQ = 288,
    T_NEQ = 289,
    UMINUS = 290
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_ID 259
#define T_QUOTED_STRING 260
#define T_INT 261
#define T_VOID 262
#define T_BOOLEAN 263
#define T_END 264
#define T_BEGIN 265
#define T_OF 266
#define T_IF 267
#define T_THEN 268
#define T_ELSE 269
#define T_READ 270
#define T_RETURN 271
#define T_WRITE 272
#define T_WHILE 273
#define T_DO 274
#define T_AND 275
#define T_OR 276
#define T_TRUE 277
#define T_FALSE 278
#define T_NOT 279
#define T_MULTIPLY 280
#define T_DIVIDE 281
#define T_ADD 282
#define T_SUBTRACT 283
#define T_LE 284
#define T_LT 285
#define T_GT 286
#define T_GE 287
#define T_EQ 288
#define T_NEQ 289
#define UMINUS 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 81 "lab9algol.y" /* yacc.c:355  */

	int value;
	char *string;
	struct ASTNode * astnode;
	enum A_OPERATORS op;

#line 256 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 273 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    41,    36,     2,
      47,    48,    39,    37,    46,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      50,    49,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    35,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   108,   109,   112,   113,   117,   131,   146,
     162,   179,   193,   194,   195,   199,   221,   199,   239,   240,
     244,   246,   253,   274,   297,   297,   312,   313,   317,   318,
     322,   323,   324,   325,   326,   327,   328,   329,   333,   337,
     341,   350,   359,   366,   369,   373,   379,   383,   390,   406,
     409,   430,   453,   454,   471,   472,   473,   474,   475,   476,
     480,   481,   499,   500,   504,   506,   533,   534,   535,   536,
     540,   541,   545,   546,   547,   552,   557,   573,   602,   603,
     608,   618
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_NUM", "T_ID", "T_QUOTED_STRING",
  "T_INT", "T_VOID", "T_BOOLEAN", "T_END", "T_BEGIN", "T_OF", "T_IF",
  "T_THEN", "T_ELSE", "T_READ", "T_RETURN", "T_WRITE", "T_WHILE", "T_DO",
  "T_AND", "T_OR", "T_TRUE", "T_FALSE", "T_NOT", "T_MULTIPLY", "T_DIVIDE",
  "T_ADD", "T_SUBTRACT", "T_LE", "T_LT", "T_GT", "T_GE", "T_EQ", "T_NEQ",
  "'|'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS", "';'", "'['",
  "']'", "','", "'('", "')'", "'='", "'<'", "'>'", "$accept", "program",
  "declaration_list", "declaration", "var_declaration", "var_list",
  "type_specifier", "fun_declaration", "$@1", "$@2", "params",
  "param_list", "param", "compound_stmt", "$@3", "local_declarations",
  "statement_list", "statement", "expression_stmt", "selection_stmt",
  "iteration_stmt", "return_stmt", "read_stmt", "write_stmt",
  "assignment_stmt", "expression", "var", "simple_expression", "relop",
  "additive_expression", "addop", "term", "multop", "factor", "call",
  "args", "arg_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   124,    38,    43,    45,    42,
      47,    37,   290,    59,    91,    93,    44,    40,    41,    61,
      60,    62
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -19

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      87,   -53,   -53,   -53,     7,   -53,    87,   -53,     9,   -53,
     -53,   -53,    22,   -29,    16,    45,   -53,   -53,     5,    40,
     -53,    90,    10,    12,    60,   -53,   -53,    30,    45,    43,
      42,    87,   -53,    44,    89,   -53,   -53,   -53,   -53,    87,
      87,    45,     8,   -53,   -53,    33,    35,    96,    18,    24,
      35,   -53,   -53,    35,   -53,    35,   -53,    93,     8,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,    61,    54,   -53,    41,
      23,   -53,   -53,    35,    35,    92,   -53,    62,    64,   -53,
      65,    66,    67,    94,   -53,    63,   -53,   -53,   -53,    35,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,    35,    35,
     -53,   -53,   -53,   -53,    35,    69,    70,    71,   -53,     8,
     -53,   -53,   -53,   -53,     8,   -53,    72,   -35,    23,   -53,
     -53,    35,   -53,    98,   -53,   -53,   -53,     8,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,    14,     0,     2,     3,     5,     0,     6,
       1,     4,     8,     0,     0,     0,    15,     7,     0,     8,
      10,     0,     9,    13,     0,    16,    19,    20,     0,    22,
       0,     0,    11,     0,     0,    21,    23,    24,    17,    27,
      27,     0,    28,    26,    71,    50,     0,     0,     0,     0,
       0,    74,    75,     0,    39,     0,    31,     0,    28,    30,
      32,    33,    35,    36,    37,    34,     0,    72,    49,    52,
      60,    64,    73,     0,    78,     0,    72,    50,     0,    44,
       0,     0,     0,     0,    76,     0,    25,    29,    38,     0,
      54,    57,    58,    59,    62,    63,    55,    56,     0,     0,
      68,    69,    66,    67,     0,     0,    80,     0,    79,     0,
      45,    43,    47,    46,     0,    70,     0,    53,    61,    65,
      51,     0,    77,    41,    42,    48,    81,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,   111,   -53,    -3,   -11,    14,   -53,   -53,   -53,
     -53,    91,   -53,    84,   -53,    80,    68,   -26,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -40,   -42,    32,   -53,    25,
     -53,    26,   -53,   -52,   -53,   -53,     3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    13,     8,     9,    21,    30,
      25,    26,    27,    56,    39,    42,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    76,    68,    98,    69,
      99,    70,   104,    71,    72,   107,   108
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,    84,    94,    95,    20,    78,    75,    10,    80,    82,
      83,    44,    45,    12,    17,    85,    67,    32,    37,    18,
      46,    44,    45,    47,    48,    49,    50,    44,    45,    81,
      51,    52,    53,   105,   106,    24,    40,    40,    44,    45,
      51,    52,    53,   100,   101,    24,    51,    52,    53,    19,
      22,    54,   119,    41,    41,    55,    28,    51,    52,    53,
     -18,    79,   102,   103,    29,    55,    14,    67,    15,    16,
      90,    55,    67,    91,    92,    93,    31,    73,    94,    95,
      74,   106,    55,   123,    14,    67,    15,    33,   124,    36,
      34,    96,    97,     1,     2,     3,     1,    23,     3,    37,
      77,   128,    86,    89,    88,   109,    73,   110,   111,   112,
     113,   115,   127,   114,   120,   125,   121,    11,    38,   122,
      43,   116,    35,   117,   126,   118,    87
};

static const yytype_uint8 yycheck[] =
{
      42,    53,    37,    38,    15,    47,    46,     0,    48,    49,
      50,     3,     4,     4,    43,    55,    58,    28,    10,     3,
      12,     3,     4,    15,    16,    17,    18,     3,     4,     5,
      22,    23,    24,    73,    74,    21,    39,    40,     3,     4,
      22,    23,    24,    20,    21,    31,    22,    23,    24,     4,
      45,    43,   104,    39,    40,    47,    46,    22,    23,    24,
      48,    43,    39,    40,     4,    47,    44,   109,    46,    47,
      29,    47,   114,    32,    33,    34,    46,    44,    37,    38,
      47,   121,    47,   109,    44,   127,    46,    44,   114,    45,
      48,    50,    51,     6,     7,     8,     6,     7,     8,    10,
       4,   127,     9,    49,    43,    13,    44,    43,    43,    43,
      43,    48,    14,    19,    45,    43,    46,     6,    34,    48,
      40,    89,    31,    98,   121,    99,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,    53,    54,    55,    56,    58,    59,
       0,    54,     4,    57,    44,    46,    47,    43,     3,     4,
      57,    60,    45,     7,    58,    62,    63,    64,    46,     4,
      61,    46,    57,    44,    48,    63,    45,    10,    65,    66,
      56,    58,    67,    67,     3,     4,    12,    15,    16,    17,
      18,    22,    23,    24,    43,    47,    65,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    81,
      83,    85,    86,    44,    47,    77,    78,     4,    78,    43,
      77,     5,    77,    77,    85,    77,     9,    68,    43,    49,
      29,    32,    33,    34,    37,    38,    50,    51,    80,    82,
      20,    21,    39,    40,    84,    77,    77,    87,    88,    13,
      43,    43,    43,    43,    19,    48,    79,    81,    83,    85,
      45,    46,    48,    69,    69,    43,    88,    14,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    56,    57,    57,
      57,    57,    58,    58,    58,    60,    61,    59,    62,    62,
      63,    63,    64,    64,    66,    65,    67,    67,    68,    68,
      69,    69,    69,    69,    69,    69,    69,    69,    70,    70,
      71,    71,    72,    73,    73,    74,    75,    75,    76,    77,
      78,    78,    79,    79,    80,    80,    80,    80,    80,    80,
      81,    81,    82,    82,    83,    83,    84,    84,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    86,    87,    87,
      88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     4,
       3,     6,     1,     1,     1,     0,     0,     8,     1,     1,
       1,     3,     2,     4,     0,     5,     2,     0,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       6,     4,     4,     3,     2,     3,     3,     3,     4,     1,
       1,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     2,     4,     0,     1,
       1,     3
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
#line 105 "lab9algol.y" /* yacc.c:1646  */
    { Program = (yyvsp[0].astnode);}
#line 1450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 108 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 109 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[-1].astnode); (yyvsp[-1].astnode) -> next=(yyvsp[0].astnode);}
#line 1462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 112 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 113 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 117 "lab9algol.y" /* yacc.c:1646  */
    {
			/*need to update the type in varlist and pass up to parent*/
			(yyval.astnode)=(yyvsp[-1].astnode);
			struct ASTNode *p;
			p = (yyvsp[-1].astnode);
			while(p!=NULL){
				p->op=(yyvsp[-2].op);
				p->symbol->Type=(yyvsp[-2].op);
				p=p->s1;
			}/*end while*/
		}
#line 1490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 131 "lab9algol.y" /* yacc.c:1646  */
    {	struct SymbTab *p;
	 		 /*Insert if OK, then ass the pointer from insertion into the ASTnode to have reference to the symbol tbale entry*/
	 		if(Search((yyvsp[0].string), level, 0)==NULL){
	 			(yyval.astnode)=ASTCreateNode(A_VARDEC);
				(yyval.astnode)->symbol=Insert((yyvsp[0].string), 0, 0, level, 1, offset);
	 			(yyval.astnode)->name=(yyvsp[0].string);/*this changes to symbol table*/
				offset += 1;/*increment offset*/
				
			}
			else{
				yyerror((yyvsp[0].string));
				yyerror("symbol table already in use ");
				exit(1);
			}
		}
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 146 "lab9algol.y" /* yacc.c:1646  */
    {
			struct SymbTab *p;
			/*Insert if OK, then ass the pointer from insertion into the ASTnode to have reference to the symbol tbale entry*/
			if(Search((yyvsp[-3].string), level, 0)==NULL){/*we did not find the anme before, so we can insert it*/
				(yyval.astnode)=ASTCreateNode(A_VARDEC);
				(yyval.astnode)->symbol=Insert((yyvsp[-3].string), 0, 2, level, (yyvsp[-1].value), offset);
				(yyval.astnode)->size=(yyvsp[-1].value); /*remember dimension*/
				(yyval.astnode)->name=(yyvsp[-3].string);/*this changes to symbol table*/
				offset += (yyvsp[-1].value);
			}
			else{
				yyerror((yyvsp[-3].string));
				yyerror("symbol already used ");
				exit(1);
			}
		}
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 162 "lab9algol.y" /* yacc.c:1646  */
    {
			 struct SymbTab *p;
			 /*Insert if OK, then ass the pointer from insertion into the ASTnode to have reference to the symbol tbale entry*/
                        if(Search((yyvsp[-2].string), level, 0)==NULL){
                                (yyval.astnode)=ASTCreateNode(A_VARDEC);
                                (yyval.astnode)->symbol=Insert((yyvsp[-2].string), 0, 0, level, 1, offset);
                                (yyval.astnode)->name=(yyvsp[-2].string);/*this changes to symbol table*/
				(yyval.astnode)->s1=(yyvsp[0].astnode);/*this changes to symbol table*/
				offset += 1;/*increment offset*/
                        }
			else{
                                yyerror((yyvsp[-2].string));
                                yyerror("symbol table already in use ");
                                exit(1);
                        }

		}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 179 "lab9algol.y" /* yacc.c:1646  */
    {
			struct SymbTab *p;
			if(Search((yyvsp[-5].string), level, 0)==NULL){/*we did not find the name before, so we can insert it*/
				(yyval.astnode)=ASTCreateNode(A_VARDEC);
				(yyval.astnode)->symbol=Insert((yyvsp[-5].string), 0, 2, level, (yyvsp[-3].value), offset);
				(yyval.astnode)->name=(yyvsp[-5].string);/*this changes to symbol table*/
                                (yyval.astnode)->size=(yyvsp[-3].value);/*remember dimensions*/
				(yyval.astnode)->s1=(yyvsp[0].astnode);/*this changes to symbol table*/
				offset += (yyvsp[-3].value);
			}
		}
#line 1569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 193 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_INTTYPE;}
#line 1575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 194 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_VOIDTYPE;}
#line 1581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 195 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_BOOLTYPE;}
#line 1587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 199 "lab9algol.y" /* yacc.c:1646  */
    {/*we are defining a function, we need to check the name and reset the offsets. 
					We allow params productions rule to insert a pointer to the AST tree for the formal parameters.
					We need to do this because inside the compound statement we may need to know the type and length fo the formals.
					If we wait to update the symbol table after the compound statement then the checking of a recursive call will not
					know the parameter length, etc.
					Effectively, we update the symbol table to point to the formal parameters.*/

					/*if we have seen the name, then we need to error. If not, we remember the global offset.*/
					
					if(Search((yyvsp[-1].string), level, 0)==NULL){
						Insert((yyvsp[-1].string), (yyvsp[-2].op), 1, level, 0, 0);
						goffset=offset;
						offset=FUNCTION_MIN_SIZE;
						maxoffset=0; 
					}
					else{
						yyerror((yyvsp[-1].string));
						yyerror("name already used ");
						exit(1);
					}
					
				}
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 221 "lab9algol.y" /* yacc.c:1646  */
    {
		/*update the symbol table to have a pointer to the formal parameters*/
			(Search((yyvsp[-3].string), 0, 0))->fparms=(yyvsp[0].astnode);
		}
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 225 "lab9algol.y" /* yacc.c:1646  */
    {
			(yyval.astnode)=ASTCreateNode(A_FUNDEC);
			(yyval.astnode)->name=(yyvsp[-6].string);
			(yyval.astnode)->op=(yyvsp[-7].op);/*rememeber the declaration type*/
			(yyval.astnode)->s1=(yyvsp[-3].astnode); /*the parameter list*/
			(yyval.astnode)->calctype=(yyvsp[-7].op);/*remember type declaration type*/
			(yyval.astnode)->symbol=Search((yyvsp[-6].string), 0, 0);/*go get the symbol table entry*/
			(yyval.astnode)->s2=(yyvsp[0].astnode);/*compound statement*/
			(yyval.astnode)->symbol->mysize = maxoffset;	
			offset=goffset;
		}
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 239 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=NULL;}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 240 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 244 "lab9algol.y" /* yacc.c:1646  */
    { (yyval.astnode)=(yyvsp[0].astnode);}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 246 "lab9algol.y" /* yacc.c:1646  */
    {
                        (yyval.astnode)=(yyvsp[-2].astnode);
			(yyval.astnode)->next=(yyvsp[0].astnode);}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 253 "lab9algol.y" /* yacc.c:1646  */
    {/*symbol table function level add/check*/
      			if(mydebug) Display();
			 if(Search((yyvsp[0].string), level+1, 0)==NULL){
			 	(yyval.astnode)=ASTCreateNode(A_PARAM);
				(yyval.astnode)->name=(yyvsp[0].string);
				(yyval.astnode)->op=(yyvsp[-1].op);
				(yyval.astnode)->calctype=(yyvsp[-1].op);
				(yyval.astnode)->symbol=Insert((yyvsp[0].string), (yyvsp[-1].op), 0, level+1, 1, offset);
				mydebug && printf("in param insert %s %d\n", (yyvsp[0].string), level+1);

				if(mydebug) Display;
				(yyval.astnode)->size=0;/*not an array*/
				offset+=1;

			}
			else{
				yyerror((yyvsp[0].string));
				yyerror("symbol already used ");
				exit(1);
			}
		}
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 274 "lab9algol.y" /* yacc.c:1646  */
    {
			 if(mydebug) Display();
                         if(Search((yyvsp[-2].string), level+1, 0)==NULL){
                                (yyval.astnode)=ASTCreateNode(A_PARAM);
                                (yyval.astnode)->name=(yyvsp[-2].string);
                                (yyval.astnode)->op=(yyvsp[-3].op);
                                (yyval.astnode)->calctype=(yyvsp[-3].op);
                                (yyval.astnode)->symbol=Insert((yyvsp[-2].string), (yyvsp[-3].op), 2, level+1, 1, offset);
				mydebug && printf("in param insert %s %d\n", (yyvsp[-2].string), level+1);

                                if(mydebug) Display;
                                (yyval.astnode)->size=0;/*not an array*/
				offset+=1;
                        }
                        else{
                                yyerror((yyvsp[-2].string));
                                yyerror("symbol already used ");
                                exit(1);
                        }
		}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 297 "lab9algol.y" /* yacc.c:1646  */
    {level++;}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 300 "lab9algol.y" /* yacc.c:1646  */
    {
			(yyval.astnode)=ASTCreateNode(A_BLOCK);
			(yyval.astnode)->s1=(yyvsp[-2].astnode);
			(yyval.astnode)->s2=(yyvsp[-1].astnode);
			
			Display();
			if(offset>maxoffset) maxoffset=offset; 
			offset=offset-Delete(level);
			level--;}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 312 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[-1].astnode); (yyval.astnode)->next=(yyvsp[0].astnode);}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 313 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode) = NULL;}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 317 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=NULL;}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 318 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[-1].astnode); (yyval.astnode)->next=(yyvsp[0].astnode);}
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 322 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 323 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 324 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 325 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 326 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 327 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 328 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 329 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 333 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_EXPR);
					(yyval.astnode)->s1=(yyvsp[-1].astnode);
				}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 337 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_EXPR);}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 341 "lab9algol.y" /* yacc.c:1646  */
    {
	       								
	       								(yyval.astnode)=ASTCreateNode(A_IF);
	       								(yyval.astnode)->s1=(yyvsp[-4].astnode);
									(yyval.astnode)->s2=ASTCreateNode(A_THEN);
									(yyval.astnode)->s2->s1=(yyvsp[-2].astnode);
									(yyval.astnode)->s2->s2=(yyvsp[0].astnode);
									
								}
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 350 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_IF);
							(yyval.astnode)->s1=(yyvsp[-2].astnode);
							(yyval.astnode)->s2=ASTCreateNode(A_THEN);
							(yyval.astnode)->s2->s1=(yyvsp[0].astnode);
							
					}
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 359 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_WHILE);
	       						(yyval.astnode)->s1=(yyvsp[-2].astnode);
							(yyval.astnode)->s2=(yyvsp[0].astnode);
						}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 366 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_RETURN);
	    				 (yyval.astnode)->s1=(yyvsp[-1].astnode);
					}
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 369 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_RETURN);}
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 373 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_READ); 
	  			(yyval.astnode)->s1=(yyvsp[-1].astnode); 
			}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 379 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_WRITE);
	                                (yyval.astnode)->name = NULL;
	   				(yyval.astnode)->s1=(yyvsp[-1].astnode);
					}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 383 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_WRITE);/*4/21/22 with addition of T_QUOTED_STRING write supports writing strings*/
					(yyval.astnode)->name=(yyvsp[-1].string);
					(yyval.astnode)->label=GenerateLabel();
					}
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 390 "lab9algol.y" /* yacc.c:1646  */
    {
						if((yyvsp[-3].astnode)->calctype!=(yyvsp[-1].astnode)->calctype){
							yyerror(" assignment types do not match ");
							exit(1);
						}
						(yyval.astnode)=ASTCreateNode(A_ASSIGN);
						/*Assignment statement we leave left alone so that it can be strung with other statements*/
							(yyval.astnode)->s1=(yyvsp[-3].astnode);
							(yyval.astnode)->s2=(yyvsp[-1].astnode);
							(yyval.astnode)->name=CreateTemp();
							(yyval.astnode)->symbol=Insert((yyval.astnode)->name,A_INTTYPE,0,level,1,offset);
							offset++;
						}
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 406 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 409 "lab9algol.y" /* yacc.c:1646  */
    {
    		/*we want to create a NODE called IDENTIFIER with a pointer to the SYMBOL table*/
		struct SymbTab *p;
		if((p=Search((yyvsp[0].string), level, 1)) != NULL) {
    			(yyval.astnode)=ASTCreateNode(A_IDENT); 
    			(yyval.astnode)->name=(yyvsp[0].string); /*change this to pointer to symbol table*/
			(yyval.astnode)->symbol=p;
			(yyval.astnode)->calctype=p->Type;
			printf("Type for VAR is %d\n", p->Type);
			if(p->IsAFunc != 0){ /*changed on 4/11/2022 to handle cases when a scalar is passed that shouldn't be passed*/
				yyerror((yyvsp[0].string));
				yyerror("variable is not a scalar, syntax error ");
				exit(1);
			}
		}
		else{
			yyerror((yyvsp[0].string));
			yyerror("undeclared variable ");
			exit(1);
		}
	}
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 430 "lab9algol.y" /* yacc.c:1646  */
    {	
				struct SymbTab *p;
				if((p=Search((yyvsp[-3].string), level, 1)) != NULL){
					(yyval.astnode)=ASTCreateNode(A_IDENT);
					(yyval.astnode)->name=(yyvsp[-3].string);/*change this to pointer to symbol table*/
					(yyval.astnode)->s1=(yyvsp[-1].astnode);
					(yyval.astnode)->calctype=p->Type; /*inherit the type*/
					(yyval.astnode)->symbol=p;
					if(p->IsAFunc != 2){/*changed on 4/11/2022 for clarity and ensurance that symbol always points to p*/
						yyerror((yyvsp[-3].string));
						yyerror("not an array, type mismatch");
						exit(1);
					}
			     	}
				else{
					yyerror((yyvsp[-3].string));
					yyerror("undeclared variable ");
					exit(1);
				}
			}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 453 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 454 "lab9algol.y" /* yacc.c:1646  */
    { /*type checking*/
									if((yyvsp[-2].astnode)->calctype != (yyvsp[0].astnode)->calctype){
										yyerror(" additive type mismatch ");
										exit(1);
									}
									(yyval.astnode)=ASTCreateNode(A_EXPR);
									(yyval.astnode)->s1=(yyvsp[-2].astnode);
									(yyval.astnode)->op=(yyvsp[-1].op);
									(yyval.astnode)->s2=(yyvsp[0].astnode);
									(yyval.astnode)->calctype=(yyvsp[0].astnode)->calctype;
									(yyval.astnode)->name=CreateTemp();
									(yyval.astnode)->symbol=(Insert((yyval.astnode)->name, A_INTTYPE, 0, level, 1, offset));
									offset++;
								}
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 471 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_LE;}
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 472 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_LT;}
#line 2008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 473 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_GT;}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 474 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_GE;}
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 475 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_EQ;}
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 476 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_NEQ;}
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 480 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 481 "lab9algol.y" /* yacc.c:1646  */
    {
							/*type checking*/
							if((yyvsp[-2].astnode)->calctype != (yyvsp[0].astnode)->calctype){
								yyerror(" additive expression type mismatch ");
								exit(1);
							}
							(yyval.astnode)=ASTCreateNode(A_EXPR);
							(yyval.astnode)->s1=(yyvsp[-2].astnode);
							(yyval.astnode)->op=(yyvsp[-1].op);
							(yyval.astnode)->s2=(yyvsp[0].astnode);
							(yyval.astnode)->name=CreateTemp();
							(yyval.astnode)->calctype=A_INTTYPE;
							(yyval.astnode)->symbol=Insert((yyval.astnode)->name, A_INTTYPE, 0, level, 1, offset);
							offset++;
							}
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 499 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_PLUS;}
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 500 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_MINUS;}
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 504 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 506 "lab9algol.y" /* yacc.c:1646  */
    {			 /*type checking*/
                                                        if((yyvsp[-2].astnode)->calctype != (yyvsp[0].astnode)->calctype){
                                                                yyerror(" additive expression type mismatch ");
                                                                exit(1);
                                                        }
							if(((yyvsp[-1].op)==A_TIMES || (yyvsp[-1].op)==A_DIVIDE)&& (yyvsp[-2].astnode)->calctype!=A_INTTYPE){
								yyerror(" term and multop type mismatch TIMES/DIVIDE");
								exit(1);
							}
							if(((yyvsp[-1].op)==A_AND || (yyvsp[-1].op)==A_OR) && (yyvsp[-2].astnode)->calctype!=A_BOOLTYPE){
								yyerror(" term and multop type mismatch AND/OR");
                                                                exit(1);
	
							}
                                                        (yyval.astnode)=ASTCreateNode(A_EXPR);
                                                        (yyval.astnode)->s1=(yyvsp[-2].astnode);
                                                        (yyval.astnode)->op=(yyvsp[-1].op);
                                                        (yyval.astnode)->s2=(yyvsp[0].astnode);
                                                        (yyval.astnode)->name=CreateTemp();
                                                        (yyval.astnode)->calctype=A_INTTYPE;
                                                        (yyval.astnode)->symbol=Insert((yyval.astnode)->name, A_INTTYPE, 0, level, 1, offset);
							offset++;
                                        }
#line 2104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 533 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_TIMES;}
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 534 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_DIVIDE;}
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 535 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_AND;}
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 536 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.op)=A_OR;}
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 540 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[-1].astnode);}
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 541 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_NUM);
			(yyval.astnode)->value=(yyvsp[0].value);
			(yyval.astnode)->calctype=A_INTTYPE;
			}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 545 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 546 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 2155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 547 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_BOOL);
				(yyval.astnode)->value=1;
				(yyval.astnode)->TF=true;
				(yyval.astnode)->calctype=A_BOOLTYPE;
			}
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 552 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=ASTCreateNode(A_BOOL);
				(yyval.astnode)->value=0;
				(yyval.astnode)->TF=false;
				(yyval.astnode)->calctype=A_BOOLTYPE;
			}
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 557 "lab9algol.y" /* yacc.c:1646  */
    {
				 if((yyvsp[0].astnode)->calctype != A_BOOLTYPE){
                                                                yyerror(" additive expression type mismatch ");
                                                                exit(1);
                                                        }

				(yyval.astnode)=ASTCreateNode(A_EXPR);
				(yyval.astnode)->name=CreateTemp();
				(yyval.astnode)->symbol=Insert((yyval.astnode)->name,A_INTTYPE,0,level,1,offset);
				(yyval.astnode)->op=A_NOT;
				(yyval.astnode)->s1=(yyvsp[0].astnode);
				offset++;
				}
#line 2193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 573 "lab9algol.y" /* yacc.c:1646  */
    {
     				struct SymbTab *p;
				if((p=Search((yyvsp[-3].string), 0, 0)) != NULL){
					if(p->IsAFunc != 1){
						yyerror((yyvsp[-3].string));
						yyerror("Function name not defined ");
						exit(1);
					}
				/*now we check that the parameter list of the function are the same as the argument list*/
					if(CompareFormals(p->fparms, (yyvsp[-1].astnode)) != 1){
						yyerror((yyvsp[-3].string));
						yyerror("parameter type or in-length mismatch between formals and actuals ");
						exit(1);
					}
     					(yyval.astnode)=ASTCreateNode(A_CALL);
					(yyval.astnode)->name=(yyvsp[-3].string);
					(yyval.astnode)->s1=(yyvsp[-1].astnode);
					(yyval.astnode)->calctype=p->Type;
					(yyval.astnode)->symbol=p;
				}
				else{/*symbol not found*/
					yyerror((yyvsp[-3].string));
					yyerror("Function name not defined ");
					exit(1);
				}
			}
#line 2224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 602 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=NULL;}
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 603 "lab9algol.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 608 "lab9algol.y" /* yacc.c:1646  */
    {
	 			(yyval.astnode)=ASTCreateNode(A_ARGS);
	 			(yyval.astnode)->s1=(yyvsp[0].astnode);
				(yyval.astnode)->calctype=(yyvsp[0].astnode)->calctype;
				(yyval.astnode)->next=NULL;
				(yyval.astnode)->name=CreateTemp();
                                (yyval.astnode)->symbol=Insert((yyval.astnode)->name,A_INTTYPE,0,level,1,offset);
                                offset++;
	
			}
#line 2251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 618 "lab9algol.y" /* yacc.c:1646  */
    {
						(yyval.astnode)=ASTCreateNode(A_ARGS); 
						(yyval.astnode)->s1=(yyvsp[-2].astnode);
						(yyval.astnode)->calctype=(yyvsp[-2].astnode)->calctype;
						(yyval.astnode)->next=(yyvsp[0].astnode);
						(yyval.astnode)->name=CreateTemp();
						(yyval.astnode)->symbol=Insert((yyval.astnode)->name,A_INTTYPE,0,level,1,offset);
						offset++;
					}
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2269 "y.tab.c" /* yacc.c:1646  */
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
#line 629 "lab9algol.y" /* yacc.c:1906  */
	/*end of rules, start of program */

/*begin parsing*/
/*
*PRE: arguments from command line, and an algol c file to parse
*POST: an asm output file and possibly ast tree and symbol table for debugging
*/
int main(int argc, char *argv[])
{ 
	int c = 1;
	FILE *fp=NULL;
	char s[100];

	while(c<argc){/*while there are still arguments to be passed*/
		if(strcmp(argv[c], "-d")==0) mydebug = 1;/*with inclusion of -d in command line mydebug is set to 1*/
		if(strcmp(argv[c], "-o")==0){/*if -o is included name the file, create an asm file named what comes after the o*/
			strcpy(s, argv[c+1]);
			strcat(s, ".asm");
			fp = fopen(s, "w");
			if(fp==NULL){
				printf("Can't open %s\n", s);
				exit(1);
			}
		}
	c++;/*iterate through command line argument*/
	}
	if(fp==NULL){/*didn't provide a file name for the asm file*/
		printf("Must provide a -o file name\n");
		exit(1);
	}
	
	yyparse();
	if(mydebug){/*if mydebug is set to one, then we print the ast tree and the symbol table*/
		printf("\n\nparsing complete\n");
		Display();
		ASTprint(0, Program);
	}
	/*following code runs emit.c to create an .asm file from algol code*/
	emit_header(Program, fp);
	emit_ast(Program, fp);
}
