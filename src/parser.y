%{
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdarg>
#include <cinttypes>

#include <architecture.hpp>
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

%}

%code requires
{
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

%type   <ptoken>    YY_SEMICOLON YY_COMMA
%type   <ptoken> 	YY_ADD YY_SUB YY_DIV YY_MOD YY_MUL
%type   <ptoken>	YY_ASSIGN
%type   <ptoken>	YY_EQ YY_NE YY_LT YY_GT YY_LE YY_GE
%type   <ptoken>	YY_PROGRAM YY_PROCEDURE YY_IS YY_IN YY_END
%type   <ptoken>	YY_READ YY_WRITE
%type   <ptoken>	YY_WHILE YY_DO YY_ENDWHILE
%type   <ptoken>    YY_REPEAT YY_UNTIL
%type   <ptoken>	YY_IF YY_THEN YY_ELSE YY_ENDIF
%type   <ptoken>	YY_L_BRACKET YY_R_BRACKET
%type   <ptoken>    YY_TABLE YY_L_SQUARE_BRACKET YY_R_SQUARE_BRACKET
%type   <ptoken>	YY_PIDENTIFIER YY_NUM
%type   <ptoken>	YY_ERROR

%type   <value>     value identifier

%%

program_all:
    procedures main
    {
        compiler.getAsmGenerator().finishProgram();
    }
;

procedures:
    procedures procedure
    {

    }
    | %empty
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
    identifier YY_ASSIGN expression YY_SEMICOLON
    {
        Lvalue* lval = dynamic_cast<Lvalue*>($1);

        // in RetVal Register we have value from expression, so just store it
        Register& retval = Architecture::getRetValRegister();

        compiler.getAsmGenerator().store(*lval, retval);

        retval.unlock();

        // after assigment set init flag
        compiler.initVariable($1);

        delete $1;
    }
    | if_condition if_else if_else_end
    {

    }
    | if_condition if_end
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
        Lvalue* lval = dynamic_cast<Lvalue*>($2);

        compiler.getAsmGenerator().read(*lval);

        compiler.initVariable($2);

        delete $2;
    }
    | YY_WRITE value YY_SEMICOLON
    {
        compiler.getAsmGenerator().write(*$2);
        delete $2;
    }
;

if_condition:
    YY_IF condition YY_THEN
    {

    }
;

if_end:
    commands YY_ENDIF
    {
        ConditionalBranch branch = compiler.getBranchManager().getBranchFromStack();
        compiler.getAsmGenerator().ifInsertJumpPoint(branch);
    }
;

if_else:
    commands YY_ELSE
    {
        ConditionalBranch jumpFromIf = ConditionalBranch(compiler.getAsmGenerator().getLabelManager().createLabel("JUMP_AFTER_IF"));
        compiler.getAsmGenerator().ifSkipElse(jumpFromIf);

        ConditionalBranch branch = compiler.getBranchManager().getBranchFromStack();

        compiler.getAsmGenerator().ifInsertJumpPoint(branch);

        compiler.getBranchManager().addBranch(jumpFromIf);
    }
;

if_else_end:
    commands YY_ENDIF
    {
        ConditionalBranch branch = compiler.getBranchManager().getBranchFromStack();
        compiler.getAsmGenerator().ifInsertJumpPoint(branch);
    }
;

pre_while:
    YY_WHILE
    {
        const std::string labelStart = compiler.getAsmGenerator().getLabelManager().createLabel("WHILE_START");

        Loop* loop = new LoopWhile(labelStart, std::string("to_be_defined_later"));
        compiler.getLoopManager().addLoopToStack(loop);

        compiler.getAsmGenerator().startWhileLoop(*dynamic_cast<LoopWhile*>(loop));
    }
;

while_declare:
    pre_while condition YY_DO
    {
        ConditionalBranch branch = compiler.getBranchManager().getBranchFromStack();
        compiler.getLoopManager().getLoopTopStack()->setEndLabel(branch.getLabelFalse());
    }
;

while_end:
    commands YY_ENDWHILE
    {
        Loop* loop = compiler.getLoopManager().getLoopFromStack();
        compiler.getAsmGenerator().doWhileLoop(*dynamic_cast<LoopWhile*>(loop));
        delete loop;
    }
;

repeat_until_declaration:
    YY_REPEAT
    {
        const std::string labelStart = compiler.getAsmGenerator().getLabelManager().createLabel("REPEAT_START");

        Loop* loop = new LoopUntil(labelStart, std::string("to_be_defined_later"));
        compiler.getLoopManager().addLoopToStack(loop);

        compiler.getAsmGenerator().startUntilLoop(*dynamic_cast<LoopUntil*>(loop));
    }
;

repeat_until_end:
    commands YY_UNTIL condition YY_SEMICOLON
    {
        Loop* loop = compiler.getLoopManager().getLoopFromStack();

        ConditionalBranch branch = compiler.getBranchManager().getBranchFromStack();
        loop->setEndLabel(branch.getLabelFalse());

        compiler.getAsmGenerator().doUntilLoop(*dynamic_cast<LoopUntil*>(loop));

        delete loop;
    }
;

declarations:
    declarations YY_COMMA YY_PIDENTIFIER
    {
        Lvalue* var = new LvalueVar(*($3.str), true);
        compiler.getVarManager().declareVariable(var);

        delete $3.str;
    }
    | declarations YY_COMMA YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET
    {
        Lvalue* var = new LvalueArray(*($3.str), $5.val);
        compiler.getVarManager().declareVariable(var);

        delete $3.str;
    }
    | YY_PIDENTIFIER
    {
        Lvalue* var = new LvalueVar(*($1.str), true);
        compiler.getVarManager().declareVariable(var);

        delete $1.str;
    }
    | YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET
    {
        Lvalue* var = new LvalueArray(*($1.str), $3.val);
        compiler.getVarManager().declareVariable(var);

        delete $1.str;
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
        Register& retval = Architecture::getRetValRegister();
        retval.lock();

        compiler.getAsmGenerator().load(retval, *$1);

        delete $1;
    }
    | value YY_ADD value
    {
        compiler.getAsmGenerator().add(*$1, *$3);

        delete $1;
        delete $3;
    }
    | value YY_SUB value
    {
        compiler.getAsmGenerator().sub(*$3, *$1);

        delete $1;
        delete $3;
    }
    | value YY_MUL value
    {
        compiler.getAsmGenerator().mul(*$1, *$3);

        delete $1;
        delete $3;
    }
    | value YY_DIV value
    {
        compiler.getAsmGenerator().div(*$1, *$3);

        delete $1;
        delete $3;
    }
    | value YY_MOD value
    {
        compiler.getAsmGenerator().mod(*$1, *$3);

        delete $1;
        delete $3;
    }
;

condition:
    value YY_EQ value
    {
        ConditionalBranch branch = compiler.getAsmGenerator().branchEq(*$1, *$3);
        compiler.getBranchManager().addBranch(branch);

        delete $1;
        delete $3;
    }
    | value YY_NE value
    {
        ConditionalBranch branch = compiler.getAsmGenerator().branchNeq(*$1, *$3);
        compiler.getBranchManager().addBranch(branch);

        delete $1;
        delete $3;
    }
    | value YY_LT value
    {
        ConditionalBranch branch = compiler.getAsmGenerator().branchLt(*$1, *$3);
        compiler.getBranchManager().addBranch(branch);

        delete $1;
        delete $3;
    }
    | value YY_GT value
    {
        ConditionalBranch branch = compiler.getAsmGenerator().branchGt(*$1, *$3);
        compiler.getBranchManager().addBranch(branch);

        delete $1;
        delete $3;
    }
    | value YY_LE value
    {
        ConditionalBranch branch = compiler.getAsmGenerator().branchLeq(*$1, *$3);
        compiler.getBranchManager().addBranch(branch);

        delete $1;
        delete $3;
    }
    | value YY_GE value
    {
        ConditionalBranch branch = compiler.getAsmGenerator().branchGeq(*$1, *$3);
        compiler.getBranchManager().addBranch(branch);

        delete $1;
        delete $3;
    }
;

value:
    YY_NUM
    {
        $$ = new Rvalue($1.val);
    }
    | identifier
    {

    }
;

identifier:
    YY_PIDENTIFIER
    {
        LvalueVar* var = dynamic_cast<LvalueVar*>(compiler.getVarManager().getVariable(*($1.str)).get());
        $$ = new LvalueVar(*var);

        delete $1.str;
    }
    | YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_NUM YY_R_SQUARE_BRACKET
    {
        LvalueArray* array = dynamic_cast<LvalueArray*>(compiler.getVarManager().getVariable(*($1.str)).get());
        auto val = std::shared_ptr<Value>(new Rvalue($3.val));

        LvalueArray* forward =  new LvalueArray(*array);
        forward->setAccessElement(val);
        $$ = forward;

        delete $1.str;
    }
    | YY_PIDENTIFIER YY_L_SQUARE_BRACKET YY_PIDENTIFIER YY_R_SQUARE_BRACKET
    {
        LvalueArray* array = dynamic_cast<LvalueArray*>(compiler.getVarManager().getVariable(*($1.str)).get());
        auto var = compiler.getVarManager().getVariable(*($3.str));

        LvalueArray* forward = new LvalueArray(*array);
        forward->setAccessElement(var);
        $$ = forward;

        delete $1.str;
        delete $3.str;
    }
;

%%

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