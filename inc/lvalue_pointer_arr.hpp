#ifndef LVALUE_POINTER_ARRAY_HPP
#define LVALUE_POINTER_ARRAY_HPP

#include <lvalue_pointer.hpp>
#include <memory>
#include <value.hpp>

class LvaluePointerArray : public LvaluePointer {
   private:
    std::shared_ptr<Value> accessElement;

   public:
    LvaluePointerArray(const std::string& name);
    LvaluePointerArray(const LvaluePointerArray& arr);

    const Value* getAccessElement() const { return accessElement.get(); }
    void setAccessElement(const std::shared_ptr<Value>& access) {
        accessElement = access;
    }
};

#endif