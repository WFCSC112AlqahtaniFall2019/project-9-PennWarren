//
// Created by Benjamin Raiford on 12/4/19.
//

#include "Pitch.h"
using namespace std;


//Default Constructor
Pitch::Pitch() {
    startSpeed = -1;
    endSpeed = -1;
    pitchResult = "Null";
    pitchType = "Null";
}

//CSV Constructor
Pitch::Pitch(double s_Speed, double e_Speed, std::string result, std::string type) {
    startSpeed = s_Speed;
    endSpeed = e_Speed;
    pitchResult = *(&result); //here I dereference the pointer to avoid creating copies of string
    pitchType = *(&type);
}

//Sort primarily by speed at strike zone, secondarily by speed from pitcher's hand
bool Pitch::operator<(const Pitch &rhs) {
    if(this->endSpeed != rhs.endSpeed){
        return this->endSpeed < rhs.endSpeed;
    }
    else{
        return this->startSpeed < rhs.startSpeed;
    }
}
bool Pitch::operator>(const Pitch &rhs) {
    if(this->endSpeed != rhs.endSpeed){
        return this->endSpeed > rhs.endSpeed;
    }
    else{
        return this->startSpeed > rhs.startSpeed;
    }
}
bool Pitch::operator==(const Pitch &rhs) {
    if (!(*this < rhs) && !(*this > rhs)){
        return true;
    }
    else
        return false;
}
bool Pitch::operator<=(const Pitch &rhs) {
    if ((*this < rhs) || (*this == rhs)){
        return true;
    }
    else
        return false;
}

//Print Data to the screen
void Pitch::printDataScreen() {
        cout << "Pitch type: " << pitchType << endl;
        cout << "Speed from pitcher's hand: " << startSpeed << endl;
        cout << "Speed at strike zone: " << endSpeed << endl;
        cout << "Pitch result: " << pitchResult << endl;
}

//Output stream operator
ostream &operator<<(ostream &os, const Pitch &p) {
    os << "Pitch type: " << p.pitchType << endl;
    os << "Speed at strike zone: " << p.endSpeed << endl;
    os << "Speed from pitcher's hand: " << p.startSpeed << endl;
    os << "Pitch result: " << p.pitchResult << endl;

    return os;
}
