#include "../src/config/ConfigParse.hpp"
#include "gtest/gtest.h"
#include <fstream>

TEST(ConfigParseTest, DefaultConstructor) {
    ConfigParse configParse;

    // There's no state to check in ConfigParse after construction,
    // so we're just checking that the constructor doesn't throw an exception
    SUCCEED();
}

TEST(ConfigParseTest, ParseFile) {
    ConfigParse configParse;

    // Create a temporary file with some content
    std::ofstream outfile("temp.txt");
    outfile << "server { listen 80; }";
    outfile.close();

    // Check if the parseFile function doesn't throw an exception
    EXPECT_NO_THROW(configParse.parseFile("temp.txt"));

    // Delete the temporary file
    std::remove("temp.txt");
}

TEST(ConfigParseTest, ParseFileNonExistent) {
    ConfigParse configParse;

    // Check if the parseFile function throws an exception for a non-existent
    // file
    EXPECT_EXIT(configParse.parseFile("non_existent.txt"),
                ::testing::ExitedWithCode(1),
                "Can't open file: non_existent.txt");
}

TEST(ConfigParseTest, Parse) {
    ConfigParse configParse;

    // Check if the _parse function doesn't throw an exception for a valid
    // source string
    EXPECT_NO_THROW(configParse._parse("server { listen 80; }"));
}

TEST(ConfigParseTest, ParseInvalid) {
    ConfigParse configParse;

    // Check if the _parse function throws an exception for an invalid source
    // string
    EXPECT_NO_THROW(configParse._parse("server { listen; }"));
}

TEST(ConfigParseTest, ToString) {
    ConfigParse configParse;

    // Check if the toString function correctly converts an integer to a string
    EXPECT_EQ(configParse.toString(123), "123");
}
