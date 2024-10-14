//
// Created by john simpsen on 9/10/2024.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib> //For quitting program early: exit(1);

#include "Driver.h"
#include "Node.h"
#include "LinkedList.h"

using namespace std;

//List Size Constants
constexpr int NUM_OF_DRIVERS = 20;
constexpr int NUM_OF_COORDINATES = 20;

//Prototypes
void readDataFile(const string&, double[NUM_OF_DRIVERS][NUM_OF_COORDINATES][2], string[NUM_OF_DRIVERS]);
void readCommandFile(const string&, LinkedList& list);
bool validateLine(string);
bool validateCoordinates(string);
void getCoordinates(double[NUM_OF_DRIVERS][NUM_OF_COORDINATES][2], const string&, int, int);
double calculateArea(double[NUM_OF_DRIVERS][NUM_OF_COORDINATES][2], int);

int main() {
    //3D array and Driver array defined to store coordinates
    double coordinates[NUM_OF_DRIVERS][NUM_OF_COORDINATES][2];
    string drivers[NUM_OF_DRIVERS];

    string dataFilename;
    string commandFilename;

    //Data Input
    cout << "filename for driver data: ";
    getline(cin, dataFilename);

    //Command Input
    cout << "filename for command data: ";
    getline(cin, commandFilename);

    cout << endl;

    readDataFile(dataFilename, coordinates, drivers);

    //Define Linked List
    LinkedList *list = new LinkedList();

    //Output
    for (int i = 0; i < NUM_OF_DRIVERS; i+=1) {

        if (drivers[i].empty())
            break;


        double area = calculateArea(coordinates, i);

        //Don't add driver if area is Nan or 0 or greater than the integer limit
        if (area == area && area != 0 && !(area > 2147483647)) {
            //Make Driver Object
            Driver* d = new Driver(drivers[i], area);

            //Make a node object and assign the driver to it
            Node* n = new Node(*d);

            //Insert the node into the LinkedList
            LinkedList::insert(*list, n);
        }

    }

    //Print list using it's overloaded (<<) of the LinkedList class
    cout << *list << endl;

    readCommandFile(commandFilename, *list);

    return 0;
}

void readDataFile(const string& filename, double coordinates[NUM_OF_DRIVERS][NUM_OF_COORDINATES][2], string drivers[NUM_OF_DRIVERS]) {
    ifstream input("../" + filename);

    //Error Handling
    if (!input.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        exit(1);
    }

    string line;
    int i = 0;
    //Read the driver name from the input file
    while(getline(input, line)) {
        int index = 0;
        //Loop through and detect the first instance of a digit
        //If the character before the first digit is a -, set the index equal to that position and exclude it from the name
        while (!isdigit(line[index])) {
            index += 1;
        }
        if (line[index-1] == '-') {
            index -= 1;
        }

        //make sure name and coords are seperated by a space
        if (line[index-1] != ' ') {
            continue;
        }

        drivers[i] =line.substr(0, index-1);
        line = line.substr(index);

        //Check if the line has valid coordinates
        if(validateLine(line)) {
            int j = 0;
            //Read the rest of the line and call getCoordinates to separate the coordinates
            //Runs until the line is empty
            while (line.empty() == false) {
                string coords;
                index = line.find(' ');

                if (index != string::npos) {
                    coords = line.substr(0, index);
                    line = line.substr(index + 1);
                }
                else {
                    coords = line;
                    line.clear();
                }

                getCoordinates(coordinates, coords, i, j);

                j+=1;
            }
            i+=1;
        }

        //Continue to next iteration of the while loop
        else {
            continue;
        }
    }
    input.close();
}

void readCommandFile(const string& filename, LinkedList& list) {
    ifstream input("../" + filename);

    //Error Handling
    if (!input.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        exit(1);
    }

    string line;
    while(getline(input, line)) {
        int index = line.find(' ');
        string command = line.substr(0, index);

        //Sort Command
        if (command == "sort") {

            //check if the sort parameter is either area or name, if not then provide an error
            string param = line.substr(index + 1);
            if (param == "area" || param == "driver") {
                Driver::setComparison(line.substr(index + 1));
                list.sort();

                //print the list
                cout << list << endl;
            }
            else {
                cout << "Error: Sort by either area or driver" << endl;
                cout << endl;
            }
        }
        //Search Commands
        else {

            //reassigns command to the entire line to accommodate names with spaces
            command = line;

            //find if the string is an area or name and is valid
            bool isNum = true;
            for (int k = 0; k < command.size(); k+=1) {

                if (isdigit(command[k]) || command[k] == '.' || command[k] == '-') {
                    continue;
                }
                else {
                    isNum = false;
                }
            }

            //search by area
            if (isNum) {
                double num = stod(command);
                num = floor(num*100)/100.0;
                LinkedList::search(num, list);
            }
            //search by name
            else {

                bool valid = true;
                //Validate the input is valid
                for (int k = 0; k < command.size(); k+=1) {
                    if (!(isalpha(command[k]) || command[k] == '-' || command[k] == '\'' || command[k] == ' ')) {
                        //cout << command << " not searched" << endl;
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    LinkedList::search(command, list);
                }
            }
        }
    }
    input.close();
}

bool validateLine(string line) {
    if (line.empty()) {
        return false;
    }

    string firstCoords;
    string lastCoords;
    bool isFirst = true;

    while (!line.empty()) {
        string coords;

        int index = line.find(' ');

        if (index != string::npos) {
            coords = line.substr(0, index);
            line = line.substr(index + 1);
        } else {
            coords = line;
            line = ""; // Clear the line to exit the loop
        }

        //Check if each coordinate is valid
        if (!validateCoordinates(coords)) {
            return false;
        }

        //Store the first coordinate
        if (isFirst) {
            firstCoords = coords;
            isFirst = false;
        }

        //Update the last coordinate with each valid coordinate
        lastCoords = coords;
    }

    //check if the first coordinate matches the last one
    if (firstCoords != lastCoords) {
        return false;
    }

    return true;
}

bool validateCoordinates(string coords) {
    int index = coords.find(',');

    // Check if the comma is found, and that it is not at the start or end of string
    if (index == string::npos || index == 0 || index == coords.size() - 1) {
        return false;
    }

    string xString = coords.substr(0, index);
    string yString = coords.substr(index + 1);

    //make sure both xString and yString are not empty
    if (xString.empty() || yString.empty()) {
        return false;
    }

    //check if last character of xString or yString is '.'
    if (xString[xString.size()-1] == '.' || yString[yString.size()-1] == '.') {
        return false;
    }

    //Check if there are multiple '.' in the coordinates
    int dotCnt = 0;
    for (int i = 0; i < xString.size(); i++) {
        if (xString[i] == '.')
            dotCnt += 1;
    }

    if (dotCnt > 1)
        return false;
    dotCnt = 0;

    for (int i = 0; i < yString.size(); i++) {
        if (yString[i] == '.')
            dotCnt += 1;
    }

    if (dotCnt > 1)
        return false;
    dotCnt = 0;

    //Validate x-coordinate is a digit or -
    for (int i = 0; i < xString.size(); i++) {
        if (!(isdigit(xString[i]) || xString[i] == '-' || xString[i] == '.')) {
            return false;
        }
    }

    //Validate y-coordinate is a digit or -
    for (int i = 0; i < yString.size(); i++) {
        if (!(isdigit(yString[i]) || yString[i] == '-' || yString[i] == '.')) {
            return false;
        }
    }

    return true;
}

void getCoordinates(double coordinates[NUM_OF_DRIVERS][NUM_OF_COORDINATES][2], const string& coords, int row, int col) {
    int index = coords.find(',');

    double x = stod(coords.substr(0, index));
    double y = stod(coords.substr(index + 1));

    //parse coordinates into 3D array
    coordinates[row][col][0] = x;
    coordinates[row][col][1] = y;
}

double calculateArea(double coordinates[NUM_OF_DRIVERS][NUM_OF_COORDINATES][2], const int row) {
    double sum = (coordinates[row][1][0] + coordinates[row][0][0]) * (coordinates[row][1][1] - coordinates[row][0][1]);

    int i = 1;
    while (!((coordinates[row][i][0] == coordinates[row][0][0]) && (coordinates[row][i][1] == coordinates[row][0][1])) && i < NUM_OF_COORDINATES) {
        sum += (coordinates[row][i+1][0] + coordinates[row][i][0]) * (coordinates[row][i+1][1] - coordinates[row][i][1]);
        i+=1;
    }
    return .5 * fabs(sum);
}