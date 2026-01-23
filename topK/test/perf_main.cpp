#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include "common/Type.hpp"
#include "Tokenizer/jiebaTokenizer.hpp"
#include "counter/WordCounter.hpp"
#include "topK/topK.hpp"

using Clock = std::chrono::high_resolution_clock;

/**
 * 模拟实时数据流：
 * - 从文件逐行读取
 * - 按给定速率注入系统
 */
int main() {
    try {
        /* ========= 可调测试参数 ========= */
        const std::string inputFile = "input1.txt";
        const size_t WINDOW_SIZE = 60;      // 滑动窗口（秒）
        const size_t TOP_K = 10;             // 查询 K
        const size_t INPUT_RATE = 500;      // 每秒多少条（负载）
        const size_t MAX_LINES = 1000;      // 最大处理条数
        /* ================================= */

        // 初始化分词器
        JiebaTokenizer tokenizer(
            "dict/jieba.dict.utf8",
            "dict/hmm_model.utf8",
            "dict/user.dict.utf8",
            "dict/idf.utf8",
            "dict/stop_words.utf8"
        );

        WordCounter counter(WINDOW_SIZE);

        std::ifstream ifs(inputFile);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open input file\n";
            return 1;
        }

        std::string line;
        size_t processed = 0;

        std::vector<long long> latency_us;
        latency_us.reserve(MAX_LINES);

        auto test_start = Clock::now();
        auto last_tick = Clock::now();

        while (processed < MAX_LINES && std::getline(ifs, line)) {
            auto one_start = Clock::now();

            // 直接模拟当前时间（秒级）
            types::Timestamp now =
                std::chrono::duration_cast<std::chrono::seconds>(
                    Clock::now().time_since_epoch()
                ).count();

            auto words = tokenizer.tokenize(line);
            counter.addWord(words, now);

            auto one_end = Clock::now();
            latency_us.push_back(
                std::chrono::duration_cast<std::chrono::microseconds>(
                    one_end - one_start
                ).count()
            );

            processed++;

            /* ====== 速率控制（模拟数据流） ====== */
            if (processed % INPUT_RATE == 0) {
                auto now_tick = Clock::now();
                auto elapsed =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        now_tick - last_tick
                    ).count();

                if (elapsed < 1000) {
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(1000 - elapsed)
                    );
                }
                last_tick = Clock::now();
            }
        }

        auto test_end = Clock::now();

        /* 性能统计 */
        auto total_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                test_end - test_start
            ).count();

        double throughput =
            processed / (total_ms / 1000.0);

        long long sum_latency = 0;
        for (auto v : latency_us) sum_latency += v;

        long long avg_latency =
            latency_us.empty() ? 0 : sum_latency / latency_us.size();

        std::cout << "=========== Performance Result ===========" << std::endl;
        std::cout << "Processed lines: " << processed << std::endl;
        std::cout << "Total time(ms): " << total_ms << std::endl;
        std::cout << "Throughput(lines/s): " << throughput << std::endl;
        std::cout << "Avg latency(us): " << avg_latency << std::endl;

        /* ========= Top-K 查询（只查一次） ========= */
        topKTracker tk(TOP_K);
        auto result = tk.getTopK(counter.getWordFreq(), TOP_K);

        std::cout << "=========== Top " << TOP_K << " ===========" << std::endl;
        for (auto& [w, f] : result) {
            std::cout << w << " : " << f << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

