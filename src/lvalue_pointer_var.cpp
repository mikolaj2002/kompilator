#include <lvalue_pointer_var.hpp>

LvaluePointerVar::LvaluePointerVar(const std::string& name, bool isMutuable)
    : LvaluePointer(name, isMutuable, VALTYPE_POINTER_VAR) {}

LvaluePointerVar::LvaluePointerVar(const LvaluePointerVar& var)
    : LvaluePointer(var) {}
