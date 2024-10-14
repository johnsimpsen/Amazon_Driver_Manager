//
// Created by john simpsen on 9/10/2024.
//
#ifndef NODE_H
#define NODE_H
#include "Driver.h"

class Node {
private:
    Node* next;
    Driver driver;
public:
    //Constructors
    Node() {next = nullptr;};
    Node(Driver& d) {driver = d; next = nullptr;}

    //Accessors (const used so they can't modify the object the function was called by)
    Node* getNext() const {return next;}
    Driver getDriver() const {return driver;}

    //Mutators
    void setNext(Node* n) {next = n;}

    //Overloaded Operators
    friend std::ostream& operator<<(std::ostream& out, Node& n);
    friend bool operator>(Node& lhs, Node& rhs);
    friend bool operator<(Node& lhs, Node& rhs);
};

//Overloaded Operators
inline std::ostream& operator<<(std::ostream& out, Node& n){
    Driver d = n.getDriver();
    out << d;
    return out;
}


//Calls back to overloaded operators in Driver
inline bool operator>(Node& lhs, Node& rhs) {
    return lhs.getDriver() > rhs.getDriver();
}

//Calls back to overloaded operators in Driver
inline bool operator<(Node& lhs, Node& rhs) {
    return lhs.getDriver() < rhs.getDriver();
}

#endif //NODE_H
