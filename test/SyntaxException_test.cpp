#include "../src/config/SyntaxException.hpp"
#include "gtest/gtest.h"

TEST(SyntaxExceptionTest, ConstructorWithChar) {
    SyntaxException exception(1, "Unexpected character", 'a');

    // Check if the error message is correctly formatted
    EXPECT_STREQ(exception.what(), "[line 1] Error: Unexpected charactera.");
}

TEST(SyntaxExceptionTest, ConstructorWithoutChar) {
    SyntaxException exception(2, "Unexpected end of file");

    // Check if the error message is correctly formatted
    EXPECT_STREQ(exception.what(), "[line 2] Error: Unexpected end of file");
}

TEST(SyntaxExceptionTest, What) {
    SyntaxException exception(1, "Unexpected character", 'a');

    // Check if the what function correctly returns the error message
    EXPECT_STREQ(exception.what(), "[line 1] Error: Unexpected charactera.");
}

TEST(SyntaxExceptionTest, ToString) {
    SyntaxException exception(1, "Unexpected character", 'a');

    // Check if the toString function correctly converts an integer to a string
    EXPECT_EQ(exception.toString(123), "123");
}
