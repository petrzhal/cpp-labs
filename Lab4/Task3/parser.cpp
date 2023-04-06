#include "parser.h"
#include <algorithm>
#include <iostream>
#include <thread>
#include <QDebug>

void parser::variablesSearch() {
    for (size_t i = 0; i < input.size(); ++i) {
        std::string typeRegex;
        typeRegex = (R"(((const\s)?()" + typesToLine() + R"()\**(<.*>)*\s+(\**\s*\w+(\s=\s[-+]?(?:\d+|\d*.\d+)(?:[eE][-+]?\d+)?\b)*(,*\s*))*(;)))");
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(input[i], typeRes, r))
            variables.emplace_back(typeRes[0], coordinates(typeRes[0], i));
    }
}

void parser::classesSearch() {
    for (const auto &i: input) {
        std::string src(R"((class|struct)\s+(\w+)\s*\{)");
        std::regex r(src);
        std::smatch res;
        if (std::regex_search(i, res, r)) {
            types.insert(res[2]);
            if (res[1] == "class")
                classes.emplace_back(res[2]);
            else if (res[1] == "struct")
                structs.emplace_back(res[2]);
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
    std::thread t1(&parser::classesSearch, this);
    std::thread t2(&parser::variablesSearch, this);
    std::thread t3(&parser::arraysSearch, this);
    std::thread t4(&parser::prototypesSearch, this);
    branchLevel.resize(input.size() + 1);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void parser::prototypesSearch() {
    for (size_t i = 0; i < input.size(); ++i) {
        std::string typeRegex;
        std::string typeLine = typesToLine();
        typeRegex = "(const\\s)?(" + typeLine + R"()&*\s*&*(\w+\:\:)*(\w+)(\s*)(\(((const\s)?()" + typeLine + R"()(&*\.*\s*&*\.*\w*)(\s=\s[-+]?(?:\d+|\d*.\d+)(?:[eE][-+]?\d+)?\b)*,*\s*)*\)))";
        std::regex r(typeRegex);
        std::smatch typeRes;
        if (std::regex_search(input[i], typeRes, r)) {
            prototypes.emplace_back(std::make_pair(typeRes[0], typeRes[4]), coordinates(typeRes[0], i));
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

std::vector<std::pair<std::string, std::pair<size_t, size_t>>> parser::logicErrors()
{
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> errors;
    for (size_t i = 0; i < input.size(); ++i) {
        std::string reg(R"(((while|if|else if)\s*\((true|false)\))|(for\s+\(\s*((\w+\s+)*\w+(\s=\s.+)*)*;\s*;.*\)))");
        std::regex r(reg);
        std::smatch res;
        if (std::regex_search(input[i], res, r)) {
            errors.emplace_back(res[0], coordinates(res[0], i));
        }
    }
    return errors;
}

std::vector<std::pair<std::string, std::pair<size_t, size_t>>> parser::variablesChanges()
{
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> changes;
    for (size_t i = 0; i < input.size(); ++i) {
        std::string reg(R"(((\+\+|--)\w+)|(\w+(\+\+|--))|(\w+\s(=|\+=|-=)\s*([^\s\)])+\s*;))");
        std::regex r(reg);
        std::smatch res;
        if (std::regex_search(input[i], res, r)) {
            changes.emplace_back(res[0], coordinates(res[0], i));
        }
    }
    return changes;
}

std::set<std::string> parser::get_types() {
    return types;
}

std::vector<std::string> parser::get_classes()
{
    return classes;
}

std::vector<std::string> parser::get_structs()
{
    return structs;
}

std::pair<size_t, size_t> parser::coordinates(const std::string &match, size_t ind) {
    size_t row = ind + 1;
    size_t col = input[ind].find(match) + 1;
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

std::pair<std::vector<std::pair<std::string, std::pair<size_t, size_t>>>, size_t> parser::overloadedFuncCount() {
    size_t count = 0;
    std::pair<std::vector<std::pair<std::string, std::pair<size_t, size_t>>>, size_t> crd;
    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (!IsChecked(prototypes, i) && !IsUnique(prototypes, i)) {
            count++;
        }
    }
    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (!IsUnique(prototypes, i)) {
            crd.first.emplace_back(prototypes[i].first.first, std::make_pair(prototypes[i].second.first, prototypes[i].second.second));
        }
    }
    crd.second = count;
    return crd;
}

void parser::countBranсh(size_t i)
{
    std::string reg(R"(((while|if|else if|else)\s?\(.+\)\s*\{)|(for\s?\(.+\)\s*\{))");
    std::regex r(reg);
    std::smatch res;
    if (std::regex_search(input[i], res, r)) {
        branchLevel[i]++;
        size_t j = i + 1;
        while (coordinates("}", j).second != coordinates(res[0], i).second && j < input.size() - 1) {
            countBranсh(j);
            ++j;
        }
    }
}

void parser::findBranches()
{
    for (size_t i = 0; i < input.size(); ++i) {
        countBranсh(i);
    }
}

std::vector<int> parser::get_branchesCount()
{
    return branchLevel;
}

std::vector<std::pair<std::string, std::pair<size_t, size_t>>> parser::get_variables() const {
    return variables;
}

std::vector<std::string> parser::get_arrays() const {
    return arrays;
}

const std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>> &parser::get_prototypes() const {
    return prototypes;
}
