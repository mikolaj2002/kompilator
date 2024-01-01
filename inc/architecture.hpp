#ifndef ARCHITECTURE_HPP
#define ARCHITECTURE_HPP

#include <cstdint>
#include <register.hpp>

class Architecture {
   public:
    typedef uint64_t addr_t;
    static constexpr size_t registersNum = 8;

   private:
    static addr_t firstFreeAddr;
    static Register registers[registersNum];

   public:
    static addr_t alloc(addr_t bytes);
    static Register& getFreeRegister();
    static const Register& getRetValRegister();
};

#endif  // ARCHITECTURE_HPP