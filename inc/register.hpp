#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <string>

class Register {
   private:
    std::string name;
    bool free;

   public:
    Register(const std::string& name);
    const std::string& getName() const { return name; }
    bool isFree() const { return free; }
    void lock();
    void unlock();
};

#endif