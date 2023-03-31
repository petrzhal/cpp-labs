#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <regex>
#include <set>

class parser {
private:
    std::vector<std::string> input;
    std::set<std::string> types {
            "void",
            "bool",
            "char",
            "unsigned char",
            "short",
            "int",
            "long long",
            "unsigned short",
            "unsigned int",
            "unsigned long",
            "unsigned long long",
            "size_t",
            "float",
            "double"
    };
public:
    std::set<std::string> get_types();
    explicit parser(const std::vector<std::string>&);
    std::vector<std::smatch> variablesSearch();
    void typesSearch();
    std::vector<std::smatch> arraysSearch();
    std::vector<std::smatch> prototypesSearch();
    std::string typesToLine();
};

#endif//PARSER_PARSER_H
