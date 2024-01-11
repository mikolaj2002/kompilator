#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <architecture.hpp>
#include <lvalue_var.hpp>
#include <string>
#include <variable_manager.hpp>

class Procedure {
   private:
    std::string name;
    std::string startLabel;
    VariableManager varManager;

   public:
    Procedure(const std::string& name, const std::string& startLabel);
    virtual ~Procedure() = default;
    Procedure(const Procedure& from) = default;
    Procedure& operator=(const Procedure& from) = default;
    Procedure(Procedure&&) = default;
    Procedure& operator=(Procedure&&) = default;

    const std::string& getName() const { return name; }
    const std::string& getStartLabel() const { return startLabel; }
    VariableManager& getVarManager() { return varManager; }
    std::shared_ptr<Lvalue>& getReturnLine() { return varManager.getVariable("0return"); }
    bool isMainProcedure() const { return name == "0"; }
    void setStartLabel(const std::string& startLabel) {
        this->startLabel = startLabel;
    }
};

#endif  // PROCEDURE_HPP