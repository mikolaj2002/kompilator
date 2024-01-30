#include <lvalue_pointer.hpp>

LvaluePointer::LvaluePointer(const std::string& name, valtype_t type)
    : Lvalue(name, type) {
    this->init = true;
}

LvaluePointer::LvaluePointer(const LvaluePointer& var)
    : Lvalue(var.getName(), var.getType(), var.getAddr()) {
    this->init = true;
}