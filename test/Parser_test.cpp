// FILEPATH: /home/essam/CLionProjects/webserv/test/Parser_test.cpp

#include "../src/config/ParseException.hpp"
#include "../src/config/Parser.hpp"
#include "gtest/gtest.h"

TEST(ParserTest, DefaultConstructor) {
    Parser parser("");
    EXPECT_TRUE(parser.isAtEnd()); // Parser should be at end with empty source
}

TEST(ParserTest, ParseEmptySource) {
    Parser parser("");
    EXPECT_THROW(parser.parse(),
                 ParseException); // Parsing invalid source should throw
}

TEST(ParserTest, ParseInvalidSource) {
    Parser parser("invalid");
    EXPECT_THROW(parser.parse(),
                 ParseException); // Parsing invalid source should throw
}

TEST(ParserTest, ParseValidSource) {
    std::string source = "server { listen 80; server_name localhost; }";
    Parser parser(source);
    EXPECT_NO_THROW(parser.parse()); // Parsing valid source should not throw
}

TEST(ParserTest, ParseIncompleteSource) {
    std::string source =
        "server { listen 80; server_name localhost;"; // Missing closing brace
    Parser parser(source);
    EXPECT_THROW(parser.parse(),
                 ParseException); // Parsing incomplete source should throw
}

TEST(ParserTest, ParseExtraTokenSource) {
    std::string source =
        "server { listen 80; server_name localhost; } extra"; // Extra token
                                                              // after server
                                                              // block
    Parser parser(source);
    EXPECT_THROW(
        parser.parse(),
        ParseException); // Parsing source with extra token should throw
}

TEST(ParserTest, ParseMultipleServerBlocks) {
    std::string source = "server { listen 80; server_name localhost; } server "
                         "{ listen 8080; server_name example.com; }";
    Parser parser(source);
    EXPECT_NO_THROW(parser.parse()); // Parsing source with multiple server
                                     // blocks should not throw
}

TEST(ParserTest, ParseServerBlockWithLocation) {
    std::string source = "server { listen 80; server_name localhost; location "
                         "/ { root /var/www; } }";
    Parser parser(source);
    EXPECT_NO_THROW(parser.parse()); // Parsing source with server block
                                     // containing location should not throw
}
