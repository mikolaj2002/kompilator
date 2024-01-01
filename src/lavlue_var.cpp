#include <lvalue_var.hpp>

LvalueVar::LvalueVar(const std::string& name, bool isMutuable)
    : Lvalue(name, isMutuable, VALTYPE_LVALUE_VAR) {}

LvalueVar::LvalueVar(const LvalueVar& var)
    : Lvalue(var.getName(), var.isMutuable(), var.getType(), var.getAddr()) {}