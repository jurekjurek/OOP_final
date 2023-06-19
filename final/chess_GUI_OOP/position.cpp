#include "position.h"



Position::Position(int x, int y) {
    if (x >= 0 and y >= 0 and x < 8 and y < 8) {
        this->X = x;
        this->Y = y;
        this->Valid = true;
    }
    else {this->X = 0; this->Y = 0; this->Valid=false;}
}


Position::Position() {
    this->X = 0; this->Y = 0;
}


void Position::setX(int x) {this->X = x;}

void Position::setY(int y) {this->Y = y;}

int Position::getX() {return this->X;}

int Position::getY() {return this->Y;}

bool Position::check_pos() {
    if (this->X >= 0 and this->Y >= 0 and this->X < 8 and this->Y < 8) {return true;}
    else {return false;}
}


bool Position::getValid() {
    return this->Valid;
}




Move::Move(Position from, Position to) {
    this->From = from; this->To = to;
}

Move::Move() {

}

void Move::setFrom(Position from) {
    this->From = from;
}

Position Move::getFrom() {
    return this->From;
}

void Move::setTo(Position to) {
    this->To = to;
}

Position Move::getTo() {
    return this->To;
}






