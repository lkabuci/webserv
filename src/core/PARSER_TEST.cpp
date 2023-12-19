//#include "Parser.hpp"

//#define RESET   "\033[0m"
//#define RED     "\033[31m"
//#define GREEN   "\033[32m"
//#define YELLOW  "\033[33m"
//#define BLUE    "\033[34m"

//class   PARSER_TEST {
//public:
//    PARSER_TEST(const std::list<Token>& tokens) : _tokens(tokens) {}
//    //static bool TEST_peekNext(const Token& expect,
//    //                        const std::list<Token>& to_test);
//    static bool TEST_previous(const Token& expect,
//                            const std::list<Token>& tokens);

//private:
//    std::list<Token>    _tokens;
//};

//bool    PARSER_TEST::TEST_previous(const Token &expect,
//                                    const std::list<Token> &to_test)
//{
//    Parser  p(to_test);
//    p.advance();
//    Token   prev = p.previous();

//    if (prev.getLexeme() != expect.getLexeme()) {
//        std::cout << RED << "[ FAILURE ]" << RESET;
//        std::cout << " Lexemes are not the same: peekNext() = "
//                << prev.getLexeme() << ", expect = " << expect.getLexeme()
//                << '\n';
//        return false;
//    }
//    if (prev.getLine() != expect.getLine()) {
//        std::cout << RED << "[ FAILURE ]" << RESET;
//        std::cout << " Lines are not the same: peekprev() = " << prev.getLine()
//                << ", expect = " << expect.getLine() << '\n';
//        return false;
//    }
//    if (prev.getType() != expect.getType()) {
//        std::cout << RED << "[ FAILURE ]" << RESET;
//        std::cout << " Types are not the same: peekprev() = " << prev.getType()
//                << ", expect = " << expect.getType() << '\n';
//        return false;
//    }
//    return true;
//}

////bool    PARSER_TEST::TEST_peekNext(const Token& expect,
////                    const std::list<Token>& to_test) {
////    Parser  p(to_test);
////    Token   next = p.peekNext();

////    if (next.getLexeme() != expect.getLexeme()) {
////        std::cout << RED << "[ FAILURE ]" << RESET;
////        std::cout << " Lexemes are not the same: peekNext() = "
////                << next.getLexeme() << ", expect = " << expect.getLexeme() << '\n';
////        return false;
////    }
////    if (next.getLine() != expect.getLine()) {
////        std::cout << RED << "[ FAILURE ]" << RESET;
////        std::cout << " Lines are not the same: peekNext() = " << next.getLine()
////                << ", expect = " << expect.getLine() << '\n';
////        return false;
////    }
////    if (next.getType() != expect.getType()) {
////        std::cout << RED << "[ FAILURE ]" << RESET;
////        std::cout << " Types are not the same: peekNext() = " << next.getType()
////                << ", expect = " << expect.getType() << '\n';
////        return false;
////    }
////    return true;
////}

//int main(int argc, char* argv[]) {
//    std::list<Token>    tokens;

//    tokens.push_back(Token(SERVER_NAME, "server", 1));
//    tokens.push_back(Token(LISTEN, "90", 2));
//    tokens.push_back(Token(ROOT, "./root", 3));
//    tokens.push_back(Token(END, "END", 2));

//    if (PARSER_TEST::TEST_previous(Token(SERVER_NAME, "server", 1), tokens))
//        std::cout << GREEN << "[ PASS ]" << RESET << "\n";
//    return 0;
//}
