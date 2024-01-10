#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <architecture.hpp>
#include <assembler_generator.hpp>
#include <lvalue_var.hpp>
#include <string>
#include <variable_manager.hpp>

/*
    TODO: add procedure manager taht returns current procudure and looks by name
   for one
*/

class Procedure {
 public:
  typedef enum { PROCTYPE_MAIN, PROCTYPE_PROC } proctype_t;

 private:
  proctype_t type;
  std::string name;
  std::string startLabel;
  VariableManager varManager;
  LvalueVar* returnLine;

 public:
  Procedure(const std::string& name, const std::string& startLabel);
  virtual ~Procedure() = default;
  Procedure(const Procedure& from) = default;
  Procedure& operator=(const Procedure& from) = default;
  Procedure(Procedure&&) = default;
  Procedure& operator=(Procedure&&) = default;

  const proctype_t getType() const { return type; }
  const std::string& getName() const { return name; }
  const std::string& getStartLabel() const { return startLabel; }
  const VariableManager& getVarManager() const { return varManager; }
  VariableManager& getVarManager() { return varManager; }
  const LvalueVar* getReturnLine() const { return returnLine; }
  LvalueVar* getReturnLine() { return returnLine; }
};

#endif  // PROCEDURE_HPP