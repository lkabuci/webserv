#include "../include/webserv.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [config_file]" << std::endl;
        std::exit(USGERR);
    }
    ConfigParse cp;

    cp.parseFile(argv[1]);
    return 0;
}
