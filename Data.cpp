//
// Created by Benjamin Raiford on 12/4/19.
//

#include "Data.h"
using namespace std;


//Default Constructor
Data::Data() {
    startSpeed = -1;
    endSpeed = -1;
    pitchResult = "Null";
    pitchType = "Null";
}

//CSV Constructor
Data::Data(double s_Speed, double e_Speed, std::string result, std::string type) {
    startSpeed = s_Speed;
    endSpeed = e_Speed;
    pitchResult = *(&result); //here I dereference the pointer to avoid creating copies of string
    pitchType = *(&type);
}

//Sort primarily by speed at strike zone, secondarily by speed from pitcher's hand
bool Data::operator<(const Data &rhs) {
    if(this->endSpeed != rhs.endSpeed){
        return this->endSpeed < rhs.endSpeed;
    }
    else{
        return this->startSpeed < rhs.startSpeed;
    }
}
bool Data::operator>(const Data &rhs) {
    if(this->endSpeed != rhs.endSpeed){
        return this->endSpeed > rhs.endSpeed;
    }
    else{
        return this->startSpeed > rhs.startSpeed;
    }
}
bool Data::operator==(const Data &rhs) {
    if (!(*this < rhs) && !(*this > rhs)){
        return true;
    }
    else
        return false;
}
bool Data::operator<=(const Data &rhs) {
    if ((*this < rhs) || (*this == rhs)){
        return true;
    }
    else
        return false;
}

//Print Data to the screen
void Data::printDataScreen() {
        cout << "Data type: " << pitchType << endl;
        cout << "Speed from pitcher's hand: " << startSpeed << endl;
        cout << "Speed at strike zone: " << endSpeed << endl;
        cout << "Data result: " << pitchResult << endl;
}

//Output stream operator
ostream &operator<<(ostream &os, const Data &p) {
    os << "Data type: " << p.pitchType << endl;
    os << "Speed at strike zone: " << p.endSpeed << endl;
    os << "Speed from pitcher's hand: " << p.startSpeed << endl;
    os << "Data result: " << p.pitchResult << endl;

    return os;
}
