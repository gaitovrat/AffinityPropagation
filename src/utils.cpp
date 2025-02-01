#include "utils.h"

uint64_t utils::sum(const std::vector<uint32_t> &vec) {
    uint64_t result = 0;

#pragma omp parallel for reduction(+ : result)
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
    }

    return result;
}
