#include <lvalue_pointer_var.hpp>

LvaluePointerVar::LvaluePointerVar(const std::string& name)
    : LvaluePointer(name, VALTYPE_POINTER_VAR) {}

LvaluePointerVar::LvaluePointerVar(const LvaluePointerVar& var)
    : LvaluePointer(var) {}
