#include "ConfigParse.hpp"
#include "Env.hpp"
#include "Parser.hpp"
#include "Servers.hpp"

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
        Parser  parser(source);
        Servers servers;

        parser.parse();
        std::vector<ServerConfig> svconfs = Env::get();
        for (size_t i = 0; i < svconfs.size(); ++i) {
            servers.add(Server(svconfs[i]));
        }
        std::vector<Server> s = servers.get();
        for (size_t i = 0; i < s.size(); ++i) {
            std::cout << "ip: " << s[i].getServerConfig().ip()
                      << ", port: " << s[i].getServerConfig().port()
                      << ", socket: " << s[i].getSocket() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string ConfigParse::toString(int n) {
    std::stringstream ss;

    ss << std::dec << n;
    return ss.str();
}
