#include "../include/webserv.hpp"
#include "gtest/gtest.h"
namespace {

TEST(HttpMethods, normal) {
    EXPECT_EQ(HTTP::toMethod("GET"), HTTP::GET);
    EXPECT_EQ(HTTP::toMethod("POST"), HTTP::POST);
    EXPECT_EQ(HTTP::toMethod("DELETE"), HTTP::DELETE);
    EXPECT_EQ(HTTP::toMethod("PUT"), HTTP::PUT);
}

TEST(HttpMethods, abnormal) {
    EXPECT_THROW(HTTP::toMethod("GETS"), std::runtime_error);
    EXPECT_THROW(HTTP::toMethod("POSTS"), std::runtime_error);
    EXPECT_THROW(HTTP::toMethod("DELETES"), std::runtime_error);
    EXPECT_THROW(HTTP::toMethod("PUTS"), std::runtime_error);
}

TEST(HttpVersion, normal) {
    EXPECT_EQ(HTTP::toVersion("HTTP/1.0"), HTTP::HTTP_1_0);
    EXPECT_EQ(HTTP::toVersion("HTTP/1.1"), HTTP::HTTP_1_1);
    EXPECT_EQ(HTTP::toVersion("HTTP/2.0"), HTTP::HTTP_2_0);
}

TEST(HttpVersion, abnormal) {
    EXPECT_THROW(HTTP::toVersion("HTTP/1.2"), std::runtime_error);
    EXPECT_THROW(HTTP::toVersion("HTTP/1.3"), std::runtime_error);
    EXPECT_THROW(HTTP::toVersion("HTTP/2.1"), std::runtime_error);
    EXPECT_THROW(HTTP::toVersion("HTTP/2.2"), std::runtime_error);
}

TEST(StatusLine, normal) {
    StatusLine statusLine(HTTP::GET, "/index.html", HTTP::HTTP_1_1);
    EXPECT_EQ(statusLine.serialize(), "GET /index.html HTTP/1.1");
}

TEST(StatusLine, abnormal) {
    StatusLine statusLine(HTTP::GET, "/index.html", HTTP::HTTP_1_1);
    EXPECT_NE(statusLine.serialize(), "GET /index.html HTTP/1.0");
}

TEST(StatusLine, deserialize) {
    StatusLine statusLine = StatusLine::deserialize("GET /index.html HTTP/1.1");
    EXPECT_EQ(statusLine.serialize(), "GET /index.html HTTP/1.1");
}

TEST(StatusLine, deserialize_abnormal) {
    EXPECT_THROW(StatusLine::deserialize("GET /index.html"),
                 std::runtime_error);
    EXPECT_THROW(StatusLine::deserialize("GET /index.html HTTP/1.2"),
                 std::runtime_error);
    EXPECT_THROW(StatusLine::deserialize("GEET /index.html HTTP/2.0"),
                 std::runtime_error);
}

TEST(Header, normal) {
    Header header("Host", "localhost:8080");
    EXPECT_EQ(header.serialize(), "Host: localhost:8080");
}

TEST(Header, abnormal) {
    Header header("Host", "localhost:8080");
    EXPECT_NE(header.serialize(), "Host: localhost:8081");
    header = Header("Host", "localhost:8080");
    EXPECT_NE(header.serialize(), "Host: localhost:808");
}

} // namespace
