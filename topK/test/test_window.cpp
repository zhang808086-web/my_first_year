# include <iostream>
# include <vector>
# include <string>

# include "counter/WordCounter.hpp"
# include "common/Type.hpp"

int main()
{
    WordCounter counter(10); // 10秒窗口

    counter.addWord({"hello", "world"}, 1); // 时间戳1秒
    counter.addWord({"hello", "cpp"}, 20);   // 时间戳20秒


    const auto& freqMap = counter.getWordFreq();

    if(freqMap.count("world") == 0){
        std::cout << "'world' correctly evicted from the window." << std::endl;
    } else {
        std::cout << "Error: 'world' should have been evicted." << std::endl;
    }

    if(freqMap.count("hello") == 1 && freqMap.at("hello") == 1){
        std::cout << "'hello' frequency is correct: " << freqMap.at("hello") << std::endl;
    } else {
        std::cout << "Error: 'hello' frequency is incorrect." << std::endl;
    }
    
    std::cout << "Current word frequencies in the window:" << std::endl;
    return 0;
}