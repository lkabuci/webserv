#include "gtest/gtest.h"
#include "../src/config/Lexer.hpp"
#include "../src/config/Token.hpp"
#include "../src/config/TokenType.hpp"

TEST(LexerTest, ScanToken) {
    Lexer lexer("server { listen 80; }");
    Token token = lexer.scan();

    EXPECT_EQ(token.getType(), SERVER_CONTEXT);
    EXPECT_EQ(token.getLexeme(), "server");
    EXPECT_EQ(token.getLine(), 1);

    token = lexer.scan();
    EXPECT_EQ(token.getType(), LEFT_BRACE);
    EXPECT_EQ(token.getLexeme(), "{");
    EXPECT_EQ(token.getLine(), 1);

    token = lexer.scan();
    EXPECT_EQ(token.getType(), LISTEN);
    EXPECT_EQ(token.getLexeme(), "listen");
    EXPECT_EQ(token.getLine(), 1);

    token = lexer.scan();
    EXPECT_EQ(token.getType(), PARAMETER);
    EXPECT_EQ(token.getLexeme(), "80");
    EXPECT_EQ(token.getLine(), 1);

    token = lexer.scan();
    EXPECT_EQ(token.getType(), SEMICOLON);
    EXPECT_EQ(token.getLexeme(), ";");
    EXPECT_EQ(token.getLine(), 1);

    token = lexer.scan();
    EXPECT_EQ(token.getType(), RIGHT_BRACE);
    EXPECT_EQ(token.getLexeme(), "}");
    EXPECT_EQ(token.getLine(), 1);

    token = lexer.scan();
    EXPECT_EQ(token.getType(), END);
    EXPECT_EQ(token.getLexeme(), "");
    EXPECT_EQ(token.getLine(), 1);
}

TEST(LexerTest, ScanString) {
    Lexer lexer("\"Hello, World!\"");
    Token token = lexer.scan();

    EXPECT_EQ(token.getType(), PARAMETER);
    EXPECT_EQ(token.getLexeme(), "Hello, World!");
    EXPECT_EQ(token.getLine(), 1);
}

TEST(LexerTest, SkipComment) {
    Lexer lexer("# This is a comment\nserver");
    Token token = lexer.scan();

    EXPECT_EQ(token.getType(), SERVER_CONTEXT);
    EXPECT_EQ(token.getLexeme(), "server");
    EXPECT_EQ(token.getLine(), 2);
}

TEST(LexerTest, SkipWhiteSpaces) {
    Lexer lexer("   \n   server");
    Token token = lexer.scan();

    EXPECT_EQ(token.getType(), SERVER_CONTEXT);
    EXPECT_EQ(token.getLexeme(), "server");
    EXPECT_EQ(token.getLine(), 2);
}

TEST(LexerTest, IsParameterChar) {
    Lexer lexer("server");
    bool isParameterChar = lexer.isParameterChar('s');

    EXPECT_TRUE(isParameterChar);
}

TEST(LexerTest, Advance) {
    Lexer lexer("server");
    char c = lexer.advance();

    EXPECT_EQ(c, 's');
}

TEST(LexerTest, Peek) {
    Lexer lexer("server");
    char c = lexer.peek();

    EXPECT_EQ(c, 's');
}
