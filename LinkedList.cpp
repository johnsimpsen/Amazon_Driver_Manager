//
// Created by john simpsen on 9/10/2024.
//
#include "LinkedList.h"

//Constructors
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

LinkedList::LinkedList(Node* h, Node* t) {
    head = h;
    tail = t;
}

//Methods

//Inserts the passed in Node at the end of the list
void LinkedList::insert(LinkedList& list, Node* n) {
    if (list.getHead() == nullptr) {
        //Assigns both head and tail pointers to the address of the new node because the list was empty
        list.setHead(n);
        list.setTail(n);
    }
    else {
        //Assigns the previous tail to point to the inserted object then moves the tail pointer to the inserted object
        list.getTail()->setNext(n);
        list.setTail(n);
    }
}

//Overloaded operators
std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
    Node* curr = list.getHead();
    //For each node
    while (curr != nullptr) {
        // Use of Overloaded (<<) of the driver class
        out << *curr << std::endl;

        // Move the current place in the list to the address of the next node
        curr = curr->getNext();
    }
    return out;
}

//Search by name
void LinkedList::search(const std::string& s, const LinkedList& list) {
    Node* curr = list.getHead();
    bool found = false;
    //For each node
    while (curr != nullptr && !found) {
        //Found
        if (curr->getDriver().getName() == s) {
            std::cout << std::fixed << std::setprecision(2) << curr->getDriver().getName() << " " << curr->getDriver().getArea() << std::endl;
            found = true;
        }

        // Move the current place in the list to the address of the next node
        curr = curr->getNext();
    }
    //Not Found
    if (!found) {
        std::cout << s << " not found" << std::endl;
    }
}

//Search by area
void LinkedList::search(const double& a, const LinkedList& list) {
    Node* curr = list.getHead();
    bool found = false;
    //For each node
    while (curr != nullptr && !found) {

        //Truncate until two decimal places
        double num = floor(curr->getDriver().getArea()*100)/100.0;
        double num2 = floor(a*100)/100.0;


        //Found
        if (num == num2) {
            std::cout << std::fixed << std::setprecision(2) << curr->getDriver().getName() << " " << curr->getDriver().getArea() << std::endl;
            found = true;
        }

        // Move the current place in the list to the address of the next node
        curr = curr->getNext();
    }
    //Not found
    if (!found) {
        std::cout << a << " not found" << std::endl;
    }
}

//Sorts in ascending order by either name or area, depending on static var comparison (init and defined in driver)
void LinkedList::sort() {
    if (getHead() == nullptr || getHead()->getNext() == nullptr) {
        return;
    }

    bool sorted = false;
    Node* curr = getHead(); //current node
    Node* prev = nullptr; //previous node
    Node* temp = nullptr; //node after the current node

    //iterate through the list until sorted (no more swaps)
    while (!sorted) {
        sorted = true;
        curr = getHead();
        prev = nullptr;

        while (curr->getNext() != nullptr) {
            if (*curr > *curr->getNext()) {

                // Swap nodes
                temp = curr->getNext();
                curr->setNext(temp->getNext());
                temp->setNext(curr);

                //Set sorted to false if the algorithm had to swap something
                sorted = false;


                //check if the node before curr (prev) is null, curr is the head of the list if it is
                if (prev != nullptr) {
                    prev->setNext(temp);
                }
                //curr was the head of the list, so head must be updated after the swap
                else {
                    setHead(temp);
                }

                // Update prev to point to the temporary node pointer
                prev = temp;
            }
                else {

                // Move the previous and curr node pointers forward in the list
                prev = curr;
                curr = curr->getNext();
            }
        }
    }

    // Update the tail pointer by looping through the list until reaching the end and assigning that node to tail
    Node* tail = getHead();
    while (tail->getNext() != nullptr) {
        tail = tail->getNext();
    }
    setTail(tail);
}