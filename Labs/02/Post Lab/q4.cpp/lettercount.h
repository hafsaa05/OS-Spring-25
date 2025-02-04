#ifndef LETTERCOUNT_H
#define LETTERCOUNT_H

#include <string>

class LetterCount
{
public:
    LetterCount(const std::string &filename);
    int countLetters() const;

private:
    std::string filename;
};

#endif