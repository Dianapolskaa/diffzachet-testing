#include "file.h"
#include <cctype>

namespace mylib {

int countWords(const std::string& s) {
    int count = 0;
    bool inWord = false;
    for (char c : s) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            inWord = false;
        } else {
            if (!inWord) {
                count++;
                inWord = true;
            }
        }
    }
    return count;
}

int countCharOccurrences(const std::string& s, char c) {
    int count = 0;
    for (char ch : s) {
        if (ch == c) count++;
    }
    return count;
}

char mostFrequentLetter(const std::string& s) {
    int freq[256] = {0};
    char mostFreq = '\0';
    int maxCount = 0;

    for (char c : s) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            unsigned char idx = static_cast<unsigned char>(c);
            freq[idx]++;
            if (freq[idx] > maxCount) {
                maxCount = freq[idx];
                mostFreq = c;
            }
        }
    }
    return mostFreq;
}

size_t longestStringLength(const std::vector<std::string>& arr) {
    size_t maxLen = 0;
    for (const auto& str : arr) {
        if (str.length() > maxLen) {
            maxLen = str.length();
        }
    }
    return maxLen;
}

} // namespace mylib