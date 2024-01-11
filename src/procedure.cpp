#include <procedure.hpp>

Procedure::Procedure(const std::string& name, const std::string& startLabel)
    : name{name}, startLabel{startLabel} {
    if (name != "0") {
        varManager.declareVariable(new LvalueVar("0return", true));
    }
}