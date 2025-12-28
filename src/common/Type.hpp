# pragma once
# include <vector>
# include <string>
# include <unordered_map>
#include <deque>
#include <utility>
#include <ctime>

namespace types{
    using Timestamp = std::time_t;

    using Word = std::string;

    using Tokens = std::vector<std::string>;

    using WordFreqMap = std::unordered_map<Word,int>;

    using WordCount = std::pair<Word, int>;
    using TopKResult = std::vector<WordCount>;

    struct windowItem{
        Timestamp timestamp;
        WordFreqMap delta;

        windowItem(Timestamp ts,const WordFreqMap &d)
            : timestamp(ts),delta(d) {}
    };

    using windowDeque = std::deque<windowItem>;
};