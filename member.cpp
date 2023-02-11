#include "member.h"

Member::Member()
{

}

std::string Member::get_country() {
    return country;
}

std::string Member::get_team() {
    return team;
}

std::string Member::get_name() {
    return name;
}

int Member::get_number() {
    return number;
}

int Member::get_age() {
    return age;
}

int Member::get_heigth() {
    return height;
}

void Member::set_country(const std::string& country) {
    this->country = country;
}

void Member::set_team(const std::string& team) {
    this->team = team;
}

void Member::set_name(const std::string& name) {
    this->name = name;
}

void Member::set_number(int number) {
    this->number = number;
}

void Member::set_age(int age) {
    this->age = age;
}

void Member::set_heigth(int height) {
    this->height = height;
}

void Member::set_weigth(int weight) {
    this->weigth = weight;
}
