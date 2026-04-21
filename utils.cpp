//
// Created by Suhail on 21-04-2026.
//

#include "utils.h"

#include <format>
#include <iostream>
#include <sstream>


namespace utils {
    std::string build_command_line(const std::string &command_path,
                                   const std::vector<std::string> &tokens) {
        std::string cmd = "\"" + command_path + "\"";

        for (const auto &token: tokens) {
            cmd += " ";

            if (token.find(' ') != std::string::npos) {
                cmd += "\"" + token + "\"";
            } else {
                cmd += token;
            }
        }
        return cmd;
    }

    std::string get_command_path_if_exists(const std::string &command) {
        std::vector<std::string> paths = get_env_var("PATH");
        for (const std::string &path: paths) {
            std::filesystem::path full_path = std::filesystem::path(path) / (command + EXE_EXECUTABLE);
            if (isExecutable(full_path)) {
                return full_path.string();
            }
        }
        return "";
    }

    bool isExecutable(const std::filesystem::path &path) {
        return std::filesystem::exists(path);
    }

    std::vector<std::string> get_env_var(const std::string &environment_variable) {
        // std::string log_message = std::format("Getting value for environment variable [{}].", environment_variable);
        // std::cout << log_message << std::endl;

        const char *path_val = std::getenv(environment_variable.c_str());


        if (path_val == nullptr) {
            // log_message = std::format("Environment variable [{}] not found.", environment_variable);
            // std::cout << log_message << std::endl;
        }

        const std::vector<std::string> paths = split_by_delimiter(path_val, ';');
        // log_message = std::format("Found [{}] elements for [{}] environment variable.", paths.size(),
        // environment_variable);
        // std::cout << log_message << std::endl;
        return paths;
    }

    void print_tokens(const std::vector<std::string> &tokens) {
        for (const std::string &token: tokens) {
            std::string log_message = std::format("Token = {}, Token Size = {}", token, token.size());
            std::cout << log_message << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<std::string> extract_flags(std::vector<std::string> &tokens) {
        std::vector<std::string> flags;

        for (auto it = tokens.begin(); it != tokens.end();) {
            const std::string &flag = *it;

            if (flag.starts_with("-") || flag.starts_with("--")) {
                flags.push_back(flag);
                tokens.erase(it);
            } else {
                break;
            }
        }
        return flags;
    }


    std::vector<std::string> split_by_delimiter(const char *val, char delimiter) {
        std::vector<std::string> result;

        if (val == nullptr) {
            return result;
        }

        std::stringstream ss(val);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            result.push_back(token);
        }
        return result;
    }
}
