#include "../src/config/Extractor.hpp"
#include "gtest/gtest.h"

TEST(ExtractorTest, PortNumber) {
    std::vector<std::string> info = {"8080"};
    Token                    token;
    Extractor                extractor(info, token);

    EXPECT_EQ(extractor.port_number(), 8080);
}

TEST(ExtractorTest, ServerName) {
    std::vector<std::string> info = {"example.com"};
    Token                    token;
    Extractor                extractor(info, token);

    std::set<std::string> expected = {"example.com"};
    EXPECT_EQ(extractor.server_name(), expected);
}

TEST(ExtractorTest, ClientMaxBodySize) {
    std::vector<std::string> info = {"2048m"};
    Token                    token;
    Extractor                extractor(info, token);

    EXPECT_EQ(extractor.client_max_body_size(), 2048);
}

TEST(ExtractorTest, Index) {
    std::vector<std::string> info = {"index.html"};
    Token                    token;
    Extractor                extractor(info, token);

    std::set<std::string> expected = {"index.html"};
    EXPECT_EQ(extractor.index(), expected);
}

TEST(ExtractorTest, Root) {
    std::vector<std::string> info = {"/var/www"};
    Token                    token;
    Extractor                extractor(info, token);

    std::set<std::string> expected = {"/var/www"};
    EXPECT_EQ(extractor.root(), expected);
}

TEST(ExtractorTest, ErrorPage) {
    std::vector<std::string> info = {"404", "notfound.html"};
    Token                    token;
    Extractor                extractor(info, token);

    std::map<size_t, std::string> expected = {{404, "notfound.html"}};
    EXPECT_EQ(extractor.error_page(), expected);
}

TEST(ExtractorTest, ReturnPage) {
    std::vector<std::string> info = {"301", "moved.html"};
    Token                    token;
    Extractor                extractor(info, token);

    std::map<size_t, std::string> expected = {{301, "moved.html"}};
    EXPECT_EQ(extractor.return_page(), expected);
}

TEST(ExtractorTest, AllowMethods) {
    std::vector<std::string> info = {"GET", "POST"};
    Token                    token;
    Extractor                extractor(info, token);

    std::set<std::string> expected = {"GET", "POST"};
    EXPECT_EQ(extractor.allow_methods(), expected);
}

TEST(ExtractorTest, Autoindex) {
    std::vector<std::string> info = {"on"};
    Token                    token;
    Extractor                extractor(info, token);

    EXPECT_TRUE(extractor.autoindex());
}
