#include "log.h"
#include "gtest/gtest.h"

#define TEST_FILE "/tmp/file_utils.tst"
#define TEST_FILE_INVALID "/_##/"

TEST(Log, LevelToName) {
    EXPECT_STREQ("EMRG", log_level_to_name(LOG_EMERG));
    EXPECT_STREQ("ALRT", log_level_to_name(LOG_ALERT));
    EXPECT_STREQ("CRIT", log_level_to_name(LOG_CRIT));
    EXPECT_STREQ("ERRR", log_level_to_name(LOG_ERR));
    EXPECT_STREQ("WARN", log_level_to_name(LOG_WARNING));
    EXPECT_STREQ("NOTI", log_level_to_name(LOG_NOTICE));
    EXPECT_STREQ("INFO", log_level_to_name(LOG_INFO));
    EXPECT_STREQ("DEBG", log_level_to_name(LOG_DEBUG));
    EXPECT_STREQ("DEBG", log_level_to_name(-1));
}

TEST(Log, LinesCount) {
    log_lines_count[LOG_NOTICE] = 0;
    log_write(LOG_NOTICE, "test");
    EXPECT_EQ(1, log_lines_count[LOG_NOTICE]);
    log_write(LOG_NOTICE | LOG_ERRNO, "test");
    EXPECT_EQ(2, log_lines_count[LOG_NOTICE]);
}
