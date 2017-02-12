
#include "misc.h"

#include "gtest/gtest.h"


TEST(Misc, StackTricks) {
    int a = 11;
    int b = 15;
    int *pa = &a;
    int *pb = &b;
    ASSERT_EQ(1, pa - pb);
    ASSERT_EQ(11, pb[1]);
    ASSERT_EQ(15, *(&a - 1));
    ASSERT_EQ(11, 1[&b]);

    1[&b] = 50;
    ASSERT_EQ(50, a);
}

TEST(Misc, MostConsecutiveChar) {
    auto c1 = MostConsecutiveChar("1234346567867aaa3");
    ASSERT_EQ(3, c1.first);
    ASSERT_EQ('a', c1.second);

    auto c2 = MostConsecutiveChar("");
    ASSERT_EQ(0, c2.first);
    ASSERT_EQ('\0', c2.second);

    auto c3 = MostConsecutiveChar("7777777");
    ASSERT_EQ(7, c3.first);
    ASSERT_EQ('7', c3.second);
}

TEST(Misc, FormatNum) {
    ASSERT_EQ("1,000,000", FormatNum(1000000, UsaStyle));
    ASSERT_EQ("15", FormatNum(15, UsaStyle));
    ASSERT_EQ("-1,500,000", FormatNum(-1500000, UsaStyle));
    ASSERT_EQ("0", FormatNum(0, UsaStyle));
    ASSERT_EQ("1,00,00,000", FormatNum(10000000, IndiaStyle));
}

TEST(Misc, SumsCount) {
    ASSERT_EQ(1, SumsCount(1));
    ASSERT_EQ(2, SumsCount(2));
    ASSERT_EQ(3, SumsCount(3));
    ASSERT_EQ(89, SumsCount(10));
    ASSERT_EQ(10946, SumsCount(20));
    ASSERT_EQ(1346269, SumsCount(30));
    ASSERT_EQ(20365011074ll, SumsCount(50));
}

struct AvgGroupsData {
    std::string description;
    std::vector<double> expect;
    std::vector<int> ar;
    int m;
} avgsGroups[] =
{
    {
        "{ 1 2 3 4 5 6 7 } and m = 3",
        { 2.0, 3.0, 4.0, 5.0, 6.0 },
        { 1, 2, 3, 4, 5, 6, 7 },
        3
    }
};

struct AvgGroupsTest : ::testing::TestWithParam<AvgGroupsData> {};

TEST_P(AvgGroupsTest, AvgGroups) {
    const auto& param = GetParam();
    auto res = AvgGroups(param.ar, param.m);
    ASSERT_EQ(param.expect.size(), res.size()) << param.description;
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(param.expect[i], res[i], 0.00001) << param.description;
    }
}

INSTANTIATE_TEST_CASE_P(Instantiation, AvgGroupsTest, ::testing::ValuesIn(avgsGroups),);

