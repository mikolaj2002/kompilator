/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INC_PARSER_TAB_H_INCLUDED
# define YY_YY_INC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 35 "./src/parser.y"

    #include <cstdint>
    #include <cstring>

    #include <architecture.hpp>
    #include <compiler.hpp>
    #include <value.hpp>
    #include <rvalue.hpp>
    #include <lvalue.hpp>
    #include <lvalue_var.hpp>
    #include <lvalue_array.hpp>
    #include <loop.hpp>

    typedef struct Parser_token
    {
        uint64_t val;
        uint64_t line;
        std::string* str; // Yacc needs pointer instead of class
    } Parser_token;


#line 71 "./inc/parser_tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    YY_SEMICOLON = 258,            /* YY_SEMICOLON  */
    YY_COMMA = 259,                /* YY_COMMA  */
    YY_ADD = 260,                  /* YY_ADD  */
    YY_SUB = 261,                  /* YY_SUB  */
    YY_DIV = 262,                  /* YY_DIV  */
    YY_MOD = 263,                  /* YY_MOD  */
    YY_MUL = 264,                  /* YY_MUL  */
    YY_ASSIGN = 265,               /* YY_ASSIGN  */
    YY_EQ = 266,                   /* YY_EQ  */
    YY_NE = 267,                   /* YY_NE  */
    YY_LT = 268,                   /* YY_LT  */
    YY_GT = 269,                   /* YY_GT  */
    YY_LE = 270,                   /* YY_LE  */
    YY_GE = 271,                   /* YY_GE  */
    YY_PROGRAM = 272,              /* YY_PROGRAM  */
    YY_PROCEDURE = 273,            /* YY_PROCEDURE  */
    YY_IS = 274,                   /* YY_IS  */
    YY_IN = 275,                   /* YY_IN  */
    YY_END = 276,                  /* YY_END  */
    YY_READ = 277,                 /* YY_READ  */
    YY_WRITE = 278,                /* YY_WRITE  */
    YY_WHILE = 279,                /* YY_WHILE  */
    YY_DO = 280,                   /* YY_DO  */
    YY_ENDWHILE = 281,             /* YY_ENDWHILE  */
    YY_REPEAT = 282,               /* YY_REPEAT  */
    YY_UNTIL = 283,                /* YY_UNTIL  */
    YY_IF = 284,                   /* YY_IF  */
    YY_THEN = 285,                 /* YY_THEN  */
    YY_ELSE = 286,                 /* YY_ELSE  */
    YY_ENDIF = 287,                /* YY_ENDIF  */
    YY_L_BRACKET = 288,            /* YY_L_BRACKET  */
    YY_R_BRACKET = 289,            /* YY_R_BRACKET  */
    YY_TABLE = 290,                /* YY_TABLE  */
    YY_L_SQUARE_BRACKET = 291,     /* YY_L_SQUARE_BRACKET  */
    YY_R_SQUARE_BRACKET = 292,     /* YY_R_SQUARE_BRACKET  */
    YY_PIDENTIFIER = 293,          /* YY_PIDENTIFIER  */
    YY_NUM = 294,                  /* YY_NUM  */
    YY_ERROR = 295                 /* YY_ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 58 "./src/parser.y"

    Parser_token ptoken;
    Value* value; // abstract class

#line 133 "./inc/parser_tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INC_PARSER_TAB_H_INCLUDED  */
