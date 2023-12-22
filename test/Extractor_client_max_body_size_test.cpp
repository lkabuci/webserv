//#include "gtest/gtest.h"
//#include "../src/config/Extractor.hpp"

//TEST(ExtractorTest, ClientMaxBodySize_Valid) {
//    std::vector<std::string> info = {"1024", "m"};
//    Token token(PARAMETER, "1024m", 1);
//    Extractor extractor(info, token);
//    EXPECT_EQ(extractor.client_max_body_size(), 1024);
//}

//TEST(ExtractorTest, ClientMaxBodySize_InvalidSize) {
//    std::vector<std::string> info = {"1024", "m", "extra"};
//    Token token(PARAMETER, "1024m", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.client_max_body_size(), RunTimeException);
//}

//TEST(ExtractorTest, ClientMaxBodySize_InvalidFormat) {
//    std::vector<std::string> info = {"invalid", "m"};
//    Token token(PARAMETER, "invalidm", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.client_max_body_size(), RunTimeException);
//}

//TEST(ExtractorTest, ClientMaxBodySize_Negative) {
//    std::vector<std::string> info = {"-1024", "m"};
//    Token token(PARAMETER, "-1024m", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.client_max_body_size(), RunTimeException);
//}

//TEST(ExtractorTest, ClientMaxBodySize_InvalidUnit) {
//    std::vector<std::string> info = {"1024", "invalid"};
//    Token token(PARAMETER, "1024invalid", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.client_max_body_size(), RunTimeException);
//}
