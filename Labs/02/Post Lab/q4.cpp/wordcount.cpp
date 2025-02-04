#include "wordcount.h"
#include <fstream>
#include <sstream>

WordCount::WordCount(const std::string& filename) : filename(filename) {}

int WordCount::countWords() const {
    std::ifstream file(filename);
    if (!file.is_open()) return -1;

    std::string word;
    int count = 0;
    while (file >> word) {
        ++count;
    }
    return count;
}