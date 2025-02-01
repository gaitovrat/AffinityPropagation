#ifndef __AFFINITY_PROPAGATION_H__
#define __AFFINITY_PROPAGATION_H__

#include <cstdint>
#include <vector>

#include "types.h"

class AffinityPropagation {
  public:
    AffinityPropagation(const Matrix &data);

    AffinityPropagation();

    virtual ~AffinityPropagation() = default;

    void train();
    std::vector<uint64_t> predict();

  private:
    static double similarity(const std::vector<uint64_t> &a, const std::vector<uint64_t> &b);

    static double median(std::vector<double> &v);

    FMatrix S;
    FMatrix R;
    FMatrix A;
};

#endif // __AFFINITY_PROPAGATION_H__
