#include "../include/webserv.h"
#include <gtest/gtest.h>

namespace {

TEST(StatusLineTest, SerializationTest) {
    StatusLine  statusLine(HTTP::METHOD::GET, "/example",
                           HTTP::VERSION::HTTP_1_1);
    std::string serialized = statusLine.serliaze();

    EXPECT_EQ("GET /example HTTP/1.1", serialized);
}

TEST(StatusLineTest, DeserializationTest) {
    std::string input = "PUT /test HTTP/2.0";
    StatusLine  deserialized = StatusLine::deserialize(input);

    EXPECT_EQ(HTTP::METHOD::PUT, deserialized.getMethod());
    EXPECT_EQ("/test", deserialized.getURI());
    EXPECT_EQ(HTTP::VERSION::HTTP_2_0, deserialized.getVersion());
}

TEST(StatusLineTest, MalformedDeserializationTest) {
    std::string malformedInput = "InvalidInputString";

    EXPECT_THROW(StatusLine::deserialize(malformedInput), std::runtime_error);
}

} // namespace
