#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
 *  The whole Project is structured using certain classes.
 *  Firstly, there is a position class. This class holds Positions on the chessboard, characterized by X and Y.
 *  The Square E4 on a Chessboard for example corresponds to the position Position(4, 3) (Position(0, 0) is A1)
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

    // A position can be valid or not, this is what we check here
    bool check_pos();

    // is the position valid?
    bool getValid();

};

#endif // POSITION_H

