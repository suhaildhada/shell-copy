#include <iostream>
#include <vector>
#include <filesystem>
#include "commands.h"
#include "tokenizer.h"


int main() {
    while (true) {
        std::cout << "> " << std::flush;
        std::string user_input;
        std::getline(std::cin, user_input);

        std::vector<std::string> tokens = tokenizer::tokenize(user_input);
        if (tokens.empty()) {
            continue;
        }

        std::string command = tokens[0];
        tokens.erase(tokens.begin());

        if (command == ECHO_COMMAND) {
            command::execute_echo(tokens);
        } else if (command == TYPE_COMMAND) {
            command::execute_type(tokens);
        } else if (command == PWD_COMMAND) {
            command::execute_pwd();
        } else if (command == CD_COMMAND) {
            command::execute_cd(tokens);
        } else {
            command::execute(command, tokens);
        }
    }
    return 0;
}
