#ifndef PIECE_H
#define PIECE_H

#include "position.h"

/*
 *  The Piece class holds the chess pieces.
 *  Every Piece has a Position, a color and a Piecenumber.
 *
 *
*/

// Enum for all the piecetypes
enum PieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    NONE
};


// this is a virtual class. We will only use and create instances of classes that inherit from the piece class.
class Piece {
private:
    // Every pieve has a position
    Position Pos;

    // It is alive or not
    bool Alive;

    // Attribute called firstmove for castling or the Pawn move
    bool Firstmove = true;

    // An attribute for the Pawn
    bool enPassant;


protected:
    // Every piece besides the king has a piecenumber
    int  PieceNo;

    // Every piece has a color, true for white, false for black
    bool Color;

public:

    // constructor
    Piece(bool color);
    // default constructor
    Piece();

    // after a piece has moved, we will set its firstmove attribute to zero
    void setFirstmove(bool);
    bool getFirstmove();

    // setters and getters for all the variables

    void setPos(Position);
    void setColor(bool);
    void setAlive(bool);
    Position getPos();
    bool getColor();
    bool getAlive();

    // this is a virtual function, because we will never implement this for a piece without an assignment.
    // All of the individual move_valid functions will override this function
    // This function checks if a given move on the board is valid given *only* the rules of moving for this piece. It does not take into account the constellation on the board
    virtual bool move_valid(Position final);

    // Every piece has a piecetype besides the virtual class piece.
    virtual PieceType Piecetype();

    // getter and setter for the pieceNo.
    virtual void setPieceNo(int);
    virtual int getPieceNo();

    // only relevant for the pawn class
    bool getEnPassant();
    void setEnPassant(bool);

    // We do not need a setPromotion method. We will see why later

};



// now for all the subpieces that inherit from the mother class Piece
// KING
class King: public Piece {
public:
    King(bool);
    King();

    // check wether a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

};


class Queen: public Piece {
public:
    Queen(bool);
    Queen();

    // check wether a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

    // the Queen has a piecenumber
    void setPieceNo(int) override;

    int getPieceNo() override;

};

// ROOK
class Rook: public Piece {
public:
    Rook(bool);
    Rook();

    // check wether a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};

// KNIGHT
class Knight: public Piece {
public:
    Knight(bool);
    Knight();
    // check, when a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};

// BISHOP
class Bishop: public Piece {
public:
    Bishop(bool);
    Bishop();

    // check, when a certain move is valid!
    bool move_valid(Position) override;

    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};

// PAWN
class Pawn: public Piece {
public:

    Pawn(bool);
    Pawn();

    // check, when a certain move is valid!
    bool move_valid(Position) override;


    PieceType Piecetype() override;

    void setPieceNo(int) override;

    int getPieceNo() override;

};


#endif // PIECE_H
