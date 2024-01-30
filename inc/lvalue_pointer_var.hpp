#ifndef LVALUE_POINTER_VAR_HPP
#define LVALUE_POINTER_VAR_HPP

#include <lvalue_pointer.hpp>

class LvaluePointerVar : public LvaluePointer {
   public:
    LvaluePointerVar(const std::string& name);
    LvaluePointerVar(const LvaluePointerVar& var);

    Architecture::addr_t getSize() const override { return 1; }
};

#endif