#include <loop_while.hpp>

LoopWhile::LoopWhile(const std::string& startLabel, const std::string& endLabel)
    : Loop(startLabel, endLabel, Loop::LOOP_TYPE_WHILE) {}