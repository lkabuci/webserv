#include "../include/webserv.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

TEST(AddressResolverTest, ConstructorTest) {
    AddressResolver resolver("127.0.0.1", "8080");
    EXPECT_NE(resolver.getAddresses(), nullptr);
}

TEST(AddressResolverTest, GetAddressesTest) {
    AddressResolver resolver("127.0.0.1", "8080");
    EXPECT_NE(resolver.getAddresses(), nullptr);
}

TEST(AddressResolverTest, FillAddressInfoTest) {
    AddressResolver resolver("127.0.0.1", "8080");
    EXPECT_NE(resolver.getAddresses(), nullptr);
}

TEST(AddressResolverTest, DestructorTest) {
    AddressResolver* resolver = new AddressResolver("127.0.0.1", "8080");
    delete resolver;
}

} // namespace
