#include "CShmBase.h"
#include "gtest/gtest.h"
#include "file_utils.h"

#define TEST_SHM "digilo_test"
#define TEST_SHM_SIZE 4000U

class ShmBase : public ::testing::Test {
protected:
    virtual void SetUp() {
        ::testing::Test::SetUp();  // Sets up the base fixture first.
        TearDown();
    }

    virtual void TearDown() {
        ::testing::Test::TearDown();
        remove("/dev/shm/"TEST_SHM);
    }
};

TEST(ShmBase, Open) {
    CShmBase test;
    EXPECT_TRUE(test.Open(TEST_SHM, TEST_SHM_SIZE));
    EXPECT_TRUE(is_file_exist("/dev/shm/"TEST_SHM));
    EXPECT_NE((uint8_t *) NULL, test.GetData());
    EXPECT_EQ(TEST_SHM_SIZE, test.GetSize());
}

TEST(ShmBase, OpenInvalidSize) {
    CShmBase test;
    EXPECT_TRUE(test.Open(TEST_SHM, TEST_SHM_SIZE));
    test.Close();
    EXPECT_FALSE(test.Open(TEST_SHM, TEST_SHM_SIZE+1));
}
