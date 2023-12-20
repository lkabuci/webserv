// FILEPATH: /home/essam/CLionProjects/webserv/test/LexerTest.cpp
#include "gtest/gtest.h"
#include "../include/webserv.h"

TEST(LexerTest, Constructor) {
    Lexer lexer("test");
    EXPECT_EQ(lexer.scanTokens().size(), 0);
}

TEST(LexerTest, ScanTokens) {
    Lexer lexer("test");
    lexer.scanTokens();
    EXPECT_EQ(lexer.scanTokens().size(), 1);
    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test");
}

TEST(LexerTest, SkipWhiteSpaces) {
    Lexer lexer("   test");
    lexer.scanTokens();
    EXPECT_EQ(lexer.scanTokens().size(), 1);
    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test");
}

TEST(LexerTest, SkipComment) {
    Lexer lexer("# this is a comment\ntest");
    lexer.scanTokens();
    EXPECT_EQ(lexer.scanTokens().size(), 1);
    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test");
}

TEST(LexerTest, StringToken) {
    Lexer lexer("\"test string\"");
    lexer.scanTokens();
    EXPECT_EQ(lexer.scanTokens().size(), 1);
    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test string");
}

TEST(LexerTest, PathToken) {
    Lexer lexer("/test/path");
    lexer.scanTokens();
    EXPECT_EQ(lexer.scanTokens().size(), 1);
    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "/test/path");
}
