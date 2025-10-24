#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <algorithm> // For std::transform

inline std::string normalize(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}
#endif