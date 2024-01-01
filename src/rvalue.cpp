#include <rvalue.hpp>

Rvalue::Rvalue() : Value(VALTYPE_RVALUE) {}

Rvalue::Rvalue(uint64_t value) : Value(VALTYPE_RVALUE), value{value} {}