#ifndef LVALUE_POINTER_HPP
#define LVALUE_POINTER_HPP

#include <lvalue.hpp>

class LvaluePointer : public Lvalue {
   public:
    LvaluePointer(const std::string& name, bool isMutuable, valtype_t type);
    LvaluePointer(const LvaluePointer& var);

    Architecture::addr_t getSize() const override { return 1; }
};

#endif