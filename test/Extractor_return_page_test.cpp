//#include "gtest/gtest.h"
//#include "../src/config/Extractor.hpp"

//TEST(ExtractorTest, ReturnPage_Valid) {
//    std::vector<std::string> info = {"404", "/path/to/return/page"};
//    Token token(PARAMETER, "404 /path/to/return/page", 1);
//    Extractor extractor(info, token);
//    std::map<size_t, std::string> expected = {{404, "/path/to/return/page"}};
//    EXPECT_EQ(extractor.return_page(), expected);
//}

//TEST(ExtractorTest, ReturnPage_InvalidSize) {
//    std::vector<std::string> info = {"404"};
//    Token token(PARAMETER, "404", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.return_page(), RunTimeException);
//}

//TEST(ExtractorTest, ReturnPage_InvalidCode) {
//    std::vector<std::string> info = {"invalid", "/path/to/return/page"};
//    Token token(PARAMETER, "invalid /path/to/return/page", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.return_page(), RunTimeException);
//}

//TEST(ExtractorTest, ReturnPage_CodeOutOfRange) {
//    std::vector<std::string> info = {"600", "/path/to/return/page"};
//    Token token(PARAMETER, "600 /path/to/return/page", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.return_page(), RunTimeException);
//}

//TEST(ExtractorTest, ReturnPage_MultipleValid) {
//    std::vector<std::string> info = {"404", "500", "/path/to/return/page"};
//    Token token(PARAMETER, "404 500 /path/to/return/page", 1);
//    Extractor extractor(info, token);
//    std::map<size_t, std::string> expected = {{404, "/path/to/return/page"}, {500, "/path/to/return/page"}};
//    EXPECT_EQ(extractor.return_page(), expected);
//}
