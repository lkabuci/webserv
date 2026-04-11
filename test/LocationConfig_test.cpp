#include "../src/config/LocationConfig.hpp"
#include "gtest/gtest.h"

// ── Default constructor ───────────────────────────────────────────────────────

TEST(LocationConfigTest, DefaultConstructor) {
    LocationConfig config;

    EXPECT_EQ(config.port(), "8000");               // default port string
    EXPECT_EQ(*(config.server_name().begin()), "_"); // default server_name
    EXPECT_EQ(config.client_max_body_size(), 100u);
    EXPECT_TRUE(config.index().empty());
    EXPECT_TRUE(config.root().empty());
    EXPECT_TRUE(config.error_page().empty());
    EXPECT_TRUE(config.return_page().empty());
    EXPECT_TRUE(config.allow_methods().empty());
    EXPECT_FALSE(config.autoindex());
    EXPECT_TRUE(config.getPaths().empty());
}

// ── Parameterized constructor ─────────────────────────────────────────────────

TEST(LocationConfigTest, ParameterizedConstructor) {
    std::set<std::string>         paths      = {"/path1", "/path2"};
    std::string                   ip         = "127.0.0.1";
    std::string                   port_str   = "8080";
    std::set<std::string>         name       = {"name"};
    size_t                        size       = 1024;
    std::set<std::string>         index      = {"index.html"};
    std::set<std::string>         root_dir   = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods    = {"GET"};
    bool                          auto_index = false;

    LocationConfig config(paths, ip, port_str, name, size, index, root_dir,
                          error_page, return_page, methods, auto_index);

    EXPECT_EQ(config.getPaths(), paths);
    EXPECT_EQ(config.port(), port_str);
    EXPECT_EQ(config.server_name(), name);
    EXPECT_EQ(config.client_max_body_size(), size);
    EXPECT_EQ(config.index(), index);
    EXPECT_EQ(config.root(), root_dir);
    EXPECT_EQ(config.error_page(), error_page);
    EXPECT_EQ(config.return_page(), return_page);
    EXPECT_EQ(config.allow_methods(), methods);
    EXPECT_EQ(config.autoindex(), auto_index);
}

// ── Copy constructor ──────────────────────────────────────────────────────────

TEST(LocationConfigTest, CopyConstructor) {
    std::set<std::string>         paths      = {"/path1", "/path2"};
    std::set<std::string>         name       = {"name"};
    size_t                        size       = 1024;
    std::set<std::string>         index      = {"index.html"};
    std::set<std::string>         root_dir   = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods    = {"GET"};

    LocationConfig config1(paths, "127.0.0.1", "8080", name, size, index,
                           root_dir, error_page, return_page, methods, false);
    const LocationConfig& config2(config1);

    EXPECT_EQ(config2, config1);
}

// ── Assignment operator ───────────────────────────────────────────────────────

TEST(LocationConfigTest, AssignmentOperator) {
    std::set<std::string>         paths      = {"/path1", "/path2"};
    std::set<std::string>         name       = {"name"};
    size_t                        size       = 1024;
    std::set<std::string>         index      = {"index.html"};
    std::set<std::string>         root_dir   = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods    = {"GET"};

    LocationConfig config1(paths, "127.0.0.1", "8080", name, size, index,
                           root_dir, error_page, return_page, methods, false);
    LocationConfig config2;
    config2 = config1;

    EXPECT_EQ(config2, config1);
    config2 = config2; // self-assignment
    EXPECT_EQ(config2, config1);
}

// ── addPath ───────────────────────────────────────────────────────────────────

TEST(LocationConfigTest, AddPath) {
    LocationConfig config;
    config.addPath("/path1");

    EXPECT_EQ(config.getPaths().size(), 1u);
    EXPECT_EQ(*(config.getPaths().begin()), "/path1");
}

TEST(LocationConfigTest, AddPaths) {
    LocationConfig           config;
    std::vector<std::string> paths = {"/path1", "/path2"};
    config.addPath(paths);

    EXPECT_EQ(config.getPaths().size(), 2u);
    EXPECT_EQ(config.getPaths(),
              std::set<std::string>(paths.begin(), paths.end()));
}

// ── Setters ───────────────────────────────────────────────────────────────────

TEST(LocationConfigTest, SetPort) {
    LocationConfig config;
    config.set_port("8080");
    EXPECT_EQ(config.port(), "8080");
}

TEST(LocationConfigTest, SetServerName) {
    LocationConfig        config;
    std::set<std::string> name = {"example.com"};
    config.set_server_name(name);
    EXPECT_EQ(config.server_name(), name);
}

TEST(LocationConfigTest, SetClientMaxBodySize) {
    LocationConfig config;
    config.set_client_max_body_size(2048);
    EXPECT_EQ(config.client_max_body_size(), 2048u);
}

TEST(LocationConfigTest, SetIndex) {
    LocationConfig        config;
    std::set<std::string> index = {"home.html"};
    config.set_index(index);
    EXPECT_EQ(config.index(), index);
}

TEST(LocationConfigTest, SetRoot) {
    LocationConfig        config;
    std::set<std::string> root_dir = {"www"};
    config.set_root(root_dir);
    EXPECT_EQ(config.root(), root_dir);
}

TEST(LocationConfigTest, SetErrorPage) {
    LocationConfig                config;
    std::map<size_t, std::string> error_page = {{500, "error.html"}};
    config.set_error_page(error_page);
    EXPECT_EQ(config.error_page(), error_page);
}

TEST(LocationConfigTest, SetReturnPage) {
    LocationConfig                config;
    std::map<size_t, std::string> return_page = {{302, "redirect.html"}};
    config.set_return(return_page);
    EXPECT_EQ(config.return_page(), return_page);
}

TEST(LocationConfigTest, SetAllowMethods) {
    LocationConfig        config;
    std::set<std::string> methods = {"GET", "POST"};
    config.set_allow_methods(methods);
    EXPECT_EQ(config.allow_methods(), methods);
}

TEST(LocationConfigTest, SetAutoindex) {
    LocationConfig config;
    config.set_autoindex(true);
    EXPECT_TRUE(config.autoindex());
}
