//#include "gtest/gtest.h"
//#include "../src/config/Extractor.hpp"

//TEST(ExtractorTest, PortNumber_Valid) {
//    std::vector<std::string> info = {"2000"};
//    Token token(PARAMETER, "2000", 1);
//    Extractor extractor(info, token);
//    EXPECT_EQ(extractor.port_number(), 2000);
//}

//TEST(ExtractorTest, PortNumber_InvalidSize) {
//    std::vector<std::string> info = {"2000", "extra"};
//    Token token(PARAMETER, "2000 extra", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.port_number(), RunTimeException);
//}

//TEST(ExtractorTest, PortNumber_InvalidValue) {
//    std::vector<std::string> info = {"invalid"};
//    Token token(PARAMETER, "invalid", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.port_number(), RunTimeException);
//}

//TEST(ExtractorTest, PortNumber_OutOfRange) {
//    std::vector<std::string> info = {"1000"};
//    Token token(PARAMETER, "1000", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.port_number(), RunTimeException);
//}

//TEST(ExtractorTest, ServerName_Valid) {
//    std::vector<std::string> info = {"server1", "server2"};
//    Token token(PARAMETER, "server1 server2", 1);
//    Extractor extractor(info, token);
//    std::set<std::string> expected = {"server1", "server2"};
//    EXPECT_EQ(extractor.server_name(), expected);
//}

//TEST(ExtractorTest, ServerName_Empty) {
//    std::vector<std::string> info = {};
//    Token token(PARAMETER, "", 1);
//    Extractor extractor(info, token);
//    EXPECT_THROW(extractor.server_name(), RunTimeException);
//}

//// Add similar tests for the other methods in the Extractor class...
