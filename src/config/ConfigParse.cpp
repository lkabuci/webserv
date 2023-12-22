#include "ConfigParse.hpp"
#include "ConfigInfo.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "AstPrinter.hpp"
#include "ServerConfig.hpp"
#include "Token.hpp"
#include "Visitor.hpp"
#include <iostream>
#include <list>

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
    Token   token;
    Expr*   expr = NULL;

    try {
        Lexer lexer("   \n   server");
        Token token = lexer.scan();


        std::cout << "type: |" << Lexer::keywordsValues[token.getType()] << "|\n";
        std::cout << "lexeme: |" << token.getLexeme() << "|\n";
        std::cout << "line: |" << token.getLine() << "|\n";
        //Parser  parser(tokens);

        //expr = parser.parse();
        //if (expr == NULL)
        //    throw std::runtime_error("no information has found.");
        //AstPrinter      ap;
        //ServerConfig    svconf;

        //ap.print(*expr, svconf);
        //std::cout << '\n';
        delete expr;
    } catch (const std::exception& e) {
        delete expr;
        std::cerr << e.what() << std::endl;
    }
}

std::string ConfigParse::toString(int n) {
    std::stringstream   ss;

    ss << std::dec << n;
    return ss.str();
}
