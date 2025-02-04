#include "lettercount.h"
#include <fstream>
#include <cctype>

LetterCount::LetterCount(const std::string& filename) : filename(filename) {}

int LetterCount::countLetters() const {
    std::ifstream file(filename);
    if (!file.is_open()) return -1;

    char ch;
    int count = 0;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            ++count;
        }
    }
    return count;
}