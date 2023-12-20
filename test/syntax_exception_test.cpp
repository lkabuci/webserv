#include "gtest/gtest.h"
#include "../include/webserv.h"

TEST(ParseExceptionTest, ConstructorWithEndToken) {
    Token t(END, "", 1);
    ParseException e(t, "Unexpected end of file");
    std::string expectedErrorMsg = "[line 1] at end: Unexpected end of file";
    EXPECT_EQ(e.what(), expectedErrorMsg);
}

TEST(ParseExceptionTest, ConstructorWithNonEndToken) {
    Token t(PARAMETER, "test", 1);
    ParseException e(t, "Unexpected token");
    std::string expectedErrorMsg = "[line 1] at 'test': Unexpected token";
    EXPECT_EQ(e.what(), expectedErrorMsg);
}
