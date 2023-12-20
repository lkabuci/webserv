//#include "gtest/gtest.h"
//#include "../include/webserv.h"

//TEST(LexerTest, ScanTokenEndOfFile) {
//    Lexer lexer("");
//    lexer.scanToken();
//    EXPECT_EQ(lexer.scanTokens().size(), 1);
//    EXPECT_EQ(lexer.scanTokens().front().getType(), END);
//}

//TEST(LexerTest, ScanTokenLeftBrace) {
//    Lexer lexer("{");
//    lexer.scanToken();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getType(), LEFT_BRACE);
//}

//TEST(LexerTest, ScanTokenRightBrace) {
//    Lexer lexer("}");
//    lexer.scanToken();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getType(), RIGHT_BRACE);
//}

//TEST(LexerTest, ScanTokenSemicolon) {
//    Lexer lexer(";");
//    lexer.scanToken();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getType(), SEMICOLON);
//}

//TEST(LexerTest, ScanTokenComment) {
//    Lexer lexer("# This is a comment");
//    lexer.scanToken();
//    EXPECT_EQ(lexer.scanTokens().size(), 1);
//}

//TEST(LexerTest, ScanTokenQuotes) {
//    Lexer lexer("\"test\"");
//    lexer.scanToken();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test");
//}

//TEST(LexerTest, ScanTokenDefault) {
//    Lexer lexer("test");
//    lexer.scanToken();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test");
//}
