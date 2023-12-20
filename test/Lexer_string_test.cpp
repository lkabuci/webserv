//#include "gtest/gtest.h"
//#include "../include/webserv.h"

//TEST(LexerTest, String) {
//    Lexer lexer("\"test\"");
//    lexer.scanTokens();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "test");
//    EXPECT_EQ(lexer.scanTokens().front().getType(), PARAMETER);
//}

//TEST(LexerTest, StringWithKey) {
//    Lexer lexer("\"server\"");
//    lexer.scanTokens();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "server");
//    EXPECT_EQ(lexer.scanTokens().front().getType(), PARAMETER);
//}

//TEST(LexerTest, StringWithInvalidCharacters) {
//    Lexer lexer("\"te$st\"");
//    lexer.scanTokens();
//    EXPECT_EQ(lexer.scanTokens().size(), 2);
//    EXPECT_EQ(lexer.scanTokens().front().getLexeme(), "te$st");
//    EXPECT_EQ(lexer.scanTokens().front().getType(), PARAMETER);
//}

//TEST(LexerTest, StringUnterminated) {
//    Lexer lexer("\"test");
//    lexer.scanTokens();
//    EXPECT_THROW(lexer.scanTokens(), SyntaxException);
//}
