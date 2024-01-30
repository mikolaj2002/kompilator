#include <lvalue.hpp>

Lvalue::Lvalue()
    : Value(VALTYPE_LVALUE),
      name{std::string("LVALUE")},
      init{false},
      addr{0} {}

Lvalue::Lvalue(const std::string& name, Value::valtype_t type)
    : Value(type), name{name}, init{false}, addr{0} {}

Lvalue::Lvalue(const std::string& name, Value::valtype_t type,
               Architecture::addr_t addr)
    : Value(type), name{name}, init{false}, addr{addr} {}