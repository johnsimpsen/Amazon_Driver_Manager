//
// Created by john simpsen on 9/10/2024.
//
#ifndef DRIVER_H
#define DRIVER_H

#include <iomanip>
#include <iostream>
#include <string>

class Driver {
private:
    std::string name;
    double area;

public:
    static std::string comparison;

    //Constructors
    Driver();
    Driver(const std::string &n, double a);

    //Accessors (const used so they can't modify the object the function was called by)
    std::string getName() const {return name;}
    double getArea() const {return area;}
    std::string getComparison() const;

    //Mutators
    void setName(const std::string &n) {name = n;}
    void setArea(const double a) {area = a;}

    static void setComparison(const std::string c) {comparison = c;}

    friend std::ostream& operator<<(std::ostream& out, const Driver& d);
    friend bool operator>(const Driver& lhs, const Driver& rhs);
    friend bool operator<(const Driver& lhs, const Driver& rhs);
};

#endif //DRIVER_H
