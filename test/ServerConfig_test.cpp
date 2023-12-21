//#include "gtest/gtest.h"
//#include "../src/core/ServerConfig.hpp"
//#include "../src/core/LocationConfig.hpp"

//TEST(ServerConfigTest, DefaultConstructor) {
//    ServerConfig config;
//    EXPECT_EQ(config.getPort(), 5050);
//    EXPECT_EQ(config.getHost(), "_");
//    EXPECT_EQ(config.getClientMaxBodySize(), 1);
//    EXPECT_TRUE(config.getErrorPage().empty());
//    EXPECT_EQ(config.getRootDir(), ".");
//    EXPECT_FALSE(config.getAutoIndex());
//    EXPECT_EQ(config.getIndexFile().size(), 1);
//    EXPECT_EQ(config.getIndexFile()[0], "index.html");
//    EXPECT_TRUE(config.getLocations().empty());
//}

//TEST(ServerConfigTest, ParameterizedConstructor) {
//    std::vector<std::string> errorPage = {"error.html"};
//    std::vector<std::string> indexFile = {"index1.html", "index2.html"};
//    std::vector<LocationConfig> locations;
//    locations.push_back(LocationConfig(8080, "localhost", 2, errorPage, indexFile, "/root", true, {"301", "http://www.google.com"}));
//    ServerConfig config(locations, 8080, "localhost", 2, errorPage, indexFile, "/root", true);
//    EXPECT_EQ(config.getPort(), 8080);
//    EXPECT_EQ(config.getHost(), "localhost");
//    EXPECT_EQ(config.getClientMaxBodySize(), 2);
//    EXPECT_EQ(config.getErrorPage(), errorPage);
//    EXPECT_EQ(config.getIndexFile(), indexFile);
//    EXPECT_EQ(config.getRootDir(), "/root");
//    EXPECT_TRUE(config.getAutoIndex());
//    EXPECT_EQ(config.getLocations().size(), 1);
//}

//TEST(ServerConfigTest, CopyConstructor) {
//    std::vector<std::string> errorPage = {"error.html"};
//    std::vector<std::string> indexFile = {"index1.html", "index2.html"};
//    std::vector<LocationConfig> locations;
//    locations.push_back(LocationConfig(8080, "localhost", 2, errorPage, indexFile, "/root", true, {"301", "http://www.google.com"}));
//    ServerConfig config1(locations, 8080, "localhost", 2, errorPage, indexFile, "/root", true);
//    ServerConfig config2(config1);
//    EXPECT_EQ(config2.getPort(), 8080);
//    EXPECT_EQ(config2.getHost(), "localhost");
//    EXPECT_EQ(config2.getClientMaxBodySize(), 2);
//    EXPECT_EQ(config2.getErrorPage(), errorPage);
//    EXPECT_EQ(config2.getIndexFile(), indexFile);
//    EXPECT_EQ(config2.getRootDir(), "/root");
//    EXPECT_TRUE(config2.getAutoIndex());
//    EXPECT_EQ(config2.getLocations().size(), 1);
//}

//TEST(ServerConfigTest, AssignmentOperator) {
//    std::vector<std::string> errorPage = {"error.html"};
//    std::vector<std::string> indexFile = {"index1.html", "index2.html"};
//    std::vector<LocationConfig> locations;
//    locations.push_back(LocationConfig(8080, "localhost", 2, errorPage, indexFile, "/root", true, {"301", "http://www.google.com"}));
//    ServerConfig config1(locations, 8080, "localhost", 2, errorPage, indexFile, "/root", true);
//    ServerConfig config2;
//    config2 = config1;
//    EXPECT_EQ(config2.getPort(), 8080);
//    EXPECT_EQ(config2.getHost(), "localhost");
//    EXPECT_EQ(config2.getClientMaxBodySize(), 2);
//    EXPECT_EQ(config2.getErrorPage(), errorPage);
//    EXPECT_EQ(config2.getIndexFile(), indexFile);
//    EXPECT_EQ(config2.getRootDir(), "/root");
//    EXPECT_TRUE(config2.getAutoIndex());
//    EXPECT_EQ(config2.getLocations().size(), 1);
//}
