#include "ConfigParse.hpp"
#include "Parser.hpp"
#include "AstPrinter.hpp"
#include "Token.hpp"
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
    //Lexer             scanner(source);
    std::list<Token>    tokens;
    Expr*   expr = NULL;

    try {
        //Lexer lexer("\"server\"");
        Lexer lexer("   test1   test2   test3   ");
        tokens = lexer.scanTokens();
        std::cout << "size: " << tokens.size() << '\n';
        std::list<Token>::iterator it = tokens.begin();

        std::cout << it->getLexeme() << '\n';
        ++it;
        std::cout << it->getLexeme() << '\n';
        ++it;
        std::cout << it->getLexeme() << '\n';
        ++it;
        std::cout << Token::values[it->getType()] << '\n';
        ++it;
        std::cout << Token::values[it->getType()] << '\n';




        //tokens = scanner.scanTokens();
        Parser  parser(tokens);

        expr = parser.parse();
        if (expr == NULL)
            throw std::runtime_error("no information has found.");
        AstPrinter  ap;

        ap.print(*expr);
        std::cout << '\n';
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
