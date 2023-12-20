//#include "gtest/gtest.h"
//#include "../include/webserv.h"

//TEST(LexerTest, ScanTokensEmptyString) {
//    Lexer lexer("");
//    std::list<Token> tokens = lexer.scanTokens();
//    EXPECT_EQ(tokens.size(), 1);
//    EXPECT_EQ(tokens.front().getType(), END);
//}

//TEST(LexerTest, ScanTokensSingleToken) {
//    Lexer lexer("test");
//    std::list<Token> tokens = lexer.scanTokens();
//    EXPECT_EQ(tokens.size(), 2);
//    EXPECT_EQ(tokens.front().getLexeme(), "test");
//    EXPECT_EQ(tokens.back().getType(), END);
//}

//TEST(LexerTest, ScanTokensMultipleTokens) {
//    Lexer lexer("test1 test2 test3");
//    std::list<Token> tokens = lexer.scanTokens();
//    EXPECT_EQ(tokens.size(), 4);
//    auto it = tokens.begin();
//    EXPECT_EQ(it->getLexeme(), "test1");
//    ++it;
//    EXPECT_EQ(it->getLexeme(), "test2");
//    ++it;
//    EXPECT_EQ(it->getLexeme(), "test3");
//    ++it;
//    EXPECT_EQ(it->getType(), END);
//}

//TEST(LexerTest, ScanTokensWithWhiteSpaces) {
//    Lexer lexer("   test1   test2   test3   ");
//    std::list<Token> tokens = lexer.scanTokens();
//    EXPECT_EQ(tokens.size(), 4);
//    auto it = tokens.begin();
//    EXPECT_EQ(it->getLexeme(), "test1");
//    ++it;
//    EXPECT_EQ(it->getLexeme(), "test2");
//    ++it;
//    EXPECT_EQ(it->getLexeme(), "test3");
//    ++it;
//    EXPECT_EQ(it->getType(), END);
//}
