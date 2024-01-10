#include <procedure.hpp>

Procedure::Procedure(const std::string& name, const std::string& startLabel)
    : name{name}, startLabel{startLabel} {
  if (name == "main_00") {
    type = PROCTYPE_MAIN;
  } else {
    type = PROCTYPE_PROC;
    returnLine = new LvalueVar(name + "return", true);
    varManager.declareVariable(returnLine);
  }
}