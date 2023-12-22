//#include "gtest/gtest.h"
//#include "../src/config/Extractor.hpp"

//TEST(ExtractorTest, ErrorPage_Valid) {
//    std::vector<std::string> info = {"404", "/path/to/error/page"};
//    Token token(PARAMETER, "404 /path/to/error/page", 1);
//    Extractor extractor(info, token);
//    std::map<size_t, std::string> expected = {{404, "/path/to/error/page"}};
//    EXPECT_EQ(extractor.error_page(), expected);
//}

//TEST(ExtractorTest, ErrorPage_InvalidSize) {
//    std::vector<std::string> info = {"404"};
//    Token token(PARAMETER, "404", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.error_page(), RunTimeException);
//}

//TEST(ExtractorTest, ErrorPage_InvalidCode) {
//    std::vector<std::string> info = {"invalid", "/path/to/error/page"};
//    Token token(PARAMETER, "invalid /path/to/error/page", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.error_page(), RunTimeException);
//}

//TEST(ExtractorTest, ErrorPage_CodeOutOfRange) {
//    std::vector<std::string> info = {"600", "/path/to/error/page"};
//    Token token(PARAMETER, "600 /path/to/error/page", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.error_page(), RunTimeException);
//}

//TEST(ExtractorTest, ErrorPage_MultipleValid) {
//    std::vector<std::string> info = {"404", "500", "501", "/path/to/other/page"};
//    Token token(PARAMETER, "404 /path/to/error/page 500 /path/to/other/page", 1);
//    Extractor extractor(info, token);
//    std::map<size_t, std::string> expected = {{404, "/path/to/error/page"},
//                                                {500, "/path/to/other/page"},
//                                                {501, "/path/to/other/page"}};
//    EXPECT_EQ(extractor.error_page(), expected);
//}
