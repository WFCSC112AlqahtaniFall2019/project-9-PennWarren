//
// Created by Benjamin Raiford on 12/4/19.
//

#ifndef PROJECT9_PITCH_H
#define PROJECT9_PITCH_H

#include <iostream>
#include <fstream>
#include <string>

class Pitch {
public:

    //Constructors
    Pitch();
    Pitch(double s_Speed, double e_Speed, std::string result, std::string type);

    //Overloaded Operators
    bool operator >(const Pitch& rhs);
    bool operator <(const Pitch& rhs);
    bool operator ==(const Pitch &rhs);
    bool operator <=(const Pitch &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Pitch &p);




    //Functions
    void printDataScreen();

    //Data pulled from CSV
    double startSpeed; //ball speed leaving the pitcher's hand
    double endSpeed; //ball speed reaching the strike zone
    std::string pitchResult;
    std::string pitchType;


};


#endif //PROJECT9_PITCH_H
