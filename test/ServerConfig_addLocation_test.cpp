//#include "gtest/gtest.h"
//#include "../src/core/ServerConfig.hpp"
//#include "../src/core/LocationConfig.hpp"

//TEST(ServerConfigTest, AddLocation) {
//    ServerConfig config;
//    std::vector<std::string> errorPage = {"error.html"};
//    std::vector<std::string> indexFile = {"index1.html", "index2.html"};
//    LocationConfig location(8080, "localhost", 2, errorPage, indexFile, "/root", true, {"301", "http://www.google.com"});

//    // Initially, the locations vector should be empty
//    EXPECT_TRUE(config.getLocations().empty());

//    // Add a location
//    config.addLocation(location);

//    // Now, the locations vector should have one element
//    EXPECT_EQ(config.getLocations().size(), 1);

//    // Check that the added location is correct
//    LocationConfig addedLocation = config.getLocations()[0];
//    EXPECT_EQ(addedLocation.getPort(), 8080);
//    EXPECT_EQ(addedLocation.getHost(), "localhost");
//    EXPECT_EQ(addedLocation.getClientMaxBodySize(), 2);
//    EXPECT_EQ(addedLocation.getErrorPage(), errorPage);
//    EXPECT_EQ(addedLocation.getIndexFile(), indexFile);
//    EXPECT_EQ(addedLocation.getRootDir(), "/root");
//    EXPECT_TRUE(addedLocation.getAutoIndex());
//    EXPECT_EQ(addedLocation.getReturnDirective(), std::vector<std::string>({"301", "http://www.google.com"}));
//}
