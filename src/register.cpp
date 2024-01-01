#include <iostream>
#include <register.hpp>

Register::Register(const std::string& name) : name{name}, free{true} {}

void Register::lock() {
    if (!free) {
        std::cerr << "Register " << name << " is already locked\n";
        exit(EXIT_FAILURE);
    }

    free = false;
}

void Register::unlock() {
    if (free) {
        std::cerr << "Register " << name << " is already unlocked\n";
        exit(EXIT_FAILURE);
    }

    free = true;
}