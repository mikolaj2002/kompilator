#ifndef LVALUE_VAR_HPP
#define LVALUE_VAR_HPP

#include <lvalue.hpp>

class LvalueVar : public Lvalue {
   public:
    LvalueVar(const std::string& name);
    LvalueVar(const LvalueVar& var);

    Architecture::addr_t getSize() const override { return 1; }
};

#endif