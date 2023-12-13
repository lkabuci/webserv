#include "ConfigParse.hpp"

void    fatal(const std::string &msg, int exit_status) {
    std::cerr << msg << std::endl;
    std::exit(exit_status);
}

ConfigParse::ConfigParse() {}

void    ConfigParse::parseFile(const char* file) {
    std::ifstream   infile(file);

    if (!infile.is_open()) {
        fatal(std::string("Can't open file: ") + file, 1);
    }
    std::stringstream   buffer;

    buffer << infile.rdbuf();
    _parse(buffer.str());
}

void    ConfigParse::_parse(const std::string& source) {
    Scanner             scanner(source);
    std::list<Token>    tokens;

    try {
        tokens = scanner.scanTokens();

        std::list<Token>::iterator  it;

        for (it = tokens.begin(); it != tokens.end(); ++it)
            std::cout << *it << std::endl;
    } catch (const SyntaxException& se) {
        std::cerr << se.what() << std::endl;
    }
}
