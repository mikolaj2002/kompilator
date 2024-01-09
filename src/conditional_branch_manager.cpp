#include <conditional_branch_manager.hpp>

void ConditionalBranchManager::addBranch(const ConditionalBranch& branch) {
  stackBranch.push(branch);
}

ConditionalBranch ConditionalBranchManager::getBranchFromStack() {
  ConditionalBranch branch = stackBranch.top();
  stackBranch.pop();

  return branch;
}