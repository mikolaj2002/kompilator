#include <architecture.hpp>
#include <cstdlib>
#include <iostream>

Architecture::addr_t Architecture::firstFreeAddr = 0;

Register Architecture::registers[] = {
    Register("a"), Register("b"), Register("c"), Register("d"),
    Register("e"), Register("f"), Register("g"), Register("h")};

Architecture::addr_t Architecture::alloc(Architecture::addr_t bytes) {
    addr_t allocAddr = firstFreeAddr;
    firstFreeAddr += bytes;

    return allocAddr;
}

Register& Architecture::getFreeRegister() {
    for (size_t i = 1; i < registersNum; ++i)
        if (registers[i].isFree()) return registers[i];

    std::cerr << "[COMPILER] No free register" << std::endl;
    exit(EXIT_FAILURE);
}

Register& Architecture::getRetValRegister() { return registers[0]; }