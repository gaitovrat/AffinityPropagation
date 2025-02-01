#include <gtest/gtest.h>

#include <utils.h>
#include <vector>

TEST(UtilsSum, Correct) {
    std::vector<uint32_t> vec = {1, 2, 3, 4, 5};
    uint64_t expected = 15;
    EXPECT_EQ(utils::sum(vec), expected);
}
