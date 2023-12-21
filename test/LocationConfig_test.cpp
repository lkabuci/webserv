//#include "gtest/gtest.h"
//#include "../src/core/LocationConfig.hpp"

//TEST(LocationConfigTest, DefaultConstructor) {
//    LocationConfig config;
//    EXPECT_EQ(config.getPort(), 5050);
//    EXPECT_EQ(config.getHost(), "_");
//    EXPECT_EQ(config.getClientMaxBodySize(), 1);
//    EXPECT_TRUE(config.getErrorPage().empty());
//    EXPECT_EQ(config.getRootDir(), ".");
//    EXPECT_FALSE(config.getAutoIndex());
//    EXPECT_EQ(config.getIndexFile().size(), 1);
//    EXPECT_EQ(config.getIndexFile()[0], "index.html");
//    EXPECT_TRUE(config.getReturnDirective().empty());
//}

//TEST(LocationConfigTest, ParameterizedConstructor) {
//    std::vector<std::string> errorPage = {"error.html"};
//    std::vector<std::string> indexFile = {"index1.html", "index2.html"};
//    std::vector<std::string> returnDirective = {"301", "http://www.google.com"};
//    LocationConfig config(8080, "localhost", 2, errorPage, indexFile, "/root", true, returnDirective);
//    EXPECT_EQ(config.getPort(), 8080);
//    EXPECT_EQ(config.getHost(), "localhost");
//    EXPECT_EQ(config.getClientMaxBodySize(), 2);
//    EXPECT_EQ(config.getErrorPage(), errorPage);
//    EXPECT_EQ(config.getIndexFile(), indexFile);
//    EXPECT_EQ(config.getRootDir(), "/root");
//    EXPECT_TRUE(config.getAutoIndex());
//    EXPECT_EQ(config.getReturnDirective(), returnDirective);
//}

//TEST(LocationConfigTest, CopyConstructor) {
//    std::vector<std::string> errorPage = {"error.html"};
//    std::vector<std::string> indexFile = {"index1.html", "index2.html"};
//    std::vector<std::string> returnDirective = {"301", "http://www.google.com"};
//    LocationConfig config1(8080, "localhost", 2, errorPage, indexFile, "/root", true, returnDirective);
//    LocationConfig config2(config1);
//    EXPECT_EQ(config2.getPort(), 8080);
//    EXPECT_EQ(config2.getHost(), "localhost");
//    EXPECT_EQ(config2.getClientMaxBodySize(), 2);
//    EXPECT_EQ(config2.getErrorPage(), errorPage);
//    EXPECT_EQ(config2.getIndexFile(), indexFile);
//    EXPECT_EQ(config2.getRootDir(), "/root");
//    EXPECT_TRUE(config2.getAutoIndex());
//    EXPECT_EQ(config2.getReturnDirective(), returnDirective);
//}

//TEST(LocationConfigTest, AssignmentOperator) {
//    std::vector<std::string> errorPage = {"error.html"};
//    std::vector<std::string> indexFile = {"index1.html", "index2.html"};
//    std::vector<std::string> returnDirective = {"301", "http://www.google.com"};
//    LocationConfig config1(8080, "localhost", 2, errorPage, indexFile, "/root", true, returnDirective);
//    LocationConfig config2;
//    config2 = config1;
//    EXPECT_EQ(config2.getPort(), 8080);
//    EXPECT_EQ(config2.getHost(), "localhost");
//    EXPECT_EQ(config2.getClientMaxBodySize(), 2);
//    EXPECT_EQ(config2.getErrorPage(), errorPage);
//    EXPECT_EQ(config2.getIndexFile(), indexFile);
//    EXPECT_EQ(config2.getRootDir(), "/root");
//    EXPECT_TRUE(config2.getAutoIndex());
//    EXPECT_EQ(config2.getReturnDirective(), returnDirective);
//}
