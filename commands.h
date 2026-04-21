//
// Created by Suhail on 21-04-2026.
//

#ifndef SHELL_COPY_ECHO_COMMAND_H
#define SHELL_COPY_ECHO_COMMAND_H
#include <string>
#include <unordered_set>
#include <vector>

#define ECHO_COMMAND "echo"
#define TYPE_COMMAND "type"
#define PWD_COMMAND  "pwd"
#define CD_COMMAND   "cd"

namespace command {
    inline std::unordered_set<std::string> inbuilt_commands = {ECHO_COMMAND, TYPE_COMMAND, PWD_COMMAND, CD_COMMAND};

    void execute_echo(std::vector<std::string> tokens);

    void execute_type(const std::vector<std::string> &tokens);

    void execute_pwd();
 void execute_cd(const std::vector<std::string> &tokens);

    void execute(const std::string &command, const std::vector<std::string> &tokens);
}

#endif //SHELL_COPY_ECHO_COMMAND_H
