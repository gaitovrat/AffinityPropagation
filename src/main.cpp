#include "affinity_propagation.h"
#include "utils.h"
#include <iostream>

int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cerr << "Filename missing.\n";
        return 1;
    }

    auto result = utils::readCSV(argv[1]);
    if (!result.has_value()) {
        std::cerr << "Incorrect filename or empty file\n";
        return 1;
    }

    AffinityPropagation affinityPropagation(*result);
    affinityPropagation.train();
    auto results = affinityPropagation.predict();

    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "Bod " << i << " patří do shluku reprezentovaného bodem " << results[i]
                  << std::endl;

        return 0;
    }
}
