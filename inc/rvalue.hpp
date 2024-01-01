#ifndef RVALUE_HPP
#define RVALUE_HPP

#include <value.hpp>

class Rvalue : public Value {
   private:
    uint64_t value;

   public:
    Rvalue();
    Rvalue(uint64_t value);

    uint64_t getValue() const { return value; }
};

#endif