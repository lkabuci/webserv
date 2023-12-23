//#include "gtest/gtest.h"
//#include "../src/config/RunTimeException.hpp"
//#include "../src/config/Env.hpp"

//TEST(EnvTest, CreateServerConfig) {
//    Env& env = Env::getInstance();
//    env.create(SERVER);
//    std::vector<ServerConfig> configs = env.get();
//    EXPECT_EQ(configs.size(), 0); // No ServerConfig added yet
//}

//TEST(EnvTest, CreateLocationConfig) {
//    Env& env = Env::getInstance();
//    env.create(SERVER);
//    env.create(LOCATION);
//    std::vector<ServerConfig> configs = env.get();
//    EXPECT_EQ(configs.size(), 0); // No ServerConfig added yet
//}

//TEST(EnvTest, AddServerConfig) {
//    Env& env = Env::getInstance();
//    env.create(SERVER);
//    env.add(SERVER);
//    std::vector<ServerConfig> configs = env.get();
//    EXPECT_EQ(configs.size(), 1); // One ServerConfig added
//}

//TEST(EnvTest, AddLocationConfig) {
//    Env& env = Env::getInstance();
//    env.create(SERVER);
//    env.create(LOCATION);
//    env.add(LOCATION);
//    std::vector<ServerConfig> configs = env.get();
//    EXPECT_EQ(configs.size(), 1); // One ServerConfig with one LocationConfig added
//    EXPECT_EQ(configs[0].getLocations().size(), 1); // One LocationConfig in the ServerConfig
//}

//TEST(EnvTest, PutServerConfig) {
//    Env& env = Env::getInstance();
//    env.create(SERVER);
//    std::vector<std::string> value = {"8080"};
//    Token token(LISTEN, "8080", 1);
//    env.put(value, token);
//    env.add(SERVER);
//    std::vector<ServerConfig> configs = env.get();
//    EXPECT_EQ(configs[0].port_number(), 8080); // Port number correctly set
//}

////TEST(EnvTest, PutLocationConfig) {
////    Env& env = Env::getInstance();
////    env.create(SERVER);
////    env.create(LOCATION);
////    std::vector<std::string> value = {"/"};
////    Token token(ROOT, "/", 1);
////    env.put(value, token);
////    env.add(LOCATION);
////    std::vector<ServerConfig> configs = env.get();
////    EXPECT_EQ(configs[0].getLocations()[0].root(), "/"); // Root correctly set
////}

//TEST(EnvTest, PutInvalidDirective) {
//    Env& env = Env::getInstance();
//    env.create(SERVER);
//    std::vector<std::string> value = {"invalid"};
//    Token token(END, "invalid", 1);
//    EXPECT_THROW(env.put(value, token), RunTimeException); // Invalid directive throws exception
//}
