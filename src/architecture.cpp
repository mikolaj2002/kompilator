#include <architecture.hpp>
#include <cstdlib>
#include <iostream>

Architecture::addr_t Architecture::firstFreeAddr = 1;

Register Architecture::registers[] = {
    Register("a"), Register("b"), Register("c"), Register("d"),
    Register("e"), Register("f"), Register("g"), Register("h")};

Architecture::addr_t Architecture::alloc(Architecture::addr_t bytes) {
  addr_t allocAddr = firstFreeAddr;
  firstFreeAddr += bytes;

  return allocAddr;
}

Register& Architecture::getFreeRegister() {
  // Register a is like eax in x86 is used to return value so it is a special
  // register cannot return Register a as normal free register
  for (size_t i = 1; i < registersNum; ++i)
    if (registers[i].isFree()) return registers[i];

  // if we reached here we have critical issue
  std::cerr << "Critical issue, no free register" << std::endl;
  exit(EXIT_FAILURE);
}

Register& Architecture::getRetValRegister() { return registers[0]; }