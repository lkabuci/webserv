#include "../include/webserv.h"
#include <gtest/gtest.h>

namespace {

TEST(HTTPTest, VersionToString) {
    EXPECT_EQ("HTTP/1.0", HTTP::toString(HTTP::HTTP_1_0));
    EXPECT_EQ("HTTP/1.1", HTTP::toString(HTTP::HTTP_1_1));
    EXPECT_EQ("HTTP/2.0", HTTP::toString(HTTP::HTTP_2_0));
}

TEST(HTTPTest, StringToVersion) {
    EXPECT_EQ(HTTP::HTTP_1_0, HTTP::toVersion("HTTP/1.0"));
    EXPECT_EQ(HTTP::HTTP_1_1, HTTP::toVersion("HTTP/1.1"));
    EXPECT_EQ(HTTP::HTTP_2_0, HTTP::toVersion("HTTP/2.0"));
    EXPECT_THROW(HTTP::toVersion("InvalidVersion"), std::runtime_error);
}

TEST(HTTPTest, MethodToString) {
    EXPECT_EQ("GET", HTTP::toString(HTTP::GET));
    EXPECT_EQ("POST", HTTP::toString(HTTP::POST));
    EXPECT_EQ("PUT", HTTP::toString(HTTP::PUT));
    EXPECT_EQ("DELETE", HTTP::toString(HTTP::DELETE));
}

TEST(HTTPTest, StringToMethod) {
    EXPECT_EQ(HTTP::GET, HTTP::toMethod("GET"));
    EXPECT_EQ(HTTP::POST, HTTP::toMethod("POST"));
    EXPECT_EQ(HTTP::PUT, HTTP::toMethod("PUT"));
    EXPECT_EQ(HTTP::DELETE, HTTP::toMethod("DELETE"));
    EXPECT_THROW(HTTP::toMethod("InvalidMethod"), std::runtime_error);
}
}
