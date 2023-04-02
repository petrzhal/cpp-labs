#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <regex>
#include <set>

class parser {
private:
    std::vector<std::string> input;
    std::vector<std::string> variables;
    std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>> prototypes;
    std::vector<std::string> arrays;
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
    explicit parser(const std::vector<std::string>&);
    void variablesSearch();
    void typesSearch();
    void arraysSearch();
    void prototypesSearch();
    std::string typesToLine();
    std::pair<size_t, size_t> coordinates(const std::string&);
    std::pair<std::vector<std::pair<size_t, size_t>>, size_t> overloadedFuncCount();
    std::set<std::string> get_types();
    [[nodiscard]] std::vector<std::string> get_variables() const;
    [[nodiscard]] std::vector<std::string> get_arrays() const;
    [[nodiscard]] const std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>>& get_prototypes() const;
};

#endif//PARSER_PARSER_H
