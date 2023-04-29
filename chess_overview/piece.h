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
    PAWN,
    NONE
};



class Piece {
private:
    Position Pos;
    bool Isalive;
    bool Iswhite;
//    int PieceNo;
    bool Firstmove = true;
public:

    // constructor
    Piece(bool);
    // default constructor
    Piece();
    void setFirstmove(bool);
    bool getFirstmove();

    // setters and getters for all the variables, but I don't know if we will actually need all of these

    void setPos(Position);
    void setIswhite(bool);
    void setIsalive(bool);
    Position getPos();
    bool getIswhite();
    bool getIsalive();

    virtual bool move_valid(Position final);    // this function checks, depending on the move rules for every piece, if a move is valid to a certain position

    virtual PieceType Piecetype();

    virtual void setPieceNo(int);

    virtual int getPieceNo();

};



// now for all the subpieces that inherit from the mother class Piece

// the king is a special piece, once it is attacked with no possibility of being rescued, the game is over.

class King: public Piece {
public:
    King(bool);
    King();

    // check, when a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

};


class Queen: public Piece {
public:
    Queen(bool);
    Queen();

    // check, when a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

};


class Rook: public Piece {
private:
    int PieceNo;
public:
    Rook(bool);
    Rook();

    // check, when a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};


class Knight: public Piece {
private:
    int PieceNo;
public:
    Knight(bool);
    Knight();
    // check, when a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};


class Bishop: public Piece {
private:
    int PieceNo;
public:
    Bishop(bool);
    Bishop();

    // check, when a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};


class Pawn: public Piece {
private:
    bool Capturepossible = false;
    int PieceNo;
public:

//    void setFirstmove(bool firstmove) {this->Firstmove = firstmove;}
//    bool getFirstmove() {return this->Firstmove;}

    Pawn(bool);
    Pawn();

    // check, when a certain move is valid!
    bool move_valid(Position) override;

    // Pawn is the only piece that has a capture_valid class!
    bool capture_valid(Position);

    bool promotion();


    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};


#endif // PIECE_H
