#include <lvalue_pointer_arr.hpp>

LvaluePointerArray::LvaluePointerArray(const std::string& name)
    : LvaluePointer(name, VALTYPE_POINTER_ARRAY) {}

LvaluePointerArray::LvaluePointerArray(const LvaluePointerArray& arr)
    : LvaluePointer(arr) {}
