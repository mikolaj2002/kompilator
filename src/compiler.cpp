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

void Compiler::warning(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    va_end(args);
}

void Compiler::assertDeclaration(const std::string& name, uint64_t line) {
    if (!getVarManager().isVariableDeclared(name))
        this->error("[COMPILER] Error: Undeclared variable %s in line %" PRIu64
                    "\n",
                    name.c_str(), line);
}

void Compiler::assertRedeclaration(const std::string& name, uint64_t line) {
    if (getVarManager().isVariableDeclared(name))
        this->error(
            "[COMPILER] Error: Redeclaration of variable %s in line %" PRIu64
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
         lval->getType() != Value::VALTYPE_LVALUE_ARRAY)) {
        std::string typeStr = "variable";
        if (lval->getType() == Value::VALTYPE_LVALUE_ARRAY ||
            lval->getType() == Value::VALTYPE_POINTER_ARRAY)
            typeStr = "array";

        this->error(
            "[COMPILER] Error: Incorrect usage of %s %s in line %" PRIu64 "\n",
            typeStr.c_str(), name.c_str(), line);
    }
}

void Compiler::assertInitalization(Value* val, uint64_t line) {
    if (val->getType() == Value::VALTYPE_LVALUE_VAR) {
        Lvalue* lval = getVarManager()
                           .getVariable(dynamic_cast<Lvalue*>(val)->getName())
                           .get();
        if (!lval->isInit())
            this->warning(
                "[COMPILER] Warning: Variable %s might not be initialized, "
                "used in line %" PRIu64 "\n",
                lval->getName().c_str(), line);
    }
}

void Compiler::assertProcedureDeclaration(const std::string& name,
                                          uint64_t line) {
    if (!getProcManager().isProcedureDeclared(name))
        this->error("[COMPILER] Error: Undeclared procedure %s in line %" PRIu64
                    "\n",
                    name.c_str(), line);
}

void Compiler::assertProcedureRedeclaration(const std::string& name,
                                            uint64_t line) {
    if (getProcManager().isProcedureDeclared(name))
        this->error(
            "[COMPILER] Error: Redeclaration of procedure %s in line %" PRIu64
            "\n",
            name.c_str(), line);
}

void Compiler::assertProcedureRecursion(const std::string& name,
                                        uint64_t line) {
    if (getProcManager().getCurrentProcedure().getName() == name)
        this->error("[COMPILER] Error: Using recursion in line %" PRIu64 "\n",
                    line);
}

void Compiler::assertProcCallArgCount(const std::string& name,
                                      size_t givenArguments, uint64_t line) {
    if (getProcManager().getProcedure(name).getArgumentNames().size() !=
        givenArguments)
        this->error(
            "[COMPILER] Error: Calling procedure %s with wrong number of "
            "arguments in "
            "line %" PRIu64 "\n",
            name.c_str(), line);
}
void Compiler::assertProcCallArgType(const std::string& name, size_t argNumber,
                                     Value::valtype_t type, uint64_t line) {
    Procedure& proc = getProcManager().getProcedure(name);

    if (proc.getArgumentNames().size() < argNumber + 1)
        this->error(
            "[COMPILER] Error: Calling procedure %s with wrong number of "
            "arguments in "
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
            "[COMPILER] Error: Incorrect procedure %s call parameter in line "
            "%" PRIu64 "\n",
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