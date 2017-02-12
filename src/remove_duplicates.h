
#pragma once

#include <algorithm>
#include <string>

inline void RemoveDuplicates(std::string& s) {
    bool isDuplicate[256] = { false };
    auto it = std::remove_if(s.begin(), s.end(), [&isDuplicate](unsigned char c) {
        if (isDuplicate[c]) {
            return true;
        }
        isDuplicate[c] = true;
        return false;
    });
    s.erase(it, s.end());
}

