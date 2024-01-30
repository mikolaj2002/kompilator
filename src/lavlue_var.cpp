#include <lvalue_var.hpp>

LvalueVar::LvalueVar(const std::string& name)
    : Lvalue(name, VALTYPE_LVALUE_VAR) {}

LvalueVar::LvalueVar(const LvalueVar& var)
    : Lvalue(var.getName(), var.getType(), var.getAddr()) {}