/**
 * @file main.cpp
 * @author Nicolas IRAGNE (nicolas.iragne@alyce.fr)
 * @brief
 * @date 2022-09-25
 *
 * @copyright Copyright Alyce (c) 2022
 */

#include "pipeline.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <type_traits>


using namespace niragne;

int main(int argc, char** argv)
{
    auto fileloader = Node<std::filesystem::path, std::string>([](std::filesystem::path path) {
        std::ifstream file(path);
        std::cout << "Loading file " << path << std::endl;
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return str;
    });
    auto inverter = Node<std::string, std::string>([](std::string str) {
        std::string inverted;
        for (auto it = str.rbegin(); it != str.rend(); ++it)
        {
            inverted.push_back(*it);
        }
        return inverted;
    });
    auto filewriter = Node<std::string, std::filesystem::path>([](std::string str) {
        std::filesystem::path path = "output.txt";
        std::ofstream file(path);
        std::cout << "Writing file " << path << std::endl;
        file << str;
        return path;
    });

    auto printer = Node<std::string, std::string>([](std::string str) {
        std::cout << str << std::endl;
        return str;
    });

    auto pipeline = fileloader >> printer >> inverter >> printer >> filewriter;
    pipeline.process("input.txt");
}
