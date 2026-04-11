#include "../src/config/ConfigParse.hpp"
#include "gtest/gtest.h"
#include <cstdio>
#include <fstream>

static const char* TEMP_CONF = "temp_valid.conf";
static const char* NONEXIST = "non_existent_xyz.conf";

// Write a minimal valid server block to a temp file.
static void writeTempConf(const char* path,
                          const char* content = "server { listen 80; }") {
    std::ofstream out(path);
    out << content;
}

// ── Construction ─────────────────────────────────────────────────────────────

TEST(ConfigParseTest, ConstructWithValidFile) {
    writeTempConf(TEMP_CONF);
    EXPECT_NO_THROW(ConfigParse cp(TEMP_CONF));
    std::remove(TEMP_CONF);
}

TEST(ConfigParseTest, ConstructWithNonExistentFileExits) {
    EXPECT_EXIT(ConfigParse cp(NONEXIST), ::testing::ExitedWithCode(1),
                "Can't open file");
}

// ── parseFile ────────────────────────────────────────────────────────────────

TEST(ConfigParseTest, ParseFileValid) {
    writeTempConf(TEMP_CONF);
    ConfigParse cp(TEMP_CONF);
    // Calling parseFile again on an existing file should not throw.
    EXPECT_NO_THROW(cp.parseFile(TEMP_CONF));
    std::remove(TEMP_CONF);
}

TEST(ConfigParseTest, ParseFileNonExistentExits) {
    writeTempConf(TEMP_CONF);
    ConfigParse cp(TEMP_CONF);
    std::remove(TEMP_CONF);
    EXPECT_EXIT(cp.parseFile(NONEXIST), ::testing::ExitedWithCode(1),
                "Can't open file");
}

// ── _parse ───────────────────────────────────────────────────────────────────

TEST(ConfigParseTest, ParseValidSource) {
    writeTempConf(TEMP_CONF);
    ConfigParse cp(TEMP_CONF);
    std::remove(TEMP_CONF);
    // _parse catches exceptions internally — valid input should not throw.
    EXPECT_NO_THROW(cp._parse("server { listen 80; }"));
}

TEST(ConfigParseTest, ParseInvalidSourceNoThrow) {
    writeTempConf(TEMP_CONF);
    ConfigParse cp(TEMP_CONF);
    std::remove(TEMP_CONF);
    // _parse swallows parse errors via try/catch — must not propagate.
    EXPECT_NO_THROW(cp._parse("server { listen; }"));
}

// ── toString ─────────────────────────────────────────────────────────────────

TEST(ConfigParseTest, ToStringPositive) {
    EXPECT_EQ(ConfigParse::toString(123), "123");
}

TEST(ConfigParseTest, ToStringZero) {
    EXPECT_EQ(ConfigParse::toString(0), "0");
}

TEST(ConfigParseTest, ToStringNegative) {
    EXPECT_EQ(ConfigParse::toString(-7), "-7");
}
