#include <fstream>
#include <iostream>
#include "parser.h"

int main() {
    setlocale(0, "");
    std::vector<std::string> lines;

    std::fstream file;
    file.open("input.txt", std::ios::in);

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    parser prs(lines);

    prs.typesSearch();
    std::cout << "Переменные:\n";
    auto res = prs.variablesSearch();
    for (auto &type: res) {
        std::cout << type[0] << "\n";
    }
    std::cout << "\nМассивы:\n";
    res = prs.arraysSearch();
    for (auto &type: res) {
        std::cout << type[0] << "\n";
    }
    std::cout << "\nПрототипы функций:\n";
    res = prs.prototypesSearch();
    for (auto &type: res) {
        std::cout << type[0] << "\n";
    }
}
