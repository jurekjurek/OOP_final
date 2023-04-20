#ifndef PIECE_H
#define PIECE_H

#include "position.h"

/*
 *  The piece class will be able to hold the general eigenschaften eines Pieces.
 *
 *
 *
*/


enum PieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};



class Piece {
private:
    Position Pos;
    bool Isalive;
    bool Iswhite;
public:

    // constructor
    Piece(bool iswhite) {
        this->Iswhite = iswhite;
        this->Isalive = true;
    }
    // default constructor
    Piece() {
        this->Iswhite = true;
        this->Isalive = true;
    }

    // setters and getters for all the variables, but I don't know if we will actually need all of these

    void setPos(Position pos) {this->Pos = pos;}
    void setIswhite(bool iswhite) {this->Iswhite = iswhite;}
    void setIsalive(bool isalive) {this->Isalive = isalive;}
    Position getPos() {return this->Pos;}
    bool getIswhite() {return this->Iswhite;}
    bool getIsalive() {return this->Isalive;}

    bool move_valid(Position final);    // this function checks, depending on the move rules for every piece, if a move is valid to a certain position

    PieceType Piecetype();

};


// now for all the subpieces that inherit from the mother class Piece

// the king is a special piece, once it is attacked with no possibility of being rescued, the game is over.

class King: public Piece {
public:
    King(bool iswhite) : Piece(iswhite) {}
    King() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) {
        if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

        int tx[] = {1, 1, -1, -1, 1, -1, 0, 0};
        int ty[] = {-1, 1, -1, 1, 0, 0, 1, -1};
        bool result = false;

        for (int i =0; i<8; i++) {
            int x = this->getPos().getX();
            int y = this->getPos().getY();
            if (x+tx[i] == final.getX() and y+ty[i] == final.getY()) {result = true;}

        }
        return result;
    }

    PieceType Piecetype() {return KING;}

};


class Queen: public Piece {
public:
    Queen(bool iswhite) : Piece(iswhite) {}
    Queen() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) {
        if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

        int tx[] = {1, 1, -1, -1, 1, -1, 0, 0};
        int ty[] = {-1, 1, -1, 1, 0, 0, 1, -1};
        bool result = false;

        for (int i =0; i<8; i++) {
            int x = this->getPos().getX();
            int y = this->getPos().getY();
            for (int j = 0; j<8; j++) {
                if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {result = true;}
            }

        }
        return result;
    }

    PieceType Piecetype() {return QUEEN;}

};


class Rook: public Piece {
public:
    Rook(bool iswhite) : Piece(iswhite) {}
    Rook() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) {
        if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

        int tx[] = {1, -1, 0, 0};
        int ty[] = {0, 0, 1, -1};
        bool result = false;

        for (int i =0; i<4; i++) {
            int x = this->getPos().getX();
            int y = this->getPos().getY();
            for (int j = 0; j<8; j++) {
                if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {result = true;}
            }
        }
        return result;
    }

    PieceType Piecetype() {return ROOK;}

};


class Knight: public Piece {
public:
    Knight(bool iswhite) : Piece(iswhite) {}
    Knight() {Piece();}
    // check, when a certain move is valid!
    bool move_valid(Position final) {
        if (!final.check_pos()) {return false;}

        int tx[] = {-2, -2, -1, 1, 2, 2, 1, -1};
        int ty[] = {-1, 1, 2, 2, 1, -1, -2, 2};
        bool result = false;

        for (int i =0; i<8; i++) {
            int x = this->getPos().getX();
            int y = this->getPos().getY();
            if (x+tx[i] == final.getX() and y+ty[i] == final.getY()) {result = true;}

        }
        return result;
    }

    PieceType Piecetype() {return KNIGHT;}

};


class Bishop: public Piece {
public:
    Bishop(bool iswhite) : Piece(iswhite) {}
    Bishop() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) {
        if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

        int tx[] = {1, 1, -1, -1};
        int ty[] = {-1, 1, -1, 1};
        bool result = false;

        for (int i =0; i<8; i++) {
            int x = this->getPos().getX();
            int y = this->getPos().getY();
            for (int j = 0; j<8; j++) {
                if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {result = true;}
            }

        }
        return result;
    }

    PieceType Piecetype() {return BISHOP;}

};


class Pawn: public Piece {
private:
    bool Firstmove = false;
    bool Capturepossible = false;
public:

    void setFirstmove(bool firstmove) {this->Firstmove = firstmove;}
    bool getFirstmove() {return this->Firstmove;}

    Pawn(bool iswhite) : Piece(iswhite) {}
    Pawn() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) {
        if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}
        bool result = false;


        int x = this->getPos().getX();
        int y = this->getPos().getY();

        if (this->Firstmove and x == final.getX() and y+2 == final.getY()) {result = true;}
        else if (x == final.getX() and y+1 == final.getY()) {result = true;}

        return result;
    }

    // Pawn is the only piece that has a capture_valid class!
    bool capture_valid(Position final) {
        if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}
        if (!this->Capturepossible) {std::cout << "invalid move, pawn not in position to capture" << std::endl; return false;}
        bool result = false;

        int x = this->getPos().getX();
        int y = this->getPos().getY();

        if (x+1 == final.getX() and y+1 == final.getY()) {result = true;}
        else if (x-1 == final.getX() and y+1 == final.getY()) {result = true;}

        return result;
    }


    PieceType Piecetype() {return PAWN;}

};













#endif // PIECE_H
