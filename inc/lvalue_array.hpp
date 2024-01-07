#ifndef LVALUE_ARRAY_HPP
#define LVALUE_ARRAY_HPP

#include <lvalue.hpp>
#include <memory>
#include <value.hpp>

class LvalueArray : public Lvalue {
   private:
    Architecture::addr_t size;
    std::shared_ptr<Value> accessElement;

   public:
    LvalueArray(const std::string& name, Architecture::addr_t size);
    LvalueArray(const LvalueArray& arr);

    Architecture::addr_t getSize() const override { return size; }

    const Value* getAccessElement() const { return accessElement.get(); }
    void setAccessElement(const std::shared_ptr<Value>& access) {
        accessElement = access;
    }
};

#endif