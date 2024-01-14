#include <cinttypes>
#include <compiler.hpp>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <lvalue.hpp>

void Compiler::error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    va_end(args);

    exit(1);
}

void Compiler::assertDeclaration(const std::string& name, uint64_t line) {
    if (!getVarManager().isVariableDeclared(name))
        this->error("[COMPILER] Undeclared variable %s in line %" PRIu64 "\n",
                    name.c_str(), line);
}

void Compiler::assertRedeclaration(const std::string& name, uint64_t line) {
    if (getVarManager().isVariableDeclared(name))
        this->error("[COMPILER] Redeclaration of variable %s in line %" PRIu64
                    "\n",
                    name.c_str(), line);
}

void Compiler::assertUsage(const std::string& name, Value::valtype_t type,
                           uint64_t line) {
    Lvalue* lval = getVarManager().getVariable(name).get();
    if ((type == Value::VALTYPE_LVALUE_VAR &&
         lval->getType() != Value::VALTYPE_POINTER_VAR &&
         lval->getType() != Value::VALTYPE_LVALUE_VAR) ||
        (type == Value::VALTYPE_LVALUE_ARRAY &&
         lval->getType() != Value::VALTYPE_POINTER_ARRAY &&
         lval->getType() != Value::VALTYPE_LVALUE_ARRAY))
        this->error("[COMPILER] Incorrect usage of variable %s in line %" PRIu64
                    "\n",
                    name.c_str(), line);
}

void Compiler::assertInitalization(Value* val, uint64_t line) {
    if (val->getType() == Value::VALTYPE_LVALUE_VAR) {
        Lvalue* lval = getVarManager()
                           .getVariable(dynamic_cast<Lvalue*>(val)->getName())
                           .get();
        if (!lval->isInit())
            this->error(
                "[COMPILER] Use of uninitialized variable %s in line %" PRIu64
                "\n",
                lval->getName().c_str(), line);
    }
}

void Compiler::assertMutuable(Value* val, uint64_t line) {
    // check if variable can be modyfied, Rval and Arrays cannot be by gramma
    // rules, so there is no need to check it here
    if (val->getType() == Value::VALTYPE_LVALUE_VAR) {
        Lvalue* lval = getVarManager()
                           .getVariable(dynamic_cast<Lvalue*>(val)->getName())
                           .get();
        if (!lval->isMutuable())
            this->error(
                "BLAD: Proba nadpisania zmiennej %s typu const w linii %" PRIu64
                "\n",
                lval->getName().c_str(), line);
    }
}

void Compiler::assertProcedureDeclaration(const std::string& name,
                                          uint64_t line) {
    if (!getProcManager().isProcedureDeclared(name))
        this->error("[COMPILER] Undeclared procedure %s in line %" PRIu64 "\n",
                    name.c_str(), line);
}

void Compiler::assertProcedureRedeclaration(const std::string& name,
                                            uint64_t line) {
    if (getProcManager().isProcedureDeclared(name))
        this->error("[COMPILER] Redeclaration of procedure %s in line %" PRIu64
                    "\n",
                    name.c_str(), line);
}

void Compiler::assertProcedureRecursion(const std::string& name,
                                        uint64_t line) {
    if (getProcManager().getCurrentProcedure().getName() == name)
        this->error("[COMPILER] Using recursion in line %" PRIu64 "\n", line);
}

void Compiler::assertProcCallArgCount(const std::string& name,
                                      size_t givenArguments, uint64_t line) {
    if (getProcManager().getProcedure(name).getArgumentNames().size() !=
        givenArguments)
        this->error(
            "[COMPILER] Calling procedure %s with wrong number of arguments in "
            "line %" PRIu64 "\n",
            name.c_str(), line);
}
void Compiler::assertProcCallArgType(const std::string& name, size_t argNumber,
                                     Value::valtype_t type, uint64_t line) {
    Procedure& proc = getProcManager().getProcedure(name);

    if (proc.getArgumentNames().size() < argNumber + 1)
        this->error(
            "[COMPILER] Calling procedure %s with wrong number of arguments in "
            "line %" PRIu64 "\n",
            name.c_str(), line);

    std::string varName = proc.getArgumentNames()[argNumber];
    Lvalue* lval = proc.getVarManager().getVariable(varName).get();
    if ((lval->getType() == Value::VALTYPE_POINTER_VAR &&
         type != Value::VALTYPE_LVALUE_VAR &&
         type != Value::VALTYPE_POINTER_VAR) ||
        (lval->getType() == Value::VALTYPE_POINTER_ARRAY &&
         type != Value::VALTYPE_LVALUE_ARRAY &&
         type != Value::VALTYPE_POINTER_ARRAY))
        this->error(
            "[COMPILER] Incorrect procedure %s call parameter in line %" PRIu64
            "\n",
            name.c_str(), line);
}

void Compiler::initVariable(Value* val) {
    if (val->getType() == Value::VALTYPE_LVALUE_VAR) {
        Lvalue* lval = getVarManager()
                           .getVariable(dynamic_cast<Lvalue*>(val)->getName())
                           .get();
        lval->setInit();
    }
}