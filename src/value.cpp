#include <value.hpp>

Value::Value() : type{VALTYPE_GENERAL} {}

Value::Value(valtype_t type) : type{type} {}