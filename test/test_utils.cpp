#include <gtest/gtest.h>

#include <utils.h>

TEST(UtilsReadCSV, Incorrect) {
    auto result = utils::readCSV("incorrect/filename");
    EXPECT_FALSE(result.has_value());
}

TEST(UtilsReadCSV, Correct) {
    auto result = utils::readCSV("test/mnist_test.csv");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 10000);
    EXPECT_EQ(result->at(0).size(), 785);
}
