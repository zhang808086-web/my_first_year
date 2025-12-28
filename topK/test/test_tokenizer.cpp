# include <iostream>
# include <vector>
# include <string>

# include "Tokenizer/jiebaTokenizer.hpp"
# include "common/Type.hpp"

int main(){
    // 初始化分词器
    JiebaTokenizer tokenizer(
        "dict/jieba.dict.utf8",
        "dict/hmm_model.utf8",
        "dict/user.dict.utf8",
        "dict/idf.utf8",
        "dict/stop_words.utf8"
    );

    // 测试用例
    std::vector<std::string> testSentences = {
        "我来到北京清华大学",
        "他来到了网易杭研大厦",
        "小明硕士毕业于中国科学院计算所，后在日本京都大学深造"
    };

    for(const auto& sentence : testSentences){
        types::Tokens tokens = tokenizer.tokenize(sentence);
        std::cout << "Original: " << sentence << std::endl;
        std::cout << "Tokens: ";
        for(const auto& token : tokens){
            std::cout << token << " | ";
        }
        std::cout << std::endl << "------------------------" << std::endl;
    }
}
