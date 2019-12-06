//
// Created by Benjamin Raiford on 12/4/19.
//

#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H

#include <iostream>
#include <fstream>
#include <string>

class Data {
public:

    //Constructors
    Data();
    Data(double s_Speed, double e_Speed, std::string result, std::string type);

    //Overloaded Operators
    bool operator >(const Data& rhs);
    bool operator <(const Data& rhs);
    bool operator ==(const Data &rhs);
    bool operator <=(const Data &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Data &p);

    //Functions
    void printDataScreen();

    //Data pulled from CSV
    double startSpeed; //ball speed leaving the pitcher's hand
    double endSpeed; //ball speed reaching the strike zone
    std::string pitchResult;
    std::string pitchType;


};


#endif //PROJECT9_DATA_H
