# include "WordCounter.hpp"
# include "common/Type.hpp"
using namespace std;

WordCounter::WordCounter(types::Timestamp windowSeconds)
    : windowSeconds_(windowSeconds) {}

void WordCounter::addWord(const types::Tokens& words, types::Timestamp timestamp){
    types::WordFreqMap delta;
    for(const auto &word : words){
        ++wordFreq_[word];
        ++delta[word];
    }
    window_.push_back({timestamp, std::move(delta)});
    evictOldWords(timestamp);
}

void WordCounter::evictOldWords(types::Timestamp now){
    while(!window_.empty())
    {
        const auto& item = window_.front();
        //最早数据还在内，stop
        if(now - item.timestamp <= windowSeconds_){
            break;
        }

        //remove 最早数据
        for(const auto &[word,cnt] : item.delta){
            auto it = wordFreq_.find(word);
            if(it != wordFreq_.end()){
                it->second -= cnt;
                if(it->second <= 0){
                    wordFreq_.erase(it);
                }
            }
        }

     window_.pop_front();   
    }
}

const types::WordFreqMap& WordCounter::getWordFreq() const{
    return wordFreq_;
}