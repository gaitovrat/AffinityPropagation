#ifndef __AFFINITY_PROPAGATION_H__
#define __AFFINITY_PROPAGATION_H__

#include <cstdint>
#include <vector>

#include "types.h"

class AffinityPropagation {
  public:
    /**
     * @brief Construct a new Affinity Propagation object
     *
     * @param data
     */
    AffinityPropagation(const Matrix &data);

    /**
     * @brief Construct a new Affinity Propagation object
     *
     */
    AffinityPropagation();

    /**
     * @brief Destroy the Affinity Propagation object
     *
     */
    virtual ~AffinityPropagation() = default;

    /**
     * @brief Calculate R and A matrixes
     *
     */
    void train();

    /**
     * @brief Get labels from R and A matrixes
     *
     * @return std::vector<uint64_t>
     */
    std::vector<uint64_t> predict();

  private:
    /**
     * @brief Similarity between a and b
     *
     * @param a vector
     * @param b vector
     * @return double
     */
    static double similarity(const std::vector<uint64_t> &a, const std::vector<uint64_t> &b);

    /**
     * @brief Median
     *
     * @param v vector
     * @return double value
     */
    static double median(std::vector<double> &v);

    FMatrix S;
    FMatrix R;
    FMatrix A;
};

#endif // __AFFINITY_PROPAGATION_H__
