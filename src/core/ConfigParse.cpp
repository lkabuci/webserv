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
        Parser  parser(tokens);

        std::shared_ptr<Expr>   stmt = parser.parse();
        AstPrinter  ap;

        ap.print(*stmt);
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string ConfigParse::toString(int n) noexcept {
    std::stringstream   ss;

    ss << std::dec << n;
    return ss.str();
}
