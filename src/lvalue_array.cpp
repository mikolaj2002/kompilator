#include <lvalue_array.hpp>

LvalueArray::LvalueArray(const std::string& name, Architecture::addr_t size)
    : Lvalue(name, VALTYPE_LVALUE_ARRAY), size{size} {}

LvalueArray::LvalueArray(const LvalueArray& arr)
    : Lvalue(arr.getName(), arr.getType(), arr.getAddr()),
      size{arr.getSize()} {}