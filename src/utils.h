#ifndef __UTILS_H__
#define __UTILS_H__

#include <cstdint>
#include <optional>
#include <string>

#include "types.h"

namespace utils {
std::optional<Matrix> readCSV(const std::string &filename);

/**
 * @brief read csv into a matrix
 *
 * @param filename filename
 * @return std::optional<Matrix> matrix
 */
std::optional<Matrix> readCSV(const std::string &filename, uint64_t maxSize);
} // namespace utils

#endif // __UTILS_H__
