#include <cinttypes>
#include <compiler.hpp>
#include <cstdarg>
#include <cstdio>
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
        this->error("BLAD: Niezadeklarowana zmienna %s w linii %" PRIu64 "\n",
                    name.c_str(), line);
}

void Compiler::assertRedeclaration(const std::string& name, uint64_t line) {
    if (getVarManager().isVariableDeclared(name))
        this->error("BLAD: Redeklaracja zmiennej %s w linii %" PRIu64 "\n",
                    name.c_str(), line);
}

void Compiler::assertUsage(const std::string& name, Value::valtype_t type,
                           uint64_t line) {
    Lvalue* lval = getVarManager().getVariable(name).get();
    if (lval->getType() != type)
        this->error("BLAD: Nieprawidlowe uzycie zmiennej %s w linii %" PRIu64
                    "\n",
                    name.c_str(), line);
}

void Compiler::assertInitalization(Value* val, uint64_t line) {
    // check if variable has been inited, Rval and Arrays are always inited
    if (val->getType() == Value::VALTYPE_LVALUE_VAR) {
        Lvalue* lval = getVarManager()
                           .getVariable(dynamic_cast<Lvalue*>(val)->getName())
                           .get();
        if (!lval->isInit())
            this->error(
                "BLAD: Uzycie zmiennej %s bez inicjalizacji w linii %" PRIu64
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

void Compiler::initVariable(Value* val) {
    if (val->getType() == Value::VALTYPE_LVALUE_VAR) {
        Lvalue* lval = getVarManager()
                           .getVariable(dynamic_cast<Lvalue*>(val)->getName())
                           .get();
        lval->setInit();
    }
}