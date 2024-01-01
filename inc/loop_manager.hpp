#ifndef LOOP_MANAGER_HPP
#define LOOP_MANAGER_HPP

#include <loop.hpp>
#include <stack>

class LoopManager {
   private:
    std::stack<Loop*> stackLoop;

   public:
    void addLoopToStack(Loop* loop);
    Loop* getLoopFromStack();
    Loop* getLoopTopStack();
};

#endif