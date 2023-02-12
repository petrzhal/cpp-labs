#ifndef MEMBER_H
#define MEMBER_H
#include <string>

class Member
{
private:
    std::string country;
    std::string team;
    std::string name;
    int number;
    int age;
    int height;
    double weight;
public:
    Member();
    std::string get_country();
    std::string get_team();
    std::string get_name();
    int get_number();
    int get_age();
    int get_height();
    double get_weight();
    void set_country(const std::string&);
    void set_team(const std::string&);
    void set_name(const std::string&);
    void set_number(int);
    void set_age(int);
    void set_height(int);
    void set_weight(double);
    Member& operator=(const Member&);
};

#endif // MEMBER_H
