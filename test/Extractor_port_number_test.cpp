//#include "gtest/gtest.h"
//#include "../src/config/Extractor.hpp"

//TEST(ExtractorTest, Constructor) {
//    std::vector<std::string> info = {"8080"};
//    Token token(PARAMETER, "8080", 1);
//    Extractor extractor(info, token);
//    EXPECT_NO_THROW(extractor.port_number());
//}

//TEST(ExtractorTest, PortNumber_Valid) {
//    std::vector<std::string> info = {"8080"};
//    Token token(PARAMETER, "8080", 1);
//    Extractor extractor(info, token);
//    EXPECT_EQ(extractor.port_number(), 8080);
//}

//TEST(ExtractorTest, PortNumber_InvalidSize) {
//    std::vector<std::string> info = {"8080", "8081"};
//    Token token(PARAMETER, "8080", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.port_number(), RunTimeException);
//}

//TEST(ExtractorTest, PortNumber_InvalidFormat) {
//    std::vector<std::string> info = {"invalid"};
//    Token token(PARAMETER, "invalid", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.port_number(), RunTimeException);
//}

//TEST(ExtractorTest, PortNumber_OutOfRange) {
//    std::vector<std::string> info = {"99999"};
//    Token token(PARAMETER, "99999", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.port_number(), RunTimeException);
//}
