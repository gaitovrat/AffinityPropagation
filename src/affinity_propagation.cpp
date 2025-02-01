#include "affinity_propagation.h"
#include "types.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

static constexpr uint64_t MAX_ITER = 100;

double AffinityPropagation::similarity(const std::vector<uint64_t> &a,
                                       const std::vector<uint64_t> &b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); ++i)
        sum += (a[i] - b[i]) * (a[i] - b[i]);

    return -sum;
}

double AffinityPropagation::median(std::vector<double> &v) {
    size_t n = v.size();
    std::sort(v.begin(), v.end());

    return (n % 2 == 0) ? (v[n / 2 - 1] + v[n / 2]) / 2.0 : v[n / 2];
}

AffinityPropagation::AffinityPropagation() : AffinityPropagation(Matrix()) {}

AffinityPropagation::AffinityPropagation(const Matrix &data)
    : S(data.size(), std::vector<double>(data.size())),
      R(data.size(), std::vector<double>(data.size())),
      A(data.size(), std::vector<double>(data.size())) {
    size_t n = data.size();
    std::vector<double> similarities(n * (n - 1));

    if (n < 1) return;

    std::cout << "Creating similarities matrix\n";

#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            S[i][j] = similarity(data[i], data[j]);

            if (i != j) {
                size_t index = i * (n - 1) + (j < i ? j : j - 1);
                similarities[index] = S[i][j];
            }
        }
    }

    double pref = median(similarities);
#pragma omp parallel for
    for (int i = 0; i < n; ++i)
        S[i][i] = pref;
}

void AffinityPropagation::train() {
    int n = S.size();

    for (int iter = 0; iter < MAX_ITER; iter++) {
        std::cout << "Processing iter " << iter << " from " << MAX_ITER << '\n';
#pragma omp parallel for collapse(2)
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                double max_val = -INFINITY;
                for (int kp = 0; kp < n; kp++) {
                    if (kp != k) {
                        max_val = std::max(max_val, A[i][kp] + S[i][kp]);
                    }
                }
                R[i][k] = S[i][k] - max_val;
            }
        }

#pragma omp parallel for
        for (int k = 0; k < n; k++) {
            double sum_positive = 0.0;
            for (int ip = 0; ip < n; ip++) {
                if (ip != k) sum_positive += std::max(0.0, R[ip][k]);
            }

            for (int i = 0; i < n; i++) {
                if (i == k) {
                    A[i][k] = sum_positive;
                } else {
                    A[i][k] = std::min(0.0, R[k][k] + sum_positive - std::max(0.0, R[i][k]));
                }
            }
        }
    }
}

std::vector<uint64_t> AffinityPropagation::predict() {
    int n = R.size();
    std::vector<uint64_t> labels(n);

#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int exemplar = 0;
        double max_val = std::numeric_limits<double>::min();
        for (int k = 0; k < n; k++) {
            double val = R[i][k] + A[i][k];
            if (val > max_val) {
                max_val = val;
                exemplar = k;
            }
        }
        labels[i] = exemplar;
    }

    return labels;
}
