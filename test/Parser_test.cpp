#include "gtest/gtest.h"
#include "../src/config/Token.hpp"
#include "../src/config/TokenType.hpp"
#include "../src/config/Parser.hpp"

TEST(ParserTest, Parse) {
    Parser parser("server { listen 80; }");
    EXPECT_NO_THROW(parser.parse());
}

TEST(ParserTest, Statement) {
    Parser parser("server { listen 80; }");
    EXPECT_NO_THROW(parser.statement());
}

TEST(ParserTest, ServerContext) {
    Parser parser("server { listen 80; }");
    EXPECT_NO_THROW(parser.serverContext());
}

TEST(ParserTest, Block) {
    Parser parser("{ listen 80; }");
    EXPECT_NO_THROW(parser.block());
}

TEST(ParserTest, LocationContext) {
    Parser parser("/path { autoindex on; }");
    EXPECT_NO_THROW(parser.locationContext());
}

TEST(ParserTest, Parameter) {
    Parser parser("80");
    EXPECT_NO_THROW(parser.parameter());
}

TEST(ParserTest, MatchServerDirective) {
    Parser parser("listen");
    EXPECT_TRUE(parser.matchServerDirective());
}

TEST(ParserTest, MatchLocationDirective) {
    Parser parser("autoindex");
    EXPECT_TRUE(parser.matchLocationDirective());
}

TEST(ParserTest, Consume) {
    Parser parser("server");
    EXPECT_NO_THROW(parser.consume(SERVER_CONTEXT, "Expect a server context."));
}

TEST(ParserTest, Match) {
    Parser parser("server");
    EXPECT_TRUE(parser.match(SERVER_CONTEXT));
}

TEST(ParserTest, Previous) {
    Parser parser("server");
    parser.advance();
    EXPECT_EQ(parser.previous().getLexeme(), "server");
}

TEST(ParserTest, Advance) {
    Parser parser("server { listen 80; }");
    parser.advance();
    EXPECT_EQ(parser.peek().getLexeme(), "{");
}

TEST(ParserTest, Check) {
    Parser parser("server");
    EXPECT_TRUE(parser.check(SERVER_CONTEXT));
}

TEST(ParserTest, Peek) {
    Parser parser("server");
    EXPECT_EQ(parser.peek().getLexeme(), "server");
}

TEST(ParserTest, IsAtEnd) {
    Parser parser("");
    EXPECT_TRUE(parser.isAtEnd());
}
