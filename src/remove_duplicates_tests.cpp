
#include "remove_duplicates.h"

#include "gtest/gtest.h"

TEST(RemoveDuplicates, SimpleTest) {
    std::string s = "abbccadeefghhhaaaa";
    RemoveDuplicates(s);
    ASSERT_EQ("abcdefgh", s);
}

TEST(RemoveDuplicates, EmptyStringTest) {
    std::string s;
    RemoveDuplicates(s);
    ASSERT_TRUE(s.empty());
}
