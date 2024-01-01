/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/parser.y"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdarg>
#include <cinttypes>

#include <compiler.hpp>
#include <value.hpp>
#include <rvalue.hpp>
#include <lvalue.hpp>
#include <lvalue_var.hpp>
#include <lvalue_array.hpp>

// C like functions for YACC / FLEX
static void yyerror(const char *msg);
static int yyparse(void);
int yylex(void);

extern FILE *yyin;

#ifdef YAC_DEBUG
#define pr_dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define pr_dbg(...)
#endif

/* Global variables */
static Compiler compiler;


#line 103 "./src/parser_tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser_tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_YY_SEMICOLON = 3,               /* YY_SEMICOLON  */
  YYSYMBOL_YY_COMMA = 4,                   /* YY_COMMA  */
  YYSYMBOL_YY_ADD = 5,                     /* YY_ADD  */
  YYSYMBOL_YY_SUB = 6,                     /* YY_SUB  */
  YYSYMBOL_YY_DIV = 7,                     /* YY_DIV  */
  YYSYMBOL_YY_MOD = 8,                     /* YY_MOD  */
  YYSYMBOL_YY_MUL = 9,                     /* YY_MUL  */
  YYSYMBOL_YY_ASSIGN = 10,                 /* YY_ASSIGN  */
  YYSYMBOL_YY_EQ = 11,                     /* YY_EQ  */
  YYSYMBOL_YY_NE = 12,                     /* YY_NE  */
  YYSYMBOL_YY_LT = 13,                     /* YY_LT  */
  YYSYMBOL_YY_GT = 14,                     /* YY_GT  */
  YYSYMBOL_YY_LE = 15,                     /* YY_LE  */
  YYSYMBOL_YY_GE = 16,                     /* YY_GE  */
  YYSYMBOL_YY_PROGRAM = 17,                /* YY_PROGRAM  */
  YYSYMBOL_YY_PROCEDURE = 18,              /* YY_PROCEDURE  */
  YYSYMBOL_YY_IS = 19,                     /* YY_IS  */
  YYSYMBOL_YY_IN = 20,                     /* YY_IN  */
  YYSYMBOL_YY_END = 21,                    /* YY_END  */
  YYSYMBOL_YY_READ = 22,                   /* YY_READ  */
  YYSYMBOL_YY_WRITE = 23,                  /* YY_WRITE  */
  YYSYMBOL_YY_WHILE = 24,                  /* YY_WHILE  */
  YYSYMBOL_YY_DO = 25,                     /* YY_DO  */
  YYSYMBOL_YY_ENDWHILE = 26,               /* YY_ENDWHILE  */
  YYSYMBOL_YY_REPEAT = 27,                 /* YY_REPEAT  */
  YYSYMBOL_YY_UNTIL = 28,                  /* YY_UNTIL  */
  YYSYMBOL_YY_IF = 29,                     /* YY_IF  */
  YYSYMBOL_YY_THEN = 30,                   /* YY_THEN  */
  YYSYMBOL_YY_ELSE = 31,                   /* YY_ELSE  */
  YYSYMBOL_YY_ENDIF = 32,                  /* YY_ENDIF  */
  YYSYMBOL_YY_L_BRACKET = 33,              /* YY_L_BRACKET  */
  YYSYMBOL_YY_R_BRACKET = 34,              /* YY_R_BRACKET  */
  YYSYMBOL_YY_TABLE = 35,                  /* YY_TABLE  */
  YYSYMBOL_YY_L_SQUARE_BRACKET = 36,       /* YY_L_SQUARE_BRACKET  */
  YYSYMBOL_YY_R_SQUARE_BRACKET = 37,       /* YY_R_SQUARE_BRACKET  */
  YYSYMBOL_YY_PIDENTIFIER = 38,            /* YY_PIDENTIFIER  */
  YYSYMBOL_YY_NUM = 39,                    /* YY_NUM  */
  YYSYMBOL_YY_ERROR = 40,                  /* YY_ERROR  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program_all = 42,               /* program_all  */
  YYSYMBOL_procedures = 43,                /* procedures  */
  YYSYMBOL_procedure = 44,                 /* procedure  */
  YYSYMBOL_procedure_declaration = 45,     /* procedure_declaration  */
  YYSYMBOL_procedure_end = 46,             /* procedure_end  */
  YYSYMBOL_proc_head = 47,                 /* proc_head  */
  YYSYMBOL_proc_call = 48,                 /* proc_call  */
  YYSYMBOL_main = 49,                      /* main  */
  YYSYMBOL_main_declaration = 50,          /* main_declaration  */
  YYSYMBOL_main_end = 51,                  /* main_end  */
  YYSYMBOL_commands = 52,                  /* commands  */
  YYSYMBOL_command = 53,                   /* command  */
  YYSYMBOL_if_declaration = 54,            /* if_declaration  */
  YYSYMBOL_if_end = 55,                    /* if_end  */
  YYSYMBOL_if_else_declaration = 56,       /* if_else_declaration  */
  YYSYMBOL_if_else_end = 57,               /* if_else_end  */
  YYSYMBOL_while_declare = 58,             /* while_declare  */
  YYSYMBOL_while_end = 59,                 /* while_end  */
  YYSYMBOL_repeat_until_declaration = 60,  /* repeat_until_declaration  */
  YYSYMBOL_repeat_until_end = 61,          /* repeat_until_end  */
  YYSYMBOL_declarations = 62,              /* declarations  */
  YYSYMBOL_args_decl = 63,                 /* args_decl  */
  YYSYMBOL_args = 64,                      /* args  */
  YYSYMBOL_expression = 65,                /* expression  */
  YYSYMBOL_condition = 66,                 /* condition  */
  YYSYMBOL_value = 67,                     /* value  */
  YYSYMBOL_identifier = 68                 /* identifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   177

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    94,    94,   101,   106,   112,   119,   126,   131,   138,
     145,   152,   159,   166,   170,   177,   181,   188,   192,   196,
     200,   204,   208,   212,   216,   224,   231,   238,   245,   252,
     259,   266,   273,   280,   284,   288,   292,   299,   303,   307,
     311,   318,   322,   329,   333,   337,   341,   345,   349,   356,
     360,   364,   368,   372,   376,   383,   387,   394,   398,   402
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "YY_SEMICOLON",
  "YY_COMMA", "YY_ADD", "YY_SUB", "YY_DIV", "YY_MOD", "YY_MUL",
  "YY_ASSIGN", "YY_EQ", "YY_NE", "YY_LT", "YY_GT", "YY_LE", "YY_GE",
  "YY_PROGRAM", "YY_PROCEDURE", "YY_IS", "YY_IN", "YY_END", "YY_READ",
  "YY_WRITE", "YY_WHILE", "YY_DO", "YY_ENDWHILE", "YY_REPEAT", "YY_UNTIL",
  "YY_IF", "YY_THEN", "YY_ELSE", "YY_ENDIF", "YY_L_BRACKET",
  "YY_R_BRACKET", "YY_TABLE", "YY_L_SQUARE_BRACKET", "YY_R_SQUARE_BRACKET",
  "YY_PIDENTIFIER", "YY_NUM", "YY_ERROR", "$accept", "program_all",
  "procedures", "procedure", "procedure_declaration", "procedure_end",
  "proc_head", "proc_call", "main", "main_declaration", "main_end",
  "commands", "command", "if_declaration", "if_end", "if_else_declaration",
  "if_else_end", "while_declare", "while_end", "repeat_until_declaration",
  "repeat_until_end", "declarations", "args_decl", "args", "expression",
  "condition", "value", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-60)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -60,    13,    21,   -60,    -4,   -60,   -60,     7,   -60,   -14,
     -60,     8,   -60,    28,   139,    45,   -60,     5,   -21,   -12,
      46,    18,   -60,   -60,   -60,    10,    82,     6,   -60,    18,
      18,   139,    77,    49,    56,   139,    57,   -60,     0,   139,
      12,    61,   101,   -60,   102,   -60,    71,    41,   -60,   -60,
     -60,   -60,   139,    38,    84,   165,   -60,    98,   110,   -60,
      18,    85,    95,    69,   -60,    20,   -60,    79,   139,   -60,
     -60,   -60,     3,    88,   106,   118,   -60,    18,    18,    18,
      18,    18,    18,   139,    18,    18,    18,    18,    18,   139,
      18,   141,   -60,   107,   -60,   111,   -60,   -60,    89,   113,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
      97,   -60,   -60,   -60,   -60,   -60,   131,   149,   -60,   122,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     6,     3,     0,     2,     0,
      12,     0,     5,     0,     0,    35,    11,     0,     0,     0,
       0,     0,    29,    31,    25,    57,     0,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    39,     0,     0,
       0,    57,     0,    55,     0,    56,     0,     0,    22,    14,
      15,    19,     0,     0,     0,    43,    20,     0,     0,    21,
       0,     0,    33,     0,    40,     0,     9,     0,     0,    23,
      24,    42,     0,     0,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,    13,     0,    37,     8,     0,     0,
      10,    59,    58,    28,    49,    50,    51,    52,    53,    54,
       0,    44,    45,    47,    48,    46,     0,     0,    17,     0,
      38,     7,    41,    27,    26,    30,    32,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,    47,   -27,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   145,   -60,   -60,   -59,   -25,   -11,   -18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,     7,    12,    13,    26,     8,     9,
      16,    27,    28,    29,    51,    52,    76,    30,    56,    31,
      59,    17,    38,    72,    53,    54,    55,    32
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      50,    91,    42,    45,    65,    57,    14,    99,    39,    34,
      44,    45,    45,     3,    36,    10,    34,    37,   104,   105,
     106,   107,   108,   109,    15,    35,    15,    49,    20,    21,
      22,    50,    68,    23,    66,    24,    50,   100,     4,     5,
      50,    18,    45,    46,    25,    11,    47,    19,    50,    77,
      78,    79,    80,    81,    82,    95,    41,    43,    96,    45,
      45,    45,    45,    45,    45,   117,    45,    45,    45,    45,
      45,    50,    45,   111,   112,   113,   114,   115,    58,    73,
      74,    33,    63,    50,    41,    48,    67,    60,    61,    50,
      94,    20,    21,    22,    62,    64,    23,    47,    24,    75,
      97,    20,    21,    22,    69,    70,    23,    25,    24,    71,
     121,    20,    21,    22,    83,    98,    23,    25,    24,    20,
      21,    22,    92,    89,    23,   101,    24,    25,   123,   124,
     110,    93,    20,    21,    22,    25,   116,    23,    90,    24,
      20,    21,    22,   102,   118,    23,   119,    24,    25,   120,
     103,   122,   126,    20,    21,    22,    25,   125,    23,   127,
      24,    20,    21,    22,    40,     0,    23,     0,    24,    25,
      84,    85,    86,    87,    88,     0,     0,    25
};

static const yytype_int8 yycheck[] =
{
      27,    60,    20,    21,     4,    30,    20,     4,    20,     4,
      21,    29,    30,     0,    35,    19,     4,    38,    77,    78,
      79,    80,    81,    82,    38,    20,    38,    21,    22,    23,
      24,    58,    20,    27,    34,    29,    63,    34,    17,    18,
      67,    33,    60,    33,    38,    38,    36,    19,    75,    11,
      12,    13,    14,    15,    16,    35,    38,    39,    38,    77,
      78,    79,    80,    81,    82,    90,    84,    85,    86,    87,
      88,    98,    90,    84,    85,    86,    87,    88,    31,    38,
      39,    36,    35,   110,    38,     3,    39,    10,    39,   116,
      21,    22,    23,    24,    38,    38,    27,    36,    29,    52,
      21,    22,    23,    24,     3,     3,    27,    38,    29,    38,
      21,    22,    23,    24,    30,    68,    27,    38,    29,    22,
      23,    24,    37,    25,    27,    37,    29,    38,    31,    32,
      83,    36,    22,    23,    24,    38,    89,    27,    28,    29,
      22,    23,    24,    37,     3,    27,    39,    29,    38,    38,
      32,    38,     3,    22,    23,    24,    38,    26,    27,    37,
      29,    22,    23,    24,    19,    -1,    27,    -1,    29,    38,
       5,     6,     7,     8,     9,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    42,    43,     0,    17,    18,    44,    45,    49,    50,
      19,    38,    46,    47,    20,    38,    51,    62,    33,    19,
      22,    23,    24,    27,    29,    38,    48,    52,    53,    54,
      58,    60,    68,    36,     4,    20,    35,    38,    63,    20,
      62,    38,    68,    39,    67,    68,    33,    36,     3,    21,
      53,    55,    56,    65,    66,    67,    59,    66,    52,    61,
      10,    39,    38,    52,    38,     4,    34,    52,    20,     3,
       3,    38,    64,    38,    39,    52,    57,    11,    12,    13,
      14,    15,    16,    30,     5,     6,     7,     8,     9,    25,
      28,    65,    37,    36,    21,    35,    38,    21,    52,     4,
      34,    37,    37,    32,    65,    65,    65,    65,    65,    65,
      52,    67,    67,    67,    67,    67,    52,    66,     3,    39,
      38,    21,    38,    31,    32,    26,     3,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    46,    46,    47,
      48,    49,    50,    51,    51,    52,    52,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    62,    62,    62,    63,    63,    63,
      63,    64,    64,    65,    65,    65,    65,    65,    65,    66,
      66,    66,    66,    66,    66,    67,    67,    68,    68,    68
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     6,     5,     4,
       4,     2,     2,     4,     3,     2,     1,     4,     3,     2,
       2,     2,     2,     3,     3,     1,     4,     4,     2,     1,
       4,     1,     4,     3,     6,     1,     4,     3,     4,     1,
       2,     3,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* program_all: procedures main  */
#line 95 "./src/parser.y"
    {
        compiler.getAsmGenerator().finishProgram();
    }
#line 1251 "./src/parser_tab.c"
    break;

  case 3: /* procedures: procedures procedure  */
#line 102 "./src/parser.y"
    {

    }
#line 1259 "./src/parser_tab.c"
    break;

  case 4: /* procedures: %empty  */
#line 106 "./src/parser.y"
    {

    }
#line 1267 "./src/parser_tab.c"
    break;

  case 5: /* procedure: procedure_declaration procedure_end  */
#line 113 "./src/parser.y"
    {
        
    }
#line 1275 "./src/parser_tab.c"
    break;

  case 6: /* procedure_declaration: YY_PROCEDURE  */
#line 120 "./src/parser.y"
    {

    }
#line 1283 "./src/parser_tab.c"
    break;

  case 7: /* procedure_end: proc_head YY_IS declarations YY_IN commands YY_END  */
#line 127 "./src/parser.y"
    {

    }
#line 1291 "./src/parser_tab.c"
    break;

  case 8: /* procedure_end: proc_head YY_IS YY_IN commands YY_END  */
#line 132 "./src/parser.y"
    {

    }
#line 1299 "./src/parser_tab.c"
    break;

  case 9: /* proc_head: YY_PIDENTIFIER YY_L_BRACKET args_decl YY_R_BRACKET  */
#line 139 "./src/parser.y"
    {

    }
#line 1307 "./src/parser_tab.c"
    break;

  case 10: /* proc_call: YY_PIDENTIFIER YY_L_BRACKET args YY_R_BRACKET  */
#line 146 "./src/parser.y"
    {

    }
#line 1315 "./src/parser_tab.c"
    break;

  case 11: /* main: main_declaration main_end  */
#line 153 "./src/parser.y"
    {

    }
#line 1323 "./src/parser_tab.c"
    break;

  case 12: /* main_declaration: YY_PROGRAM YY_IS  */
#line 160 "./src/parser.y"
    {

    }
#line 1331 "./src/parser_tab.c"
    break;

  case 13: /* main_end: declarations YY_IN commands YY_END  */
#line 167 "./src/parser.y"
    {

    }
#line 1339 "./src/parser_tab.c"
    break;

  case 14: /* main_end: YY_IN commands YY_END  */
#line 171 "./src/parser.y"
    {

    }
#line 1347 "./src/parser_tab.c"
    break;

  case 15: /* commands: commands command  */
#line 178 "./src/parser.y"
    {

    }
#line 1355 "./src/parser_tab.c"
    break;

  case 16: /* commands: command  */
#line 182 "./src/parser.y"
    {

    }
#line 1363 "./src/parser_tab.c"
    break;

  case 17: /* command: identifier YY_ASSIGN expression YY_SEMICOLON  */
#line 189 "./src/parser.y"
    {

    }
#line 1371 "./src/parser_tab.c"
    break;

  case 18: /* command: if_declaration if_else_declaration if_else_end  */
#line 193 "./src/parser.y"
    {

    }
#line 1379 "./src/parser_tab.c"
    break;

  case 19: /* command: if_declaration if_end  */
#line 197 "./src/parser.y"
    {

    }
#line 1387 "./src/parser_tab.c"
    break;

  case 20: /* command: while_declare while_end  */
#line 201 "./src/parser.y"
    {

    }
#line 1395 "./src/parser_tab.c"
    break;

  case 21: /* command: repeat_until_declaration repeat_until_end  */
#line 205 "./src/parser.y"
    {

    }
#line 1403 "./src/parser_tab.c"
    break;

  case 22: /* command: proc_call YY_SEMICOLON  */
#line 209 "./src/parser.y"
    {

    }
#line 1411 "./src/parser_tab.c"
    break;

  case 23: /* command: YY_READ identifier YY_SEMICOLON  */
#line 213 "./src/parser.y"
    {

    }
#line 1419 "./src/parser_tab.c"
    break;

  case 24: /* command: YY_WRITE value YY_SEMICOLON  */
#line 217 "./src/parser.y"
    {
        compiler.getAsmGenerator().write(*(yyvsp[-1].value));
        delete (yyvsp[-1].value);
    }
#line 1428 "./src/parser_tab.c"
    break;

  case 25: /* if_declaration: YY_IF  */
#line 225 "./src/parser.y"
    {

    }
#line 1436 "./src/parser_tab.c"
    break;

  case 26: /* if_end: condition YY_THEN commands YY_ENDIF  */
#line 232 "./src/parser.y"
    {

    }
#line 1444 "./src/parser_tab.c"
    break;

  case 27: /* if_else_declaration: condition YY_THEN commands YY_ELSE  */
#line 239 "./src/parser.y"
    {

    }
#line 1452 "./src/parser_tab.c"
    break;

  case 28: /* if_else_end: commands YY_ENDIF  */
#line 246 "./src/parser.y"
    {

    }
#line 1460 "./src/parser_tab.c"
    break;

  case 29: /* while_declare: YY_WHILE  */
#line 253 "./src/parser.y"
    {

    }
#line 1468 "./src/parser_tab.c"
    break;

  case 30: /* while_end: condition YY_DO commands YY_ENDWHILE  */
#line 260 "./src/parser.y"
    {

    }
#line 1476 "./src/parser_tab.c"
    break;

  case 31: /* repeat_until_declaration: YY_REPEAT  */
#line 267 "./src/parser.y"
    {

    }
#line 1484 "./src/parser_tab.c"
    break;

  case 32: /* repeat_until_end: commands YY_UNTIL condition YY_SEMICOLON  */
#line 274 "./src/parser.y"
    {

    }
#line 1492 "./src/parser_tab.c"
    break;

  case 33: /* declarations: declarations YY_COMMA YY_PIDENTIFIER  */
#line 281 "./src/parser.y"
    {

    }
#line 1500 "./src/parser_tab.c"
    break;

  case 34: /* declarations: declarations YY_COMMA YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET  */
#line 285 "./src/parser.y"
    {

    }
#line 1508 "./src/parser_tab.c"
    break;

  case 35: /* declarations: YY_PIDENTIFIER  */
#line 289 "./src/parser.y"
    {

    }
#line 1516 "./src/parser_tab.c"
    break;

  case 36: /* declarations: YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET  */
#line 293 "./src/parser.y"
    {

    }
#line 1524 "./src/parser_tab.c"
    break;

  case 37: /* args_decl: args_decl YY_COMMA YY_PIDENTIFIER  */
#line 300 "./src/parser.y"
    {

    }
#line 1532 "./src/parser_tab.c"
    break;

  case 38: /* args_decl: args_decl YY_COMMA YY_TABLE YY_PIDENTIFIER  */
#line 304 "./src/parser.y"
    {

    }
#line 1540 "./src/parser_tab.c"
    break;

  case 39: /* args_decl: YY_PIDENTIFIER  */
#line 308 "./src/parser.y"
    {

    }
#line 1548 "./src/parser_tab.c"
    break;

  case 40: /* args_decl: YY_TABLE YY_PIDENTIFIER  */
#line 312 "./src/parser.y"
    {

    }
#line 1556 "./src/parser_tab.c"
    break;

  case 41: /* args: args YY_COMMA YY_PIDENTIFIER  */
#line 319 "./src/parser.y"
    {

    }
#line 1564 "./src/parser_tab.c"
    break;

  case 42: /* args: YY_PIDENTIFIER  */
#line 323 "./src/parser.y"
    {

    }
#line 1572 "./src/parser_tab.c"
    break;

  case 43: /* expression: value  */
#line 330 "./src/parser.y"
    {

    }
#line 1580 "./src/parser_tab.c"
    break;

  case 44: /* expression: value YY_ADD value  */
#line 334 "./src/parser.y"
    {

    }
#line 1588 "./src/parser_tab.c"
    break;

  case 45: /* expression: value YY_SUB value  */
#line 338 "./src/parser.y"
    {

    }
#line 1596 "./src/parser_tab.c"
    break;

  case 46: /* expression: value YY_MUL value  */
#line 342 "./src/parser.y"
    {

    }
#line 1604 "./src/parser_tab.c"
    break;

  case 47: /* expression: value YY_DIV value  */
#line 346 "./src/parser.y"
    {

    }
#line 1612 "./src/parser_tab.c"
    break;

  case 48: /* expression: value YY_MOD value  */
#line 350 "./src/parser.y"
    {

    }
#line 1620 "./src/parser_tab.c"
    break;

  case 49: /* condition: expression YY_EQ expression  */
#line 357 "./src/parser.y"
    {

    }
#line 1628 "./src/parser_tab.c"
    break;

  case 50: /* condition: expression YY_NE expression  */
#line 361 "./src/parser.y"
    {

    }
#line 1636 "./src/parser_tab.c"
    break;

  case 51: /* condition: expression YY_LT expression  */
#line 365 "./src/parser.y"
    {

    }
#line 1644 "./src/parser_tab.c"
    break;

  case 52: /* condition: expression YY_GT expression  */
#line 369 "./src/parser.y"
    {

    }
#line 1652 "./src/parser_tab.c"
    break;

  case 53: /* condition: expression YY_LE expression  */
#line 373 "./src/parser.y"
    {

    }
#line 1660 "./src/parser_tab.c"
    break;

  case 54: /* condition: expression YY_GE expression  */
#line 377 "./src/parser.y"
    {

    }
#line 1668 "./src/parser_tab.c"
    break;

  case 55: /* value: YY_NUM  */
#line 384 "./src/parser.y"
    {
        (yyval.value) = new Rvalue((yyvsp[0].ptoken).val);
    }
#line 1676 "./src/parser_tab.c"
    break;

  case 56: /* value: identifier  */
#line 388 "./src/parser.y"
    {

    }
#line 1684 "./src/parser_tab.c"
    break;

  case 57: /* identifier: YY_PIDENTIFIER  */
#line 395 "./src/parser.y"
    {

    }
#line 1692 "./src/parser_tab.c"
    break;

  case 58: /* identifier: YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET  */
#line 399 "./src/parser.y"
    {

    }
#line 1700 "./src/parser_tab.c"
    break;

  case 59: /* identifier: YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_PIDENTIFIER YY_R_SQUARE_BRACKET  */
#line 403 "./src/parser.y"
    {

    }
#line 1708 "./src/parser_tab.c"
    break;


#line 1712 "./src/parser_tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 408 "./src/parser.y"


static void yyerror(const char* msg)
{
    std::cerr << "BLAD: " << msg << " w linii " << yylval.ptoken.line << std::endl;
}

int compile(const char* inFile, const char* outFile)
{
    yyin = fopen(inFile, "r");
    const int ret = yyparse();
    fclose(yyin);

    std::ofstream outstream;
    outstream.open(outFile);

    compiler.getAsmGenerator().finishCodeGeneration();
    const std::string code = compiler.getAsmGenerator().getGeneratedCode();

    outstream << code << std::endl;

    return ret;
}