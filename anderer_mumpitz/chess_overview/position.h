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
//        if (x >= 0 and y >= 0 and x < 8 and y < 8) {
//            this->X = x;
//            this->Y = y;
//            this->Valid = true;
//        }
//        else {this->X = 0; this->Y = 0; this->Valid=false;}
//    }
    // default constructor, FINDE NOCHMAL RAUS, WARUM!!
    Position();
    // setter and getter for the private variables X, Y
    void setX(int);
    void setY(int);
    int getX();
    int getY();

    bool check_pos();
//        if (this->X >= 0 and this->Y >= 0 and this->X < 8 and this->Y < 8) {return true;}
//        else {return false;}
//    }

    bool getValid();

    Position shiftPos(int, int); // {this->X += x; this->Y += y; return Position(this->X, this->Y);}

};

// the class Move is handy, because it can hold two positions

class Move {
private:
    Position First;
    Position Last;
public:
    Move(Position first, Position last) {this->First = first; this->Last = last;}
    // default one, no idea why
    Move() {}
    // getter and setter for the positions first and last
    void setFirst(Position first) {this->First = first;}
    void setLast(Position last) {this->Last = last;}
    Position getFirst() {return this->First;}
    Position getLast() {return this->Last;}
};

#endif // POSITION_H
