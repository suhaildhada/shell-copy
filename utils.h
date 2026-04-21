//
// Created by Suhail on 21-04-2026.
//

#ifndef SHELL_COPY_UTILS_H
#define SHELL_COPY_UTILS_H
#include <filesystem>
#include <string>
#include <vector>


#define EXE_EXECUTABLE ".exe"

namespace utils {
    void print_tokens(const std::vector<std::string> &tokens);

    std::vector<std::string> extract_flags(std::vector<std::string> &tokens);

    std::vector<std::string> split_by_delimiter(const char *val, char delimiter);

    std::vector<std::string> get_env_var(const std::string &environment_variable);

    bool isExecutable(const std::filesystem::path &path);

    std::string get_command_path_if_exists(const std::string &command);

    std::string build_command_line(const std::string &command_path,
                                   const std::vector<std::string> &tokens);
}

#endif //SHELL_COPY_UTILS_H
