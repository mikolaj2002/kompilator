#ifndef CONDITIONAL_BRANCH_MANAGER
#define CONDITIONAL_BRANCH_MANAGER

#include <conditional_branch.hpp>
#include <stack>

class ConditionalBranchManager {
 private:
  std::stack<ConditionalBranch> stackBranch;

 public:
  void addBranch(const ConditionalBranch& branch);
  ConditionalBranch getBranchFromStack();
};

#endif