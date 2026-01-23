#include "jiebaTokenizer.hpp"
# include "common/Type.hpp"
# include <cctype>

JiebaTokenizer::JiebaTokenizer(
    const types::Word& dict_path,
    const types::Word& hmm_path,
    const types::Word& user_dict_path,
    const types::Word& idf_path,
    const types::Word& stop_word_path)
    : jieba_(dict_path,
             hmm_path,
             user_dict_path,
             idf_path,
             stop_word_path){
    std::ifstream ifs(stop_word_path);
    std::string word;
    while (std::getline(ifs, word)) {
        if (!word.empty())
            stopWords_.insert(word);
    }
}





types::Tokens
JiebaTokenizer::tokenize(const types::Word& text) {
    types::Tokens result;
    std::vector<std::string> words;
    jieba_.Cut(text,words,true);

    for(const auto& w : words)
    {
        if(w.size() < 2) continue;

        bool allPunc = true;
        for(char c : w)
        {
            if(!std::ispunct(static_cast<unsigned char>(c))){
                allPunc = false;
                break;
            }
        }
        if(allPunc) continue;

        if(stopWords_.count(w)) continue;
        result.push_back(w);
    }
    return result;
}
