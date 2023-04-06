#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

#include <regex>
#include <set>
#include <QString>

class parser {
private:
    std::vector<std::string> classes;
    std::vector<std::string> structs;
    std::vector<std::string> input;
    QString inputStr;
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> variables;
    std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>> prototypes;
    std::vector<std::string> arrays;
    std::set<std::string> types {
            "auto",
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
    std::vector<int> branchLevel;
    void variablesSearch();
    void classesSearch();
    void arraysSearch();
    void prototypesSearch();
    std::string typesToLine();
public:
    explicit parser(const std::vector<std::string>&);
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> logicErrors();
    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> variablesChanges();
    std::pair<size_t, size_t> coordinates(const std::string&, size_t);
    std::pair<std::vector<std::pair<std::string, std::pair<size_t, size_t>>>, size_t> overloadedFuncCount();
    void countBranсh(size_t);
    void findBranches();
    [[nodiscard]] std::vector<int> get_branchesCount();
    [[nodiscard]] std::set<std::string> get_types();
    [[nodiscard]] std::vector<std::string> get_classes();
    [[nodiscard]] std::vector<std::string> get_structs();
    [[nodiscard]] std::vector<std::pair<std::string, std::pair<size_t, size_t>>> get_variables() const;
    [[nodiscard]] std::vector<std::string> get_arrays() const;
    [[nodiscard]] const std::vector<std::pair<std::pair<std::string, std::string>, std::pair<size_t, size_t>>>& get_prototypes() const;
};

#endif//PARSER_PARSER_HPP
