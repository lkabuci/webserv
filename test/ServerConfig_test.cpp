#include "../src/config/ServerConfig.hpp"
#include "gtest/gtest.h"

// ── Default constructor ───────────────────────────────────────────────────────

TEST(ServerConfigTest, DefaultConstructor) {
    ServerConfig config;

    EXPECT_EQ(config.port(), "8000");               // default port string
    EXPECT_EQ(*(config.server_name().begin()), "_"); // default server_name
    EXPECT_EQ(config.client_max_body_size(), 100u);
    EXPECT_TRUE(config.index().empty());
    EXPECT_TRUE(config.root().empty());
    EXPECT_TRUE(config.error_page().empty());
    EXPECT_TRUE(config.return_page().empty());
    EXPECT_TRUE(config.allow_methods().empty());
    EXPECT_FALSE(config.autoindex());
    EXPECT_TRUE(config.getLocations().empty());
}

// ── Parameterized constructor ─────────────────────────────────────────────────

TEST(ServerConfigTest, ParameterizedConstructor) {
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

    ServerConfig config(ip, port_str, name, size, index, root_dir, error_page,
                        return_page, methods, auto_index);

    EXPECT_EQ(config.port(), port_str);
    EXPECT_EQ(config.server_name(), name);
    EXPECT_EQ(config.client_max_body_size(), size);
    EXPECT_EQ(config.index(), index);
    EXPECT_EQ(config.root(), root_dir);
    EXPECT_EQ(config.error_page(), error_page);
    EXPECT_EQ(config.return_page(), return_page);
    EXPECT_EQ(config.allow_methods(), methods);
    EXPECT_EQ(config.autoindex(), auto_index);
    EXPECT_TRUE(config.getLocations().empty());
}

// ── Copy constructor ──────────────────────────────────────────────────────────

TEST(ServerConfigTest, CopyConstructor) {
    std::set<std::string>         name       = {"name"};
    size_t                        size       = 1024;
    std::set<std::string>         index      = {"index.html"};
    std::set<std::string>         root_dir   = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods    = {"GET"};

    ServerConfig config1("127.0.0.1", "8080", name, size, index, root_dir,
                         error_page, return_page, methods, false);
    ServerConfig config2(config1);

    EXPECT_EQ(config2, config1);
}

// ── Assignment operator ───────────────────────────────────────────────────────

TEST(ServerConfigTest, AssignmentOperator) {
    std::set<std::string>         name       = {"name"};
    size_t                        size       = 1024;
    std::set<std::string>         index      = {"index.html"};
    std::set<std::string>         root_dir   = {"root"};
    std::map<size_t, std::string> error_page = {{404, "notfound.html"}};
    std::map<size_t, std::string> return_page = {{301, "moved.html"}};
    std::set<std::string>         methods    = {"GET"};

    ServerConfig config1("127.0.0.1", "8080", name, size, index, root_dir,
                         error_page, return_page, methods, false);
    ServerConfig config2;
    config2 = config1;

    EXPECT_EQ(config2, config1);
    config2 = config2; // self-assignment
    EXPECT_EQ(config2, config1);
}

// ── addLocation ───────────────────────────────────────────────────────────────

TEST(ServerConfigTest, AddLocation) {
    ServerConfig   config;
    LocationConfig location;

    config.addLocation(location);

    EXPECT_EQ(config.getLocations().size(), 1u);
    EXPECT_EQ(config.getLocations()[0], location);
}
