# pragma    once
# include <unordered_set>
# include "common/Type.hpp"
# include "Tokenizer.hpp"
# include "Jieba.hpp"

class JiebaTokenizer : public Tokenizer {
    public:
           JiebaTokenizer(const types::Word& dict_path,
                   const types::Word& hmm_path,
                   const types::Word& user_dict_path,
                   const types::Word& idf_path,
                   const types::Word& stop_word_path);
            types::Tokens

            tokenize(const types::Word &text) override;
            
    private:
            cppjieba::Jieba jieba_;
            std::unordered_set<std::string> stopWords_;
};
