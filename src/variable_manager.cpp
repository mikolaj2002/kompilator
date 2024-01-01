#include <cstdlib>
#include <iostream>
#include <variable_manager.hpp>

void VariableManager::declareVariable(Lvalue* val) {
    // Alloc memory
    val->setAddr(Architecture::alloc(val->getSize()));

    // Declare variable
    variables[val->getName()] = std::shared_ptr<Lvalue>(val);
}

void VariableManager::undeclareVariable(Lvalue* val) {
    variables.erase(val->getName());
}

std::shared_ptr<Lvalue>& VariableManager::getVariable(const std::string& name) {
    if (!isVariableDeclared(name)) {
        std::cerr << "Critical issue, getting undeclare variable" << std::endl;
        exit(EXIT_FAILURE);
    }

    return variables[name];
}

bool VariableManager::isVariableDeclared(const std::string& name) const {
    return variables.find(name) != variables.end();
}