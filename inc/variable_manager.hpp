#ifndef VARIABLE_MANAGER_HPP
#define VARIABLE_MANAGER_HPP

#include <lvalue.hpp>
#include <map>
#include <memory>
#include <string>

class VariableManager {
   private:
    std::map<std::string, std::shared_ptr<Lvalue>> variables;

   public:
    void declareVariable(Lvalue* val);
    void undeclareVariable(Lvalue* val);
    bool isVariableDeclared(const std::string& name) const;
    std::shared_ptr<Lvalue>& getVariable(const std::string& name);
};

#endif