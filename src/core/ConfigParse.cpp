#include "ConfigParse.hpp"
#include "Parser.hpp"
#include "AstPrinter.hpp"

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
        //for (auto token : tokens)
        //    std::cout << token << std::endl;
        Parser  parser(tokens);

        //std::shared_ptr<Expr>   expr(parser.parse());
        std::shared_ptr<Stmt>   stmt = parser.parse();
        AstPrinter              ap;
        //Interpret   interpret;

        ap.print(*stmt);
        std::cout << "\n";
        //interpret.interpret(expr);
        //for (auto ep : expr)
        //    ap.print(*ep);
        //std::list<Token>::iterator  it;

        //for (it = tokens.begin(); it != tokens.end(); ++it)
        //    std::cout << *it << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string ConfigParse::toString(int n) noexcept {
    std::stringstream   ss;

    ss << std::dec << n;
    return ss.str();
}
