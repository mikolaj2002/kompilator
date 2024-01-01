#ifndef LVALUE_HPP
#define LVALUE_HPP

#include <value.hpp>

class Lvalue : public Value {
   protected:
    std::string name;
    bool init;
    bool mutuable;
    Architecture::addr_t addr;

   public:
    Lvalue();
    Lvalue(const std::string& name, bool mutuable, Value::valtype_t type);
    Lvalue(const std::string& name, bool mutuable, Value::valtype_t type,
           Architecture::addr_t addr);
    virtual ~Lvalue() = default;
    Lvalue(const Lvalue& from) = default;
    Lvalue& operator=(const Lvalue& from) = default;
    Lvalue(Lvalue&&) = default;
    Lvalue& operator=(Lvalue&&) = default;

    virtual const std::string& getName() const { return name; }
    virtual bool isInit() const { return init; }
    virtual bool isMutuable() const { return mutuable; }
    virtual Architecture::addr_t getAddr() const { return addr; }
    virtual Architecture::addr_t getSize() const = 0;

    virtual void setAddr(Architecture::addr_t addr) { this->addr = addr; }
    virtual void setInit() { init = true; }
};

#endif