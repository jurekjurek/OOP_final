#ifndef POSITION_H
#define POSITION_H


#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
 *  This class can hold a position, characterised by an X- and a Y-value
 *  Every class name will be uppercase!
 *  The class move will be containing a move from a position to another one
*/

class Position {
private:
    int X,Y;
    bool Valid;
public:
    // constructor
    Position(int, int);

    // default constructor, FINDE NOCHMAL RAUS, WARUM!!
    Position();
    // setter and getter for the private variables X, Y
    void setX(int);
    void setY(int);
    int getX();
    int getY();

    bool check_pos();

    bool getValid();

    Position shiftPos(int, int); // {this->X += x; this->Y += y; return Position(this->X, this->Y);}

};


#endif // POSITION_H
