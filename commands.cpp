//
// Created by Suhail on 21-04-2026.
//

#include "commands.h"

#include <format>
#include <iostream>
#include <ostream>
#include <windows.h>

#include "utils.h"

namespace command {
    void execute(const std::string &command, const std::vector<std::string> &tokens) {
        const std::string command_path = utils::get_command_path_if_exists(command);

        if (command_path.empty()) {
            std::cerr << "invalid command: " << command << std::endl;
            return;
        }


        std::string command_line = utils::build_command_line(command_path, tokens);

        std::vector buffer(command_line.begin(), command_line.end());
        buffer.push_back('\0');


        STARTUPINFO startup_info{};
        startup_info.cb = sizeof(startup_info);

        PROCESS_INFORMATION process_info{};

        if (!CreateProcess(
            nullptr,
            buffer.data(),
            nullptr, nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &startup_info,
            &process_info

        )) {
            std::cerr << "CreateProcess Failed with following error: " << GetLastError() << std::endl;
            return;
        }


        WaitForSingleObject(process_info.hProcess, INFINITE);
        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);
    }

    void execute_type(const std::vector<std::string> &tokens) {
        if (tokens.size() != 1) {
            std::cerr << "type command only accepts 1 argument." << std::endl;
            std::cout << "   Usage: type <command name>" << std::endl;
            return;
        }

        const std::string &command = tokens[0];

        std::string output_builtin = std::format("{} is bash builtin", command);

        if (inbuilt_commands.contains(command)) {
            std::cout << output_builtin << std::endl;
            return;
        }

        std::string command_path = utils::get_command_path_if_exists(command);

        if (command_path.empty()) {
            std::cout << "invalid command: " << command << std::endl;
            return;
        }

        std::string output_command_in_path = std::format("{} is {}", command, command_path);
        std::cout << output_command_in_path << std::endl;
    }

    void execute_echo(std::vector<std::string> tokens) {
        utils::extract_flags(tokens);

        const size_t n = tokens.size();

        std::string message;
        for (size_t i = 0; i < n; i++) {
            message += tokens[i];
            if (i != n - 1) {
                message += " ";
            }
        }

        std::cout << message << std::endl;
    }

    void execute_pwd() {
        std::cout << std::filesystem::current_path() << std::endl;
    }

    void execute_cd(const std::vector<std::string> &tokens) {
        if (tokens.size() != 1) {
            std::cerr << "cd command only accepts 1 argument." << std::endl;
            std::cout << "   Usage: cd <directory>" << std::endl;
            return;
        }

        const std::string &location_path = tokens[0];
        if (location_path.empty()) {
            return;
        }

        try {
            std::filesystem::current_path(location_path);
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
