// FILEPATH: /home/essam/CLionProjects/webserv/test/ServerConfig_test.cpp

#include "../src/config/ServerConfig.hpp"
#include "gtest/gtest.h"

TEST(ServerConfigTest, DefaultConstructor) {
    ServerConfig config;

    // Check if the default values are correctly set
    EXPECT_EQ(config.port_number(), 8000);
    EXPECT_EQ(*(config.server_name().begin()), "-");
    EXPECT_EQ(config.client_max_body_size(), 100);
    EXPECT_TRUE(config.index().empty());
    EXPECT_TRUE(config.root().empty());
    EXPECT_TRUE(config.error_page().empty());
    EXPECT_TRUE(config.return_page().empty());
    EXPECT_TRUE(config.allow_methods().empty());
    EXPECT_FALSE(config.autoindex());
    EXPECT_TRUE(config.getLocations().empty());
}

TEST(ServerConfigTest, ParameterizedConstructor) {
    size_t                        port = 8080;
    std::set<std::string>         name = {"name"};
    size_t                        size = 1024;
    std::set<std::string>         indx = {"index.html"};
    std::set<std::string>         root_dir = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods = {"GET"};
    bool                          auto_index = false;

    ServerConfig config(port, name, size, indx, root_dir, error_page,
                        return_page, methods, auto_index);

    // Check if the values are correctly set
    EXPECT_EQ(config.port_number(), port);
    EXPECT_EQ(config.server_name(), name);
    EXPECT_EQ(config.client_max_body_size(), size);
    EXPECT_EQ(config.index(), indx);
    EXPECT_EQ(config.root(), root_dir);
    EXPECT_EQ(config.error_page(), error_page);
    EXPECT_EQ(config.return_page(), return_page);
    EXPECT_EQ(config.allow_methods(), methods);
    EXPECT_EQ(config.autoindex(), auto_index);
    EXPECT_TRUE(config.getLocations().empty());
}

TEST(ServerConfigTest, CopyConstructor) {
    size_t                        port = 8080;
    std::set<std::string>         name = {"name"};
    size_t                        size = 1024;
    std::set<std::string>         indx = {"index.html"};
    std::set<std::string>         root_dir = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods = {"GET"};
    bool                          auto_index = false;

    ServerConfig config1(port, name, size, indx, root_dir, error_page,
                         return_page, methods, auto_index);
    ServerConfig config2(config1);

    // Check if the values are correctly copied
    EXPECT_EQ(config2, config1);
}

TEST(ServerConfigTest, AssignmentOperator) {
    size_t                        port = 8080;
    std::set<std::string>         name = {"name"};
    size_t                        size = 1024;
    std::set<std::string>         indx = {"index.html"};
    std::set<std::string>         root_dir = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods = {"GET"};
    bool                          auto_index = false;

    ServerConfig config1(port, name, size, indx, root_dir, error_page,
                         return_page, methods, auto_index);
    ServerConfig config2;
    config2 = config1;

    // Check if the values are correctly copied
    EXPECT_EQ(config2, config1);

    // Test self-assignment
    config2 = config2;
    EXPECT_EQ(config2, config1);
}

TEST(ServerConfigTest, AddLocation) {
    ServerConfig   config;
    LocationConfig location;

    config.addLocation(location);

    // Check if the location is correctly added
    EXPECT_EQ(config.getLocations().size(), 1);
    EXPECT_EQ(config.getLocations()[0], location);
}
