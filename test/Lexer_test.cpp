#include "gtest/gtest.h"
#include "../src/config/Lexer.hpp"
#include "../src/config/Token.hpp"
#include "../src/config/TokenType.hpp"

TEST(LexerTest, Constructor) {
    Lexer lexer("server { listen 80; }");

    // Check if the lexer is correctly initialized
    EXPECT_EQ(lexer._line, 1);
}

TEST(LexerTest, Scan) {
    Lexer lexer("server { listen 80; }");

    // Check if the lexer correctly scans the tokens
    EXPECT_EQ(lexer.scan().type(), SERVER);
    EXPECT_EQ(lexer.scan().type(), LEFT_BRACE);
    EXPECT_EQ(lexer.scan().type(), LISTEN);
    EXPECT_EQ(lexer.scan().type(), PARAMETER);
    EXPECT_EQ(lexer.scan().type(), SEMICOLON);
    EXPECT_EQ(lexer.scan().type(), RIGHT_BRACE);
    EXPECT_EQ(lexer.scan().type(), END);
}

TEST(LexerTest, ScanWithComment) {
    Lexer lexer("server { # This is a comment\n listen 80; }");

    // Check if the lexer correctly scans the tokens and skips the comment
    EXPECT_EQ(lexer.scan().type(), SERVER);
    EXPECT_EQ(lexer.scan().type(), LEFT_BRACE);
    EXPECT_EQ(lexer.scan().type(), LISTEN);
    EXPECT_EQ(lexer.scan().type(), PARAMETER);
    EXPECT_EQ(lexer.scan().type(), SEMICOLON);
    EXPECT_EQ(lexer.scan().type(), RIGHT_BRACE);
    EXPECT_EQ(lexer.scan().type(), END);
}

TEST(LexerTest, ScanWithStrings) {
    Lexer lexer("server { server_name \"example.com\"; }");

    // Check if the lexer correctly scans the tokens and the string
    EXPECT_EQ(lexer.scan().type(), SERVER);
    EXPECT_EQ(lexer.scan().type(), LEFT_BRACE);
    EXPECT_EQ(lexer.scan().type(), SERVER_NAME);
    EXPECT_EQ(lexer.scan().type(), PARAMETER);
    EXPECT_EQ(lexer.scan().type(), SEMICOLON);
    EXPECT_EQ(lexer.scan().type(), RIGHT_BRACE);
    EXPECT_EQ(lexer.scan().type(), END);
}

TEST(LexerTest, ScanWithUnterminatedString) {
    Lexer lexer("server { server_name \"example.com; }");

    // Check if the lexer throws a SyntaxException for the unterminated string
    EXPECT_NO_THROW(lexer.scan());
    EXPECT_NO_THROW(lexer.scan());
    EXPECT_NO_THROW(lexer.scan());
    EXPECT_THROW(lexer.scan(), SyntaxException);
}
