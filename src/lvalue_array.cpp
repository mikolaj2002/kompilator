#include <lvalue_array.hpp>

LvalueArray::LvalueArray(const std::string& name, Architecture::addr_t size)
    : Lvalue(name, true, VALTYPE_LVALUE_ARRAY), size{size} {}

LvalueArray::LvalueArray(const LvalueArray& arr)
    : Lvalue(arr.getName(), arr.isMutuable(), arr.getType(), arr.getAddr()),
      size{arr.getSize()} {}