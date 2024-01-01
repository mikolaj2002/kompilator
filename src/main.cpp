#include <iostream>
#include <lvalue_array.hpp>
#include <lvalue_var.hpp>
#include <rvalue.hpp>

// extern from parser.y
int compile(const char* inFile, const char* outFile);

int main(int argc, const char* argv[]) {
    if (argc < 3) {
        std ::cout << "./kompilator <plik_z_kodem> "
                      "<plik_do_ktorego_zapiszemy_asembler>"
                   << std ::endl;
        return 1;
    }

    return compile(argv[1], argv[2]);
}