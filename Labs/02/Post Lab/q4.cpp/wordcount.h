#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <string>

class WordCount {
public:
    WordCount(const std::string& filename);
    int countWords() const;

private:
    std::string filename;
};

#endif