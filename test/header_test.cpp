#include "../include/webserv.h"
#include <gtest/gtest.h>

namespace {
TEST(HeaderTest, Serialization) {
    Header header("Content-Type", "application/json");
    EXPECT_EQ("Content-Type: application/json", header.serialize());
}

TEST(HeaderTest, ValidHeaderDeserialization) {
    std::string validHeader = "Accept-Language: en-US";
    Header      deserialized = Header::deserialize(validHeader);

    EXPECT_EQ("Accept-Language", deserialized.getKey());
    EXPECT_EQ("en-US", deserialized.getValue());
}

TEST(HeaderTest, InvalidHeaderDeserialization) {
    std::string invalidHeader = "InvalidHeader";

    EXPECT_THROW(Header::deserialize(invalidHeader), std::runtime_error);
}

TEST(HeaderTest, EmptyHeaderDeserialization) {
    std::string emptyHeader = "";

    EXPECT_THROW(Header::deserialize(emptyHeader), std::runtime_error);
}

TEST(HeaderTest, HeaderWithoutValueDeserialization) {
    std::string headerWithoutValue = "NoValue:";
    Header      deserialized = Header::deserialize(headerWithoutValue);

    EXPECT_EQ("NoValue", deserialized.getKey());
    EXPECT_EQ("", deserialized.getValue());
}

TEST(HeaderTest, HeaderWithSpacesDeserialization) {
    std::string headerWithSpaces = "   KeyWithSpaces  : ValueWithSpaces   ";
    Header      deserialized = Header::deserialize(headerWithSpaces);

    EXPECT_EQ("KeyWithSpaces", deserialized.getKey());
    EXPECT_EQ("ValueWithSpaces", deserialized.getValue());
}

TEST(HeaderTest, SetterGetter) {
    Header header("Authorization", "Bearer token");

    // Test setters and getters
    header.setKey("Content-Type");
    header.setValue("text/plain");

    EXPECT_EQ("Content-Type", header.getKey());
    EXPECT_EQ("text/plain", header.getValue());
}

} // namespace
