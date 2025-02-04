#include <iostream>
#include "lettercount.h"
#include "wordcount.h"
#include "linecount.h"

int main() {
    std::string filename = "sample.txt";

    LetterCount letterCounter(filename);
    WordCount wordCounter(filename);
    LineCount lineCounter(filename);

    std::cout << "Letters: " << letterCounter.countLetters() << std::endl;
    std::cout << "Words: " << wordCounter.countWords() << std::endl;
    std::cout << "Lines: " << lineCounter.countLines() << std::endl;

    return 0;
}
