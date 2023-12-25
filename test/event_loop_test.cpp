// FILEPATH: /Users/relkabou/Desktop/webserv/test/event_loop_test.cpp

#include "../include/webserv.h"
#include <gtest/gtest.h>

namespace {

TEST(EventLoopTest, AddClientTest) {
    EventLoop::addClient(4);
    EXPECT_EQ(1, EventLoop::getSize());
    EXPECT_EQ(4, EventLoop::getFd(0));
}

TEST(EventLoopTest, RemoveClientTest) {
    EventLoop::addClient(5);
    EventLoop::removeClient(0);
    EXPECT_EQ(1, EventLoop::getSize());
}

// TEST(EventLoopTest, IsEventSetTest) {
//     EventLoop::addClient(7);
//     EventLoop::setEvent(0, POLLIN);
//     EXPECT_TRUE(EventLoop::isEventSet(0, POLLIN));
// }

// TEST(EventLoopTest, SetEventTest) {
//     EventLoop::addClient(5);
//     EventLoop::setEvent(0, POLLOUT);
//     EXPECT_TRUE(EventLoop::isEventSet(0, POLLOUT));
// }

} // namespace
