#include "ConfigParse.hpp"

void    f() { system("leaks parse"); }

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [config_file]" << std::endl;
        std::exit(USGERR);
    }
    ConfigParse cp;

    cp.parseFile(argv[1]);
    std::cout << "\n\n";
    std::atexit(f);
    return 0;
}
