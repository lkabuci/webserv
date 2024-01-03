#include "ConfigParse.hpp"
#include "../stream/Servers.hpp"
#include "Env.hpp"
#include "Parser.hpp"

void fatal(const std::string& msg, int exit_status) {
    std::cerr << msg << std::endl;
    std::exit(exit_status);
}

ConfigParse::ConfigParse() : _servers() {
}

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
        Parser  parser(source);
        parser.parse();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    _setServers();
}

Servers& ConfigParse::getServers() {
    return _servers;
}

void ConfigParse::_setServers() {
    std::vector<ServerConfig> svconfs = Env::get();

    for (size_t i = 0; i < svconfs.size(); ++i) {
       _servers.add(new Server(svconfs[i]));
    }
}

std::string ConfigParse::toString(int n) {
    std::stringstream ss;

    ss << std::dec << n;
    return ss.str();
}
