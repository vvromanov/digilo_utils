#include "CShmDictionary.h"
#include "gtest/gtest.h"

#define TEST_FILE "/tmp/file_utils.tst"
#define TEST_FILE_INVALID "/_##/"

TEST(ShmDictionary, Add) {
    CShmDictionary d;
    d.Clear();
    EXPECT_EQ(0, d.Add("e"));
    EXPECT_EQ(1, d.Add("f"));
    EXPECT_EQ(2, d.Add("g"));
    EXPECT_EQ(2, d.Add("g"));
    EXPECT_EQ(0, d.Add("e"));
    EXPECT_EQ(3, d.Add("a"));
    EXPECT_EQ(4, d.Add("b"));
}

TEST(ShmDictionary, TooManyItems) {
    CShmDictionary d;
    d.Clear();
    for (uint32_t i = 0; i < DICTIONARY_SIZE; i++) {
        char tmp[10];
        snprintf(tmp, sizeof(tmp), "%X", i);
        EXPECT_EQ(i, d.Add(tmp));
    }
    EXPECT_EQ(DICTIONARY_INVALID_INDEX, d.Add("xxx"));
}

TEST(ShmDictionary, TooLongNames) {
    CShmDictionary d;
    d.Clear();
    int str_size = 0;
    for (uint32_t i = 0; i < DICTIONARY_SIZE; i++) {
        char tmp[1000];
        snprintf(tmp, sizeof(tmp),
                 "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++%X",
                 i);
        str_size += strlen(tmp) + 1;
        if (str_size >= DICTIONARY_NAMES_STORAGE_SIZE) {
            EXPECT_EQ(DICTIONARY_INVALID_INDEX, d.Add(tmp));
            break;
        } else {
            EXPECT_EQ(i, d.Add(tmp));
        }
    }
}

TEST(ShmDictionary, LookupByName) {
    CShmDictionary d;
    d.Clear();
    EXPECT_EQ(DICTIONARY_INVALID_INDEX, d.Lookup("e"));
    EXPECT_EQ(0, d.Add("e"));
    EXPECT_EQ(1, d.Add("f"));
    EXPECT_EQ(2, d.Add("g"));
    EXPECT_EQ(2, d.Add("g"));
    EXPECT_EQ(0, d.Add("e"));
    EXPECT_EQ(3, d.Add("a"));
    EXPECT_EQ(4, d.Add("b"));
    EXPECT_EQ(DICTIONARY_INVALID_INDEX, d.Lookup("xxx"));
    EXPECT_EQ(0, d.Lookup("e"));
    EXPECT_EQ(1, d.Lookup("f"));
    EXPECT_EQ(2, d.Lookup("g"));
    EXPECT_EQ(3, d.Lookup("a"));
    EXPECT_EQ(4, d.Lookup("b"));
}

TEST(ShmDictionary, LookupById) {
    CShmDictionary d;
    d.Clear();
    EXPECT_EQ(DICTIONARY_INVALID_INDEX, d.Lookup("e"));
    EXPECT_EQ(0, d.Add("e"));
    EXPECT_EQ(1, d.Add("f"));
    EXPECT_EQ(2, d.Add("g"));
    EXPECT_EQ(2, d.Add("g"));
    EXPECT_EQ(0, d.Add("e"));
    EXPECT_EQ(3, d.Add("a"));
    EXPECT_EQ(4, d.Add("b"));
    EXPECT_EQ(NULL, d.Lookup(DICTIONARY_INVALID_INDEX));
    EXPECT_EQ(NULL, d.Lookup(-3));
    EXPECT_EQ(NULL, d.Lookup(5));
    EXPECT_STREQ("e", d.Lookup(0));
    EXPECT_STREQ("f", d.Lookup(1));
    EXPECT_STREQ("g", d.Lookup(2));
    EXPECT_STREQ("a", d.Lookup(3));
    EXPECT_STREQ("b", d.Lookup(4));
}
