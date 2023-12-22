//#include "gtest/gtest.h"
//#include "../src/config/Extractor.hpp"

//TEST(ExtractorTest, ServerName_Valid) {
//    std::vector<std::string> info = {"www.example.com", "example.com"};
//    Token token(PARAMETER, "www.example.com", 1);
//    Extractor extractor(info, token);
//    std::set<std::string> expected = {"www.example.com", "example.com"};
//    EXPECT_EQ(extractor.server_name(), expected);
//}

//TEST(ExtractorTest, ServerName_Single) {
//    std::vector<std::string> info = {"www.example.com"};
//    Token token(PARAMETER, "www.example.com", 1);
//    Extractor extractor(info, token);
//    std::set<std::string> expected = {"www.example.com"};
//    EXPECT_EQ(extractor.server_name(), expected);
//}

//TEST(ExtractorTest, ServerName_Empty) {
//    std::vector<std::string> info = {};
//    Token token(PARAMETER, "", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.server_name(), RunTimeException);
//}
