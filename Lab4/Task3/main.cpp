#include <fstream>
#include <iostream>
#include "parser.h"

int main() {
    setlocale(0, "");
    std::vector<std::string> lines;

    std::fstream file;
    file.open("input2.txt", std::ios::in);

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    parser prs(lines);
    prs.typesSearch();

    auto types = prs.get_types();
    std::cout << "Types:\n";
    for (const auto& type : types) {
        std::cout << type << "\n";
    }
    std::cout << "Variables:\n";
    auto res = prs.variablesSearch();
    for (auto &type: res) {
        std::cout << type[0] << "\n";
    }
    std::cout << "\nArrays:\n";
    res = prs.arraysSearch();
    for (auto &type: res) {
        std::cout << type[0] << "\n";
    }
    std::cout << "\nFunction prototypes:\n";
    res = prs.prototypesSearch();
    for (auto &type: res) {
        std::cout << type[0] << "\n";
    }
    system("pause");
}
