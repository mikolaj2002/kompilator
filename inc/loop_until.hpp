#ifndef LOOP_UNTIL_HPP
#define LOOP_UNTIL_HPP

#include <loop.hpp>

class LoopUntil : public Loop {
   public:
    LoopUntil(const std::string& startLabel, const std::string& endLabel);
};

#endif