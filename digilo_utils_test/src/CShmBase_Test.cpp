#include "CShmBase.h"
#include "gtest/gtest.h"
#include "file_utils.h"
#include "log.h"

#define TEST_SHM "digilo_test"
#define TEST_SHM_FILE "/dev/shm/"TEST_SHM
#define TEST_SHM_SIZE 4000U

class ShmBase : public ::testing::Test {
protected:
    virtual void SetUp() {
        ::testing::Test::SetUp();  // Sets up the base fixture first.
        TearDown();
        EXPECT_FALSE(is_file_exist(TEST_SHM_FILE));
    }

    virtual void TearDown() {
        ::testing::Test::TearDown();
        if (is_file_exist(TEST_SHM_FILE)) {
            if (0 == remove(TEST_SHM_FILE)) {
                log_write(LOG_NOTICE, "File %s removed", TEST_SHM_FILE);
            } else {
                log_write(LOG_ERR | LOG_ERRNO, "Can't remove %s file", TEST_SHM_FILE);
            }
        }
    }
};

TEST_F(ShmBase, Open) {
    CShmBase test;
    EXPECT_TRUE(test.Open(TEST_SHM, TEST_SHM_SIZE));
    EXPECT_TRUE(is_file_exist(TEST_SHM_FILE));
    EXPECT_NE((uint8_t *) NULL, test.GetData());
    EXPECT_EQ(TEST_SHM_SIZE, test.GetSize());
}

TEST_F(ShmBase, OpenInvalidSize) {
    CShmBase test;
    EXPECT_TRUE(test.Open(TEST_SHM, TEST_SHM_SIZE));
    test.Close();
    EXPECT_FALSE(test.Open(TEST_SHM, TEST_SHM_SIZE + 1));
}

TEST_F(ShmBase, AlreadyOpen) {
    CShmBase test;
    EXPECT_TRUE(test.Open(TEST_SHM, TEST_SHM_SIZE));
    EXPECT_FALSE(test.Open(TEST_SHM, TEST_SHM_SIZE));
}

TEST_F(ShmBase, ReOpen) {
    CShmBase test1, test2;
    EXPECT_TRUE(test1.Open(TEST_SHM, TEST_SHM_SIZE));
    EXPECT_TRUE(test2.Open(TEST_SHM, 0));
}

TEST_F(ShmBase, ReOpenFailed) {
    CShmBase test;
    EXPECT_FALSE(test.Open(TEST_SHM, 0));
}

TEST_F(ShmBase, TooBigSize) {
    CShmBase test;
    EXPECT_FALSE(test.Open(TEST_SHM, 1024UL * 1024UL * 1024UL * 100UL)); //100 Gn
}
