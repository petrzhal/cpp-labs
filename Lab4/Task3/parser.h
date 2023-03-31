#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <regex>

class parser {
private:
    std::vector<std::string> input;
    std::vector<std::string> types {
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
    explicit parser(const std::vector<std::string>&);
    std::vector<std::smatch> variablesSearch();
    void typesSearch();
    std::vector<std::smatch> arraysSearch();
    std::vector<std::smatch> prototypesSearch();
    std::string typesToLine();
};

#endif//PARSER_PARSER_H
