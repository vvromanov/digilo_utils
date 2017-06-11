#include "file_utils.h"
#include "gtest/gtest.h"

#define TEST_FILE "/tmp/file_utils.tst"
#define TEST_FILE_INVALID "/_##/"

TEST(FileUtils, FileExists) {
}

TEST(FileUtils, FileNotExists) {
    remove(TEST_FILE);
    EXPECT_FALSE(is_file_exist(TEST_FILE));
}


TEST(FileUtils, FileNotExistsInvalid) {
    remove(TEST_FILE);
    EXPECT_FALSE(is_file_exist(""));
    EXPECT_FALSE(is_file_exist(TEST_FILE_INVALID));
}
