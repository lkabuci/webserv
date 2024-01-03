#include "../include/webserv.h"
#include <gtest/gtest.h>

// namespace {

// TEST(SocketTest, ConstructorTest) {
//     Socket socket("127.0.0.1", "8080");
//     EXPECT_GE(socket.getSocketfd(), 0);
//     EXPECT_STREQ(socket.getIP(), "127.0.0.1");
//     EXPECT_STREQ(socket.getPort(), "8080");
// }

// TEST(SocketTest, InitializeSocketTest) {
//     Socket socket("127.0.0.1", "8080");
//     EXPECT_GE(socket.getSocketfd(), 0);
// }
// TEST(SocketTest, InvalidIPTest) {
//     // An invalid IP should cause the constructor to throw an exception.
//     EXPECT_THROW(Socket socket("256.0.0.1", "8080"), std::runtime_error);
// }

// TEST(SocketTest, InvalidPortTest) {
//     // An invalid port should cause the constructor to throw an exception.
//     EXPECT_THROW(Socket socket("127.0.0.1", "70000"), std::runtime_error);
// }

// TEST(SocketTest, EmptyIPTest) {
//     // An empty IP should cause the constructor to throw an exception.
//     EXPECT_THROW(Socket socket("", "8080"), std::runtime_error);
// }

// TEST(SocketTest, EmptyPortTest) {
//     // An empty port should cause the constructor to throw an exception.
//     EXPECT_THROW(Socket socket("127.0.0.1", ""), std::runtime_error);
// }
// } // namespace
