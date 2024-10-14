//
// Created by john simpsen - jhs230005 on 9/10/2024.
//
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>


#include "Node.h"

class LinkedList {
private:
    Node* head;
    Node* tail;
public:
    //Constructors
    LinkedList();
    LinkedList(Node* h, Node* t);

    //Accessors
    Node* getHead() const {return head;}
    Node* getTail() const {return tail;}

    //Mutators
    void setHead(Node* n) {head = n;}
    void setTail(Node* n) {tail = n;}

    //Methods
    static void insert(LinkedList& list, Node* n);

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list);

    static void search(const std::string& s, const LinkedList& list);
    static void search(const double& a, const LinkedList& list);

    void sort();
};

#endif //LINKEDLIST_H
