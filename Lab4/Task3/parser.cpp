#include "parser.h"
#include <algorithm>
#include <iostream>

void parser::variablesSearch() {
    for (const auto &i: input) {
        std::string typeRegex;
        typeRegex = R"(((const\s)?()" + typesToLine() + R"()\**(<.*>)*\s+(\**\s*\w+(\s=\s[-+]?(?:\d+|\d*.\d+)(?:[eE][-+]?\d+)?\b)*(,*\s*))*(;)))";
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(i, typeRes, r))
            variables.emplace_back(typeRes[0]);
    }
}

void parser::typesSearch() {
    for (const auto &i: input) {
        std::string src(R"((class|struct)\.*\s+(\w+))");
        std::regex r(src);
        std::smatch res;
        if (std::regex_search(i, res, r)) {
            types.insert(res[2]);
        }
    }
}

void parser::arraysSearch() {
    for (const auto &i: input) {
        std::string typeRegex;
        typeRegex = "((" + typesToLine() + R"(\**)\s*(\w+\[\d+\]+)\s*((\{(.)*\})*)(;)))";
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(i, typeRes, r)) {
            arrays.emplace_back(typeRes[0]);
        }
    }
}

parser::parser(const std::vector<std::string> &input) {
    this->input = input;
    typesSearch();
    variablesSearch();
    arraysSearch();
    prototypesSearch();
}

void parser::prototypesSearch() {
    for (const auto &i: input) {
        std::string typeRegex;
        std::string typeLine = typesToLine();
        typeRegex = "(const\\s)?(" + typeLine + R"()&*\.*\s*&*\.*(\w+)(\s*)(\(((const\s)?()" + typeLine + R"()(&*\.*\s*&*\.*\w*)(\s=\s[-+]?(?:\d+|\d*.\d+)(?:[eE][-+]?\d+)?\b)*,*\s*)*\)))";
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(i, typeRes, r)) {
            prototypes.emplace_back(std::make_pair(typeRes[0], typeRes[3]), coordinates(typeRes[0]));
        }
    }
}

std::string parser::typesToLine() {
    std::string typesLine;
    auto it = types.begin();
    for (size_t i = 0; i < types.size(); ++i) {
        typesLine += *it++;
        if (i != types.size() - 1)
            typesLine.push_back('|');
    }
    return typesLine;
}

std::set<std::string> parser::get_types() {
    return types;
}
std::pair<size_t, size_t> parser::coordinates(const std::string &match) {
    size_t row = -1;
    size_t col = -1;
    std::string correctMatch(match);
    for (size_t i = 0; i < correctMatch.size(); ++i) {
        if (correctMatch[i] == '*' || correctMatch[i] == '(' || correctMatch[i] == ')') {
            correctMatch.insert(i, R"(\)");
            i++;
        }
    }
    std::regex r(correctMatch);
    std::smatch res;
    bool exit = false;
    for (size_t i = 0; i < input.size() && !exit; ++i) {
        if (std::regex_search(input[i], res, r)) {
            for (size_t j = 0; j <= input[i].size() - res[0].length() && !exit; ++j) {
                if (input[i].substr(j, res[0].length()) == res[0]) {
                    col = j + 1;
                    row = i + 1;
                    exit = true;
                }
            }
        }
    }
    return {row, col};
}

bool IsUnique(const std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>> &vec, size_t ind) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i == ind)
            continue;
        if (vec[i].first.second == vec[ind].first.second) {
            return false;
        }
    }
    return true;
}

bool IsChecked(const std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>> &vec, size_t ind) {
    for (size_t i = 0; i < ind; ++i) {
        if (vec[i].first.second == vec[ind].first.second) {
            return true;
        }
    }
    return false;
}

std::pair<std::vector<std::pair<size_t, size_t>>, size_t> parser::overloadedFuncCount() {
    size_t count = 0;
    std::pair<std::vector<std::pair<size_t, size_t>>, size_t> crd;
    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (!IsChecked(prototypes, i) && !IsUnique(prototypes, i)) {
            count++;
        }
    }
    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (!IsUnique(prototypes, i)) {
            crd.first.emplace_back(prototypes[i].second.first, prototypes[i].second.second);
        }
    }
    crd.second = count;
    return crd;
}

std::vector<std::string> parser::get_variables() const {
    return variables;
}

std::vector<std::string> parser::get_arrays() const {
    return arrays;
}

const std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>>& parser::get_prototypes() const {
    return prototypes;
}
