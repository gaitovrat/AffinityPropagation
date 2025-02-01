#include "types.h"

#include <cstddef>
#include <gtest/gtest.h>

#include <affinity_propagation.h>
#include <utils.h>

class AffinityPropagationTest : public ::testing::Test {
  protected:
    AffinityPropagationTest() : affinityPropagation() {
        // Set max size to decrease waiting time
        auto result = utils::readCSV("test/mnist_test.csv", 1000);
        EXPECT_TRUE(result.has_value());

        data = *result;
        auto newData = data;

        // Delete label column
        for (auto &row : newData) {
            row.erase(row.begin());
        }

        affinityPropagation = AffinityPropagation(newData);
    }

    AffinityPropagation affinityPropagation;
    Matrix data;
};

TEST_F(AffinityPropagationTest, Clustering) {
    affinityPropagation.train();
    auto result = affinityPropagation.predict();
    size_t n = result.size();

    EXPECT_EQ(n, 1000);

    for (size_t i = 0; i < result.size(); i++) {
        std::cout << "Bod " << i << " patří do shluku reprezentovaného bodem " << result[i]
                  << std::endl;
    }
}
