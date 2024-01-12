#include <lvalue_pointer.hpp>

LvaluePointer::LvaluePointer(const std::string& name, bool isMutuable,
                             valtype_t type)
    : Lvalue(name, isMutuable, type) {}

LvaluePointer::LvaluePointer(const LvaluePointer& var)
    : Lvalue(var.getName(), var.isMutuable(), var.getType(), var.getAddr()) {}