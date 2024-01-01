#ifndef LOOP_WHILE_HPP
#define LOOP_WHILE_HPP

#include <loop.hpp>

class LoopWhile : public Loop {
   public:
    LoopWhile(const std::string& startLabel, const std::string& endLabel);
};

#endif