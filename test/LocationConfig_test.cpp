// FILEPATH: /home/essam/CLionProjects/webserv/test/LocationConfig_test.cpp

#include "../src/config/LocationConfig.hpp"
#include "gtest/gtest.h"

TEST(LocationConfigTest, DefaultConstructor) {
    LocationConfig config;

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
    EXPECT_TRUE(config.getPaths().empty());
}

TEST(LocationConfigTest, ParameterizedConstructor) {
    std::set<std::string>         paths = {"/path1", "/path2"};
    size_t                        port = 8080;
    std::set<std::string>         name = {"name"};
    size_t                        size = 1024;
    std::set<std::string>         indx = {"index.html"};
    std::set<std::string>         root_dir = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods = {"GET"};
    bool                          auto_index = false;

    LocationConfig config(paths, port, name, size, indx, root_dir, error_page,
                          return_page, methods, auto_index);

    // Check if the values are correctly set
    EXPECT_EQ(config.getPaths(), paths);
    EXPECT_EQ(config.port_number(), port);
    EXPECT_EQ(config.server_name(), name);
    EXPECT_EQ(config.client_max_body_size(), size);
    EXPECT_EQ(config.index(), indx);
    EXPECT_EQ(config.root(), root_dir);
    EXPECT_EQ(config.error_page(), error_page);
    EXPECT_EQ(config.return_page(), return_page);
    EXPECT_EQ(config.allow_methods(), methods);
    EXPECT_EQ(config.autoindex(), auto_index);
}

TEST(LocationConfigTest, CopyConstructor) {
    std::set<std::string>         paths = {"/path1", "/path2"};
    size_t                        port = 8080;
    std::set<std::string>         name = {"name"};
    size_t                        size = 1024;
    std::set<std::string>         indx = {"index.html"};
    std::set<std::string>         root_dir = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods = {"GET"};
    bool                          auto_index = false;

    LocationConfig config1(paths, port, name, size, indx, root_dir, error_page,
                           return_page, methods, auto_index);
    LocationConfig config2(config1);

    // Check if the values are correctly copied
    EXPECT_EQ(config2, config1);
}

TEST(LocationConfigTest, AssignmentOperator) {
    std::set<std::string>         paths = {"/path1", "/path2"};
    size_t                        port = 8080;
    std::set<std::string>         name = {"name"};
    size_t                        size = 1024;
    std::set<std::string>         indx = {"index.html"};
    std::set<std::string>         root_dir = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods = {"GET"};
    bool                          auto_index = false;

    LocationConfig config1(paths, port, name, size, indx, root_dir, error_page,
                           return_page, methods, auto_index);
    LocationConfig config2;
    config2 = config1;

    // Check if the values are correctly copied
    EXPECT_EQ(config2, config1);

    // Test self-assignment
    config2 = config2;
    EXPECT_EQ(config2, config1);
}

TEST(LocationConfigTest, AddPath) {
    LocationConfig config;
    std::string    path = "/path1";

    config.addPath(path);

    // Check if the path is correctly added
    EXPECT_EQ(config.getPaths().size(), 1);
    EXPECT_EQ(*(config.getPaths().begin()), path);
}

TEST(LocationConfigTest, AddPaths) {
    LocationConfig           config;
    std::vector<std::string> paths = {"/path1", "/path2"};

    config.addPath(paths);

    // Check if the paths are correctly added
    EXPECT_EQ(config.getPaths().size(), 2);
    EXPECT_EQ(config.getPaths(),
              std::set<std::string>(paths.begin(), paths.end()));
}

#include "../src/config/LocationConfig.hpp"
#include "gtest/gtest.h"

TEST(LocationConfigTest, SetPortNumber) {
    LocationConfig config;
    size_t         port = 8080;

    config.set_port_number(port);

    // Check if the port number is correctly set
    EXPECT_EQ(config.port_number(), port);
}

TEST(LocationConfigTest, SetServerName) {
    LocationConfig        config;
    std::set<std::string> name = {"example.com"};

    config.set_server_name(name);

    // Check if the server name is correctly set
    EXPECT_EQ(config.server_name(), name);
}

TEST(LocationConfigTest, SetClientMaxBodySize) {
    LocationConfig config;
    size_t         size = 2048;

    config.set_client_max_body_size(size);

    // Check if the client max body size is correctly set
    EXPECT_EQ(config.client_max_body_size(), size);
}

TEST(LocationConfigTest, SetIndex) {
    LocationConfig        config;
    std::set<std::string> indx = {"home.html"};

    config.set_index(indx);

    // Check if the index is correctly set
    EXPECT_EQ(config.index(), indx);
}

TEST(LocationConfigTest, SetRoot) {
    LocationConfig        config;
    std::set<std::string> root_dir = {"www"};

    config.set_root(root_dir);

    // Check if the root directory is correctly set
    EXPECT_EQ(config.root(), root_dir);
}

TEST(LocationConfigTest, SetErrorPage) {
    LocationConfig                config;
    std::map<size_t, std::string> error_page = {{500, "error.html"}};

    config.set_error_page(error_page);

    // Check if the error page is correctly set
    EXPECT_EQ(config.error_page(), error_page);
}

TEST(LocationConfigTest, SetReturnPage) {
    LocationConfig                config;
    std::map<size_t, std::string> return_page = {{302, "redirect.html"}};

    config.set_return(return_page);

    // Check if the return page is correctly set
    EXPECT_EQ(config.return_page(), return_page);
}

TEST(LocationConfigTest, SetAllowMethods) {
    LocationConfig        config;
    std::set<std::string> methods = {"GET", "POST"};

    config.set_allow_methods(methods);

    // Check if the allowed methods are correctly set
    EXPECT_EQ(config.allow_methods(), methods);
}

TEST(LocationConfigTest, SetAutoindex) {
    LocationConfig config;
    bool           auto_index = true;

    config.set_autoindex(auto_index);

    // Check if the autoindex flag is correctly set
    EXPECT_EQ(config.autoindex(), auto_index);
}
