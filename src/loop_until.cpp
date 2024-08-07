#include <loop_until.hpp>

LoopUntil::LoopUntil(const std::string& startLabel, const std::string& endLabel)
    : Loop(startLabel, endLabel, Loop::LOOP_TYPE_UNTIL) {}