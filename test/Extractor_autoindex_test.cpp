//#include "gtest/gtest.h"
//#include "../src/config/Extractor.hpp"

//TEST(ExtractorTest, Autoindex_ValidOn) {
//    std::vector<std::string> info = {"on"};
//    Token token(PARAMETER, "on", 1);
//    Extractor extractor(info, token);
//    EXPECT_TRUE(extractor.autoindex());
//}

//TEST(ExtractorTest, Autoindex_ValidOff) {
//    std::vector<std::string> info = {"off"};
//    Token token(PARAMETER, "off", 1);
//    Extractor extractor(info, token);
//    EXPECT_FALSE(extractor.autoindex());
//}

//TEST(ExtractorTest, Autoindex_InvalidSize) {
//    std::vector<std::string> info = {"on", "extra"};
//    Token token(PARAMETER, "on extra", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.autoindex(), RunTimeException);
//}

//TEST(ExtractorTest, Autoindex_InvalidValue) {
//    std::vector<std::string> info = {"invalid"};
//    Token token(PARAMETER, "invalid", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.autoindex(), RunTimeException);
//}
