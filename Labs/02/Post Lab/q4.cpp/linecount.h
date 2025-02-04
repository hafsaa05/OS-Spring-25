#ifndef LINECOUNT_H
#define LINECOUNT_H

#include <string>

class LineCount {
public:
    LineCount(const std::string& filename);
    int countLines() const;

private:
    std::string filename;
};

#endif