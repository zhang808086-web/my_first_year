#include <iostream>
#include <ctime>
# include <thread>
# include <chrono>
# include <fstream>

# include "common/Type.hpp"
# include "io/ioReader.hpp"
#include "Tokenizer/jiebaTokenizer.hpp"
#include "counter/WordCounter.hpp"
#include "topK/topK.hpp"

int main() {
        try {

        // 1️ 初始化分词器
        JiebaTokenizer tokenizer(
            "dict/jieba.dict.utf8",
            "dict/hmm_model.utf8",
            "dict/user.dict.utf8",
            "dict/idf.utf8",
            "dict/stop_words.utf8"
        );
        // 输出文件
        std::ofstream ofs("output.txt",std::ios::app);
        if(!ofs.is_open()){
            std::cerr << "Failed to open output file." << std::endl;
            return 1;
        }

        std::string input;

        while(true){
            std::cout << "Enter start time (in seconds) or 'q' to quit or 'c' to clear output: ";
            std::cin >> input;
            if(input == "q"){
                break;
            }

            if(input == "c" || input == "C") {
                std::ofstream ofs_clear("output.txt", std::ios::trunc);
                if(ofs_clear.is_open()) {
                    ofs_clear.close();
                    std::cout << "output.txt cleared." << std::endl;
                } else {
                    std::cerr << "Failed to clear output.txt" << std::endl;
                }
                continue; // 返回循环继续
            }

            // 读取时间范围和K值
            types::Timestamp startTime = std::stoul(input);
            std::cout << "Enter end time (in seconds): ";
            std::cin >> input;
            types::Timestamp endTime = std::stoul(input);

            std::cout << "Enter K for Top-K words: ";
            std::cin >> input;
            size_t K = std::stoul(input);

        // 2️ 初始化滑动窗口
        WordCounter counter(endTime - startTime+1);
        topKTracker tk(K);

        for(int i = 1;i <=3;++i)
        {
            ioReader reader("input" + std::to_string(i) + ".txt");

            types::Timestamp ts;
            std::string text;

            while(reader.next(ts,text))
            {   
                if(ts < startTime || ts > endTime)
                    continue;

                auto words = tokenizer.tokenize(text);
                //加入统计
                counter.addWord(words, ts);
            }
        }

        auto result = tk.getTopK(counter.getWordFreq(), K);

        ofs << "[Time " << startTime << "s ~ "<< endTime << "s] Top" << K << "\n";
        for(auto& [word,freq] : result)
        {
            ofs << word << " : " << freq << "\n";
        }

        ofs << "--------------------------\n";
        std::cout << "Done. Results written to topK/output.txt" << std::endl;
    }

    ofs.close();
    std::cout << "Program exited." << std::endl;




    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

