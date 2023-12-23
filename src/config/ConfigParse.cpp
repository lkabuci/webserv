#include "ConfigParse.hpp"
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
        Env& env = Env::getInstance();
        env.create(SERVER);
        std::vector<std::string> value = {"8080"};
        Token token(LISTEN, "8080", 1);
        env.put(value, token);
        env.add(SERVER);
        std::vector<ServerConfig> configs = env.get();

        std::cout << "server: " << configs.size() << '\n';
        std::cout << "port: " << configs[0].port_number() << '\n';
        //Env&    env = Env::getInstance();

        //env.create(SERVER);
        //env.create(LOCATION);
        //env.add(LOCATION);
        //std::vector<ServerConfig> configs = env.get();

        //std::cout << "server: " << configs.size() << '\n';
        //std::cout << "location: " << configs[0].getLocations().size() << '\n';

        //Lexer lexer("\nserver");
        //Token token = lexer.scan();

        //std::cout << "type: |" << Lexer::keywordsValues[token.getType()] << "|\n";
        //std::cout << "lexeme: |" << token.getLexeme() << "|\n";
        //std::cout << "line: |" << token.getLine() << "|\n";
        //Parser  parser(source);

        //parser.parse();
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
