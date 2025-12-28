# pragma once
# include <vector>
# include <string>
# include <queue>
# include <unordered_set>
# include <utility>
# include "common/Type.hpp"

class topKTracker{
    public:
        explicit topKTracker(size_t K);

        void update(const types::Word& word,int freq);
        types::TopKResult getTopK(const types::WordFreqMap& wordFreq,size_t K) const;

private:
    size_t K_;
    using Node = std::pair<int,types::Word>;
    std::priority_queue<Node,std::vector<Node>,std::greater<Node>> minHeap_;
    std::unordered_set<types::Word> inHeap_;
};