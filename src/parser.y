%{
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdarg>
#include <cinttypes>

#include <compiler.hpp>
#include <value.hpp>
#include <rvalue.hpp>
#include <lvalue.hpp>
#include <lvalue-var.hpp>
#include <lvalue-array.hpp>

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

%}

%code requires
{
    #include <cstdint>
    #include <cstring>

    #include <compiler.hpp>
    #include <value.hpp>
    #include <rvalue.hpp>
    #include <lvalue.hpp>
    #include <lvalue-var.hpp>
    #include <lvalue-array.hpp>
    #include <loop.hpp>
    #include <loop-for.hpp>

    typedef struct Parser_token
    {
        uint64_t val;
        uint64_t line;
        std::string* str; // Yacc needs pointer instead of class
    } Parser_token;

}

%union
{
    Parser_token ptoken;
    Value* value; // abstract class
}

%token	YY_SEMICOLON YY_COMMA
%token 	YY_ADD YY_SUB YY_DIV YY_MOD YY_MUL
%token	YY_ASSIGN
%token	YY_EQ YY_NE YY_LT YY_GT YY_LE YY_GE
%token	YY_PROGRAM YY_PROCEDURE YY_IS YY_IN YY_END
%token	YY_READ YY_WRITE
%token	YY_WHILE YY_DO YY_ENDWHILE
%token  YY_REPEAT YY_UNTIL
%token	YY_IF YY_THEN YY_ELSE YY_ENDIF
%token	YY_L_BRACKET YY_R_BRACKET
%token  YY_TABLE YY_L_SQUARE_BRACKET YY_R_SQUARE_BRACKET
%token	YY_PIDENTIFIER YY_NUM
%token	YY_ERROR

%token	<ptoken>    YY_SEMICOLON YY_COMMA
%token 	<ptoken>    YY_ADD YY_SUB YY_DIV YY_MOD YY_MUL
%token	<ptoken>    YY_ASSIGN
%token	<ptoken>    YY_EQ YY_NE YY_LT YY_GT YY_LE YY_GE
%token	<ptoken>    YY_PROGRAM YY_PROCEDURE YY_IS YY_IN YY_END
%token	<ptoken>    YY_READ YY_WRITE
%token	<ptoken>    YY_WHILE YY_DO YY_ENDWHILE
%token  <ptoken>    YY_REPEAT YY_UNTIL
%token	<ptoken>    YY_IF YY_THEN YY_ELSE YY_ENDIF
%token	<ptoken>    YY_L_BRACKET YY_R_BRACKET
%token  <ptoken>    YY_TABLE YY_L_SQUARE_BRACKET YY_R_SQUARE_BRACKET
%token	<ptoken>    YY_PIDENTIFIER YY_NUM
%token	<ptoken>    YY_ERROR

%%

program_all:
    procedures main
    {

    }
;

procedures:
    procedures procedure
    {

    }
    |
    {

    }
;

procedure:
    procedure_declaration procedure_end
    {
        
    }
;

procedure_declaration:
    YY_PROCEDURE
    {

    }
;

procedure_end:
    proc_head YY_IS declarations YY_IN commands YY_END
    {

    }
    |
    proc_head YY_IS YY_IN commands YY_END
    {

    }
;

proc_head:
    YY_PIDENTIFIER YY_L_BRACKET args_decl YY_R_BRACKET
    {

    }
;

proc_call:
    YY_PIDENTIFIER YY_L_BRACKET args YY_R_BRACKET
    {

    }
;

main:
    main_declaration main_end
    {

    }
;

main_declaration:
    YY_PROGRAM YY_IS
    {

    }
;

main_end:
    declarations YY_IN commands YY_END
    {

    }
    | YY_IN commands YY_END
    {

    }
;

commands:
    commands command
    {

    }
    | command
    {

    }
;

command:
    identifier YY_ASSIGN expr YY_SEMICOLON
    {

    }
    | if_declaration if_else_declaration if_else_end
    {

    }
    | if_declaration if_end
    {

    }
    | while_declare while_end
    {

    }
    | repeat_until_declaration repeat_until_end
    {

    }
    | proc_call YY_SEMICOLON
    {

    }
    | YY_READ identifier YY_SEMICOLON
    {

    }
    | YY_WRITE value YY_SEMICOLON
    {

    }
;

if_declaration:
    YY_IF
    {

    }
;

if_end:
    condition YY_THEN commands YY_ENDIF
    {

    }
;

if_else_declaration:
    condition YY_THEN commands YY_ELSE
    {

    }
;

if_else_end:
    commands YY_ENDIF
    {

    }
;

while_declare:
    YY_WHILE
    {

    }
;

while_end:
    condition YY_DO commands YY_ENDWHILE
    {

    }
;

repeat_until_declaration:
    YY_REPEAT
    {

    }
;

repeat_until_end:
    commands YY_UNTIL condition YY_SEMICOLON
    {

    }
;

declarations:
    declarations YY_COMMA YY_PIDENTIFIER
    {

    }
    | declarations YY_COMMA YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET
    {

    }
    | YY_PIDENTIFIER
    {

    }
    | YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET
    {

    }
;

args_decl:
    args_decl YY_COMMA YY_PIDENTIFIER
    {

    }
    | args_decl YY_COMMA YY_TABLE YY_PIDENTIFIER
    {

    }
    | YY_PIDENTIFIER
    {

    }
    | YY_TABLE YY_PIDENTIFIER
    {

    }
;

args:
    args YY_COMMA YY_PIDENTIFIER
    {

    }
    | YY_PIDENTIFIER
    {

    }
;

expression:
    value
    {

    }
    | value YY_ADD value
    {

    }
    | value YY_SUB value
    {

    }
    | value YY_MUL value
    {

    }
    | value YY_DIV value
    {

    }
    | value YY_MOD value
    {

    }
;

condition:
    expression YY_EQ expression
    {

    }
    | expression YY_NE expression
    {

    }
    | expression YY_LT expression
    {

    }
    | expression YY_GT expression
    {

    }
    | expression YY_LE expression
    {

    }
    | expression YY_GE expression
    {

    }
;

value:
    YY_NUM
    {

    }
    | identifier
    {

    }
;

identifier:
    YY_PIDENTIFIER
    {

    }
    | YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET
    {

    }
    | YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_PIDENTIFIER YY_R_SQUARE_BRACKET
    {

    }
;

%%

static void yyerror(const char* msg)
{
    std::cerr << "BLAD: " << msg << " w linii " << yylval.ptoken.line << std::endl;
}

int compile(const char* in_file, const char* out_file)
{
    yyin = fopen(in_file, "r");
    const int ret = yyparse();
    fclose(yyin);

    std::ofstream outstream;
    outstream.open(out_file);

    compiler.get_asm_generator().finish_code_generation();
    const std::string code = compiler.get_asm_generator().get_generated_code();

    outstream << code << std::endl;

    return ret;
}