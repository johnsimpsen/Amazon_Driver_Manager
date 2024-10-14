//
// Created by john simpsen on 9/10/2024.
//
#include "Driver.h"

//Set comparison variable to default value
std::string Driver::comparison = "area";

//Constructors
Driver::Driver() {
    name = "";
    area = 0.0;
}

Driver::Driver(const std::string &n, double a) {
    name = n;
    area = a;
}

//Accessors
std::string getComparison() {
    return Driver::comparison;
}

//Overloaded operators
std::ostream& operator<<(std::ostream& out, const Driver& d) {
    out << std::fixed << std::setprecision(2) << d.getName() << "\t" << d.getArea();
    return out;
}

bool operator>(const Driver& lhs, const Driver& rhs) {
    if (Driver::comparison == "area") {
        return lhs.area > rhs.area;
    }
    else if (Driver::comparison == "driver") {
        return lhs.name > rhs.name;
    }
    //return false if comparison is neither area or driver
    return false;
}

bool operator<(const Driver& lhs, const Driver& rhs) {
    if (Driver::comparison == "area") {
        return lhs.area < rhs.area;
    }
    else if (Driver::comparison == "driver") {
        return lhs.name < rhs.name;
    }
    //return false if comparison is neither area or driver
    return false;
}

