//#include "gtest/gtest.h"
//#include "../include/webserv.h"

//TEST(LexerTest, Quotes) {
//    Lexer lexer("\"test\"");
//    lexer.scanTokens();
//    EXPECT_EQ(lexer.scanTokens().size(), 1);
//    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test");
//}

//TEST(LexerTest, QuotesWithNewLine) {
//    Lexer lexer("\"test\n\"");
//    lexer.scanTokens();
//    EXPECT_THROW(lexer.scanTokens(), SyntaxException);
//}

//TEST(LexerTest, QuotesUnterminated) {
//    Lexer lexer("\"test");
//    lexer.scanTokens();
//    EXPECT_THROW(lexer.scanTokens(), SyntaxException);
//}
