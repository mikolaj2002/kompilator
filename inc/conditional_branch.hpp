#ifndef CONDITIONAL_BRANCH_HPP
#define CONDITIONAL_BRANCH_HPP

#include <string>

class ConditionalBranch {
   private:
    std::string labelFalse;

   public:
    ConditionalBranch(const std::string& labelFalse);

    const std::string& getLabelFalse() const { return labelFalse; }
};

#endif