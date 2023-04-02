#include "parser.h"
#include <fstream>
#include <iostream>

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

    auto types = prs.get_types();
    std::cout << "Types:\n";
    for (const auto &type: types) {
        std::cout << type << "\n";
    }
    std::cout << "\nVariables:\n";
    auto res = prs.get_variables();
    for (auto &type: res) {
        auto coordinates = prs.coordinates(type);
        std::cout << type << " (" << coordinates.first << ", " << coordinates.second << ")\n";
    }
    std::cout << "\nArrays:\n";
    res = prs.get_arrays();
    for (auto &type: res) {
        std::cout << type << "\n";
    }
    std::cout << "\nFunction prototypes:\n";
    auto res2 = prs.get_prototypes();
    for (auto &type : res2) {
        std::cout << type.first.first << "\n";
    }
    auto pr = prs.overloadedFuncCount();
    std::cout << "\nOverloaded functions: " << pr.second << "\n";
    for (const auto& p : pr.first) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }
}
