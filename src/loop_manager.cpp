#include <loop_manager.hpp>

void LoopManager::addLoopToStack(Loop* loop) { stackLoop.push(loop); }

Loop* LoopManager::getLoopFromStack() {
  Loop* loop = stackLoop.top();
  stackLoop.pop();

  return loop;
}

Loop* LoopManager::getLoopTopStack() { return stackLoop.top(); }