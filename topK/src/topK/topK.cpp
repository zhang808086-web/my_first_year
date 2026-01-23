#include "topK.hpp"
# include "common/Type.hpp"
#include <queue>
#include <algorithm>

topKTracker::topKTracker(size_t K)
    : K_(K) {}

void topKTracker::update(const types::Word& word, int freq) {
    // 更新词频
    if(K_ == 0) return;

    if(inHeap_.count(word))
    {
        minHeap_.push({freq, word});
        return;
    }

    if(minHeap_.size() < K_)
    {
        minHeap_.push({freq, word});
        inHeap_.insert(word);
    }
    else if(freq > minHeap_.top().first)
    {
        //弹出堆顶
        inHeap_.erase(minHeap_.top().second);
        minHeap_.pop();

        //加入新元素
        minHeap_.push({freq, word});
        inHeap_.insert(word);
    }
}

types::TopKResult
topKTracker::getTopK(const types::WordFreqMap& wordFreq,size_t K) const {

    types::TopKResult result;
    if(K == 0 || wordFreq.empty()) return result;

    using Item = std::pair<int,types::Word>;
    auto cmp = [](const Item &a,const Item &b){
        return a.first > b.first; //大顶堆
    };

    std::priority_queue<Item,std::vector<Item>,decltype(cmp)> heap(cmp);

    for(const auto& [word,freq] : wordFreq){
        heap.emplace(freq,word);
        if(heap.size() > K){
            heap.pop();
        }
    }

    while(!heap.empty()){
        result.push_back({heap.top().second,heap.top().first});
        heap.pop();
    }

    std::reverse(result.begin(),result.end());
    return result;
}



