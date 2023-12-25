#include "../src/config/ParseException.hpp"
#include "../src/config/Token.hpp"
#include "../src/config/TokenType.hpp"
#include "gtest/gtest.h"

TEST(ParseExceptionTest, ConstructorEndToken) {
    Token token(END, "", 1);
    ParseException exception(token, "Unexpected end of file");

    // Check if the error message is correctly formatted
    EXPECT_STREQ(exception.what(), "[line 1] at end: Unexpected end of file");
}

TEST(ParseExceptionTest, ConstructorOtherToken) {
    Token token(SERVER, "server", 2);
    ParseException exception(token, "Unexpected token");

    // Check if the error message is correctly formatted
    EXPECT_STREQ(exception.what(), "[line 2] at 'server': Unexpected token");
}

TEST(ParseExceptionTest, What) {
    Token token(SERVER, "server", 2);
    ParseException exception(token, "Unexpected token");

    // Check if the what function correctly returns the error message
    EXPECT_STREQ(exception.what(), "[line 2] at 'server': Unexpected token");
}
