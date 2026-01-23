# ifndef    TOKENIZER_HPP
# define    TOKENIZER_HPP

# include "common/Type.hpp"
# include <vector>
# include <string>

class Tokenizer {
    public:
        virtual types::Tokens
        tokenize(const types::Word &text) = 0;
        virtual ~Tokenizer(){} 

};

# endif // TOKENIZER_HPP