#include "utils.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

std::optional<Matrix> utils::readCSV(const std::string &filename) {
    return utils::readCSV(filename, std::numeric_limits<uint64_t>::max());
}

std::optional<Matrix> utils::readCSV(const std::string &filename, uint64_t maxSize) {
    Matrix out;
    std::ifstream fin(filename);
    std::string line;

    if (!fin.is_open()) return {};

    // SKip the header line
    if (!std::getline(fin, line)) return {};

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::vector<uint64_t> row;
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stoull(cell));
        }

        out.push_back(row);
        if (out.size() == maxSize) break;
    }

    return out;
}
