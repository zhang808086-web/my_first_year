# pragma once
# include <string>
# include <vector>
# include <deque>
# include <ctime>
# include <unordered_map>
# include "common/Type.hpp"

class WordCounter {
public:
    explicit WordCounter(types::Timestamp windowSeconds);

    void addWord(const types::Tokens& words,
                 types::Timestamp timestamp);

    const types::WordFreqMap& getWordFreq() const;

private:
    void evictOldWords(types::Timestamp now);

private:
    types::Timestamp windowSeconds_;
    types::windowDeque window_;
    types::WordFreqMap wordFreq_;
};