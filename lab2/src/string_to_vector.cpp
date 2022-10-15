#include "string_to_vector.h"


std::vector<float> StringToVectorFloats(std::string const& stringNumbers, char separator) {
    std::vector<float> results;
    auto start = stringNumbers.begin();
    auto end = stringNumbers.end();
    auto next = std::find(start, end, separator);
    while (next != end) {
        results.push_back(stof(std::string(start, next)));
        start = next + 1;
        next = std::find(start, end, separator);
    }
    results.push_back(stof(std::string(start, next)));
    return results;
}