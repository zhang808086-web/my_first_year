# pragma once
#include <fstream>
#include <string>
# include <stdexcept>
# include <sstream>

# include "common/Type.hpp"


class ioReader{
    public:
        explicit ioReader(const std::string& filename);

        ~ioReader();

        bool next(types::Timestamp& ts,std::string& content);

        private:
            std::ifstream ifs;
};



