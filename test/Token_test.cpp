#include "../src/config/Token.hpp"
#include "../src/config/TokenType.hpp"
#include "gtest/gtest.h"

TEST(TokenTest, DefaultConstructor) {
    Token token;

    // Check if the default values are correctly set
    EXPECT_EQ(token.type(), END);
    EXPECT_TRUE(token.lexeme().empty());
    EXPECT_EQ(token.line(), 0);
}

TEST(TokenTest, ParameterizedConstructor) {
    TokenType   type = PARAMETER;
    std::string lexeme = "test";
    int         line = 1;

    Token token(type, lexeme, line);

    // Check if the values are correctly set
    EXPECT_EQ(token.type(), type);
    EXPECT_EQ(token.lexeme(), lexeme);
    EXPECT_EQ(token.line(), line);
}

TEST(TokenTest, CopyConstructor) {
    TokenType   type = PARAMETER;
    std::string lexeme = "test";
    int         line = 1;

    Token token1(type, lexeme, line);
    Token token2(token1);

    // Check if the values are correctly copied
    EXPECT_EQ(token2.type(), token1.type());
    EXPECT_EQ(token2.lexeme(), token1.lexeme());
    EXPECT_EQ(token2.line(), token1.line());
}

TEST(TokenTest, AssignmentOperator) {
    TokenType   type = PARAMETER;
    std::string lexeme = "test";
    int         line = 1;

    Token token1(type, lexeme, line);
    Token token2;
    token2 = token1;

    // Check if the values are correctly copied
    EXPECT_EQ(token2.type(), token1.type());
    EXPECT_EQ(token2.lexeme(), token1.lexeme());
    EXPECT_EQ(token2.line(), token1.line());

    // Test self-assignment
    token2 = token2;
    EXPECT_EQ(token2.type(), token1.type());
    EXPECT_EQ(token2.lexeme(), token1.lexeme());
    EXPECT_EQ(token2.line(), token1.line());
}
