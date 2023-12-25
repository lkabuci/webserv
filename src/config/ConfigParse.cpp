#include "ConfigParse.hpp"
#include "Env.hpp"
#include "Parser.hpp"

void fatal(const std::string& msg, int exit_status) {
    std::cerr << msg << std::endl;
    std::exit(exit_status);
}

ConfigParse::ConfigParse() {}

void ConfigParse::parseFile(const char* file) {
    std::ifstream infile(file);

    if (!infile.is_open()) {
        fatal(std::string("Can't open file: ") + file, 1);
    }
    std::stringstream buffer;

    buffer << infile.rdbuf();
    _parse(buffer.str());
}

void ConfigParse::_parse(const std::string& source) {
    try {
        // Parser parser(source);

        // parser.parse();
        // std::vector<ServerConfig>   svconfs = Env::get();
        // std::cout << "size: " << svconfs.size() << '\n';
        // for (size_t i = 0; i < svconfs.size(); ++i) {
        //     std::cout << "------------ SERVER " << i + 1 << "\n";
        //     svconfs[i].display();
        // }
        // Env& env = Env::getInstance();

        // env.create(SERVER);
        // env.create(LOCATION);
        // env.add(LOCATION);
        // env.add(SERVER);

        // std::cout << "size: " << env.get().size() << '\n';
        Env& env = Env::getInstance();

        env.create(SERVER);
        env.add(SERVER);

        std::cout << "Size: " << env.get().size() << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string ConfigParse::toString(int n) {
    std::stringstream ss;

    ss << std::dec << n;
    return ss.str();
}
