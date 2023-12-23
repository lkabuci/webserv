#include "gtest/gtest.h"
#include "../src/config/Parser.hpp"

TEST(ParserTest, ParseMultipleServerContexts) {
    Parser parser("server { listen 8000; } server { listen 8080; }");
    EXPECT_NO_THROW(parser.parse());
}

TEST(ParserTest, ParseInvalidServerContext) {
    Parser parser("server { listen; }");
    EXPECT_THROW(parser.parse(), ParseException);
}

TEST(ParserTest, ParseInvalidLocationContext) {
    Parser parser("server { location /path { autoindex; } }");
    EXPECT_THROW(parser.parse(), ParseException);
}

TEST(ParserTest, ParseMultipleLocationContexts) {
    Parser parser("server { location /path1 { autoindex on; } location /path2 { autoindex off; } }");
    EXPECT_NO_THROW(parser.parse());
}

TEST(ParserTest, ParseInvalidBlock) {
    Parser parser("server { listen 80 }");
    EXPECT_THROW(parser.parse(), ParseException);
}

TEST(ParserTest, ParseInvalidParameter) {
    Parser parser("server { listen; }");
    EXPECT_THROW(parser.parse(), ParseException);
}

TEST(ParserTest, ParseInvalidDirective) {
    Parser parser("server { invalid 80; }");
    EXPECT_THROW(parser.parse(), ParseException);
}

TEST(ParserTest, ParseInvalidToken) {
    Parser parser("invalid { listen 80; }");
    EXPECT_THROW(parser.parse(), ParseException);
}

TEST(ParserTest, ParseEmptyBlock) {
    Parser parser("server { }");
    EXPECT_NO_THROW(parser.parse());
}

TEST(ParserTest, ParseEmptyLocationContext) {
    Parser parser("server { location /path { } }");
    EXPECT_NO_THROW(parser.parse());
}

TEST(ParserTest, ParseEmptyParameter) {
    Parser parser("server { listen ; }");
    EXPECT_THROW(parser.parse(), ParseException);
}

TEST(ParserTest, ParseEmptyServerContext) {
    Parser parser("server { }");
    EXPECT_NO_THROW(parser.parse());
}
TEST(ParserTest, ParseServerContext) {
    Parser parser("server { listen 8000; }");
    EXPECT_NO_THROW(parser.parse());
}

TEST(ParserTest, ParseLocationContext) {
    Parser parser("server { location /path { autoindex on; } }");
    EXPECT_NO_THROW(parser.parse());
}

TEST(ParserTest, ParseServerAndLocationContexts) {
    Parser parser("server { listen 8000; location /path { autoindex on; } }");
    EXPECT_NO_THROW(parser.parse());
}

//TEST(ParserTest, ParseInvalidServerContext) {
//    Parser parser("server { listen; }");
//    EXPECT_THROW(parser.parse(), ParseException);
//}

//TEST(ParserTest, ParseInvalidLocationContext) {
//    Parser parser("server { location /path { autoindex; } }");
//    EXPECT_THROW(parser.parse(), ParseException);
//}

//TEST(ParserTest, ParseInvalidBlock) {
//    Parser parser("server { listen 80 }");
//    EXPECT_THROW(parser.parse(), ParseException);
//}

//TEST(ParserTest, ParseInvalidParameter) {
//    Parser parser("server { listen; }");
//    EXPECT_THROW(parser.parse(), ParseException);
//}

//TEST(ParserTest, ParseInvalidDirective) {
//    Parser parser("server { invalid 80; }");
//    EXPECT_THROW(parser.parse(), ParseException);
//}

//TEST(ParserTest, ParseInvalidToken) {
//    Parser parser("invalid { listen 80; }");
//    EXPECT_THROW(parser.parse(), ParseException);
//}

//TEST(ParserTest, ParseEmptyBlock) {
//    Parser parser("server { }");
//    EXPECT_NO_THROW(parser.parse());
//}

//TEST(ParserTest, ParseEmptyLocationContext) {
//    Parser parser("server { location /path { } }");
//    EXPECT_NO_THROW(parser.parse());
//}

//TEST(ParserTest, ParseEmptyParameter) {
//    Parser parser("server { listen ; }");
//    EXPECT_THROW(parser.parse(), ParseException);
//}
