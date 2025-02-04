#include "linecount.h"
#include <fstream>

LineCount::LineCount(const std::string& filename) : filename(filename) {}

int LineCount::countLines() const {
    std::ifstream file(filename);
    if (!file.is_open()) return -1;

    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        ++count;
    }
    return count;
}
