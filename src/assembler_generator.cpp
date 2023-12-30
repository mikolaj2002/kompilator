#include <assembler_generator.hpp>

void AssemblerGenerator::addCode(const std::string& line) {
    code.push_back(line);
}

std::string AssemblerGenerator::getCode() {
    std::string result = "";
    for (auto& line : code) {
        result += line + "\n";
    }
    return result;
}

void AssemblerGenerator::addHalt() { addCode("HALT"); }

void AssemblerGenerator::addWrite() { addCode("WRITE"); }