#include "member.h"

Member::Member()
{

}

std::string Member::get_country() const {
    return country;
}

std::string Member::get_team() const {
    return team;
}

std::string Member::get_name() const {
    return name;
}

int Member::get_number() const {
    return number;
}

int Member::get_age() const {
    return age;
}

int Member::get_height() const {
    return height;
}

double Member::get_weight() const {
    return weight;
}

void Member::set_country(const std::string& country) {
    for (int i = 0; i < country.length(); ++i)
        if (!isalpha(country[i]) && country[i] != ' ')
            throw "Invalid country";
    this->country = country;
}

void Member::set_team(const std::string& team) {
    this->team = team;
}

void Member::set_name(const std::string& name) {
    for (int i = 0; i < name.length(); ++i)
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '\'')
            throw "Invalid name";
    this->name = name;
}

void Member::set_number(int number) {
    if (!number)
        throw "Invalid number";
    this->number = number;
}

void Member::set_age(int age) {
    if (!age)
        throw "Invalid age";
    this->age = age;
}

void Member::set_height(int height) {
    if (!height)
        throw "Invalid height";
    this->height = height;
}

void Member::set_weight(double weight) {
    if (!weight)
        throw "Invalid weight";
    this->weight = weight;
}

Member& Member::operator=(const Member& other) {
    country = other.country;
    team = other.team;
    name = other.name;
    number = other.number;
    age = other.age;
    height = other.height;
    weight = other.weight;
    return *this;
}
