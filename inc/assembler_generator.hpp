#ifndef ASSERMBLER_GENERATOR_HPP
#define ASSERMBLER_GENERATOR_HPP

#include <string>
#include <vector>

class AssemblerGenerator {
   private:
    std::vector<std::string> code;
    void addCode(const std::string& line);

   public:
    std::string& getCode();
    void addHalt();
    void addWrite();
};

#endif  // ASSERMBLER_GENERATOR_HPP