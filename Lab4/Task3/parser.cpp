#include "parser.h"
#include <iostream>

std::vector<std::smatch> parser::variablesSearch() {
    std::vector<std::smatch> res;
    for (const auto &i: input) {
        std::string typeRegex;
        typeRegex = "((" + typesToLine() + R"(\**)\s+(\w+(\s=\s[-+]?(?:\d+|\d*.\d+)(?:[eE][-+]?\d+)?\b)*(,*\s*))*(;)))";
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(i, typeRes, r))
            res.emplace_back(typeRes);
    }
    return res;
}

void parser::typesSearch() {
    for (const auto &i: input) {
        std::string src(R"((class|struct)\s+(\w+))");
        std::regex r(src);
        std::smatch res;
        if (std::regex_search(i, res, r)) {
            types.emplace_back(res[2]);
        }
    }
    arraysSearch();
}

std::vector<std::smatch> parser::arraysSearch() {
    std::vector<std::smatch> res;
    for (const auto &i: input) {
        std::string typeRegex;
        typeRegex = "((" + typesToLine() + R"(\**)\s*(\w+\[\d+\]+)\s*((\{(.)*\})*)(;)))";
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(i, typeRes, r)) {
            res.emplace_back(typeRes);
            std::cout << typeRes[0] << "\n";
        }
    }
    return res;
}

parser::parser(const std::vector<std::string> &input) {
    this->input = input;
}

std::vector<std::smatch> parser::prototypesSearch() {
    std::vector<std::smatch> res;
    for (const auto &i: input) {
        std::string typeRegex;
        std::string typeLine = typesToLine();
        typeRegex = "(" + typeLine + ")\\s+(\\w+\\s*)(\\(((" + typeLine + ")(\\s+\\w+)(\\s=\\s[-+]?(?:\\d+|\\d*.\\d+)(?:[eE][-+]?\\d+)?\\b)*,*\\s*)*\\))";
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(i, typeRes, r)) {
            res.emplace_back(typeRes);
        }
    }
    return res;
}

std::string parser::typesToLine() {
    std::string typesLine;
    for (size_t i = 0; i < types.size(); ++i) {
        typesLine += types[i];
        if (i != types.size() - 1)
            typesLine.push_back('|');
    }
    return typesLine;
}
