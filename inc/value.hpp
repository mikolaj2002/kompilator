#ifndef VALUE_HPP
#define VALUE_HPP

#include <architecture.hpp>
#include <cstdint>
#include <string>

class Value {
   public:
    typedef enum {
        VALTYPE_GENERAL,
        VALTYPE_RVALUE,
        VALTYPE_LVALUE,
        VALTYPE_LVALUE_VAR,
        VALTYPE_LVALUE_ARRAY
    } valtype_t;

   protected:
    valtype_t type;

   public:
    Value();
    Value(valtype_t type);
    virtual ~Value() = default;
    Value(const Value& from) = default;
    Value& operator=(const Value& from) = default;
    Value(Value&&) = default;
    Value& operator=(Value&&) = default;

    virtual valtype_t getType() const { return type; }
};

#endif