#include "../src/config/Env.hpp"
#include "gtest/gtest.h"

TEST(EnvTest, SingletonTest) {
    Env& env1 = Env::getInstance();
    Env& env2 = Env::getInstance();

    // Check if the same instance is returned
    EXPECT_EQ(&env1, &env2);
}

TEST(EnvTest, CreateServerConfig) {
    Env& env = Env::getInstance();

    Env::create(SERVER);

    // Check if a ServerConfig object is created
    EXPECT_NE(dynamic_cast<ServerConfig*>(env._ptr), nullptr);
}

TEST(EnvTest, CreateLocationConfig) {
    Env& env = Env::getInstance();

    Env::create(LOCATION);

    // Check if a LocationConfig object is created
    EXPECT_NE(dynamic_cast<LocationConfig*>(env._ptr), nullptr);
}

TEST(EnvTest, AddLocationConfig) {
    Env& env = Env::getInstance();

    Env::create(SERVER);
    Env::create(LOCATION);
    Env::add(LOCATION);
    Env::add(SERVER);

    // Check if a LocationConfig object is added to the last ServerConfig object
    EXPECT_EQ(env.get().back().getLocations().size(), 1);
}

TEST(EnvTest, Put) {
    Env& env = Env::getInstance();

    Env::create(SERVER);
    std::vector<std::string> value = {"8080"};
    Token                    token(LISTEN, "listen", 1);
    Env::put(value, token);

    // Check if the port number is correctly set
    EXPECT_EQ(env._ptr->port_number(), 8080);
}

// Add more tests for other methods and edge cases
