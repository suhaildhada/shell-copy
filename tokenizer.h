//
// Created by Suhail on 21-04-2026.
//

#ifndef SHELL_COPY_TOKENIZER_H
#define SHELL_COPY_TOKENIZER_H

#define ESCAPE_CHAR '\\'
#define DOUBLE_QUOTES_CHAR '"'
#define SINGLE_QUOTES_CHAR '\''

#include <string>
#include <vector>

namespace tokenizer {
    std::vector<std::string> tokenize(const std::string &user_input);
}

#endif //SHELL_COPY_TOKENIZER_H
