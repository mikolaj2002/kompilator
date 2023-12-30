#include <iostream>

// extern from parser.y
int compile(const char* in_file, const char* out_file);

int main(int argc, const char* argv[]) {
    if (argc < 3) {
        std ::cout << "Kompilator 2020" << std ::endl
                   << "./kompilator <plik_z_kodem> "
                      "<plik_do_ktorego_zapiszemy_asembler>"
                   << std ::endl;
        return 1;
    }

    return compile(argv[1], argv[2]);
}