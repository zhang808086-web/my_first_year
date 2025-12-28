# include <iostream>
# include <vector>
# include <string>

# include "topK/topK.hpp"
# include "common/Type.hpp"

int main()
{
    types::WordFreqMap freq = {
        {"A", 10},
        {"B", 5},
        {"C", 3},
        {"D", 1}
    };

    topKTracker tk(2);
    auto result = tk.getTopK(freq, 2);

    if (result.size() != 2) {
        std::cerr << "[FAIL] topK size incorrect\n";
        return 1;
    }

    if (result[0].first != "A" || result[0].second != 10) {
        std::cerr << "[FAIL] topK first element incorrect\n";
        return 1;
    }

    if (result[1].first != "B") {
        std::cerr << "[FAIL] topK second element incorrect\n";
        return 1;
    }

    std::cout << "[PASS] topK correctness test\n";
    return 0;
}