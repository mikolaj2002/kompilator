#include <loop.hpp>

Loop::Loop(const std::string& startLabel, const std::string& endLabel,
           looptype_t type)
    : startLabel{startLabel}, endLabel{endLabel}, type{type} {}