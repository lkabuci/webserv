#include "../include/webserv.hpp"
#include <gtest/gtest.h>

TEST(HttpUtilsTest, TrimFunction) {
    EXPECT_EQ("word", HttpUtils::trim("  word  "));
    EXPECT_EQ("", HttpUtils::trim("   "));
    EXPECT_EQ("single", HttpUtils::trim("single"));
    EXPECT_EQ("leading space", HttpUtils::trim(" leading space"));
    EXPECT_EQ("trailing space", HttpUtils::trim("trailing space "));
    EXPECT_EQ("multiple spaces in between",
              HttpUtils::trim(" multiple spaces in between "));
    EXPECT_EQ("tabs and newlines",
              HttpUtils::trim("\t  tabs and newlines  \n"));
    EXPECT_EQ("", HttpUtils::trim(""));
}

TEST(HttpUtilsTest, IsAllWhiteSpaceFunction) {
    EXPECT_TRUE(HttpUtils::isAllWhiteSpace("  \t\n"));
    EXPECT_FALSE(HttpUtils::isAllWhiteSpace("  word  "));
    EXPECT_TRUE(HttpUtils::isAllWhiteSpace(""));
    EXPECT_TRUE(HttpUtils::isAllWhiteSpace("\t\n\r "));
    EXPECT_FALSE(HttpUtils::isAllWhiteSpace("has content"));
}
