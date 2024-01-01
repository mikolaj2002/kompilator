#include <lvalue.hpp>

Lvalue::Lvalue()
    : Value(VALTYPE_LVALUE),
      name{std::string("LVALUE")},
      init{false},
      mutuable{true},
      addr{0} {}

Lvalue::Lvalue(const std::string& name, bool mutuable, Value::valtype_t type)
    : Value(type), name{name}, init{false}, mutuable{mutuable}, addr{0} {}

Lvalue::Lvalue(const std::string& name, bool mutuable, Value::valtype_t type,
               Architecture::addr_t addr)
    : Value(type), name{name}, init{false}, mutuable{mutuable}, addr{addr} {}