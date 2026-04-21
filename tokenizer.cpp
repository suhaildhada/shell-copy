//
// Created by Suhail on 21-04-2026.
//

#include "tokenizer.h"

#include "utils.h"


namespace tokenizer {
    void insert_token(std::vector<std::string> &tokens, std::string &token) {
        if (!token.empty()) {
            tokens.push_back(token);
            token.clear();
        }
    }

    std::vector<std::string> tokenize(const std::string &user_input) {
        std::vector<std::string> tokens;

        const size_t n = user_input.size();

        if (n == 0) {
            return tokens;
        }

        bool inside_double_quotes = false;
        bool inside_single_quotes = false;
        bool next_character_escaped = false;

        std::string token;

        for (int i = 0; i < n; i++) {
            const char c = user_input[i];
            if (c == ESCAPE_CHAR && !next_character_escaped) {
                next_character_escaped = true;

                if (i + 1 < n) {
                    const char next_char = user_input[i + 1];
                    if (isspace(next_char)) {
                        next_character_escaped = false;
                        token.push_back(c);
                    }
                }
            } else if (c == DOUBLE_QUOTES_CHAR && !inside_single_quotes && !next_character_escaped) {
                inside_double_quotes = !inside_double_quotes;
                if (!inside_double_quotes) {
                    insert_token(tokens, token);
                }
            } else if (c == SINGLE_QUOTES_CHAR && !inside_double_quotes && !next_character_escaped) {
                inside_single_quotes = !inside_single_quotes;
                if (!inside_single_quotes) {
                    insert_token(tokens, token);
                }
            } else if (!inside_double_quotes && !inside_single_quotes && isspace(c)) {
                insert_token(tokens, token);
            } else {
                token.push_back(c);
                if (next_character_escaped) {
                    next_character_escaped = false;
                }
            }
        }
        insert_token(tokens, token);
        return tokens;
    }
}
