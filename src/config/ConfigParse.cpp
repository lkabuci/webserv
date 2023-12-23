#include "ConfigParse.hpp"
#include "Parser.hpp"
#include "Env.hpp"
#include <iostream>
#include <string>

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
    //Lexer             lexer(source);
    //std::list<Token>    tokens;
    //Token   token;
    //Expr*   expr = NULL;

    try {
        Parser  parser(source);

        parser.parse();
        std::vector<ServerConfig>   svconfs = Env::get();
        for (size_t i = 0; i < svconfs.size(); ++i) {
            std::cout << "port: " << svconfs[i].port_number();
        }
        //if (expr == NULL)
        //    throw std::runtime_error("no information has found.");
        //AstPrinter      ap;
        //ServerConfig    svconf;

        //ap.print(*expr, svconf);
        //std::cout << '\n';
        //delete expr;
    } catch (const std::exception& e) {
        //delete expr;
        std::cerr << e.what() << std::endl;
    }
}

std::string ConfigParse::toString(int n) {
    std::stringstream   ss;

    ss << std::dec << n;
    return ss.str();
}
