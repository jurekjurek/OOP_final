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
    Piece(bool iswhite) {
        this->Iswhite = iswhite;
        this->Isalive = true;
    }
    // default constructor
    Piece() {
        this->Iswhite = true;
        this->Isalive = true;
    }

    void setFirstmove(bool firstmove) {this->Firstmove = firstmove;}
    bool getFirstmove() {return this->Firstmove;}

    // setters and getters for all the variables, but I don't know if we will actually need all of these

    void setPos(Position pos) {this->Pos = pos;}
    void setIswhite(bool iswhite) {this->Iswhite = iswhite;}
    void setIsalive(bool isalive) {this->Isalive = isalive;}
    Position getPos() {return this->Pos;}
    bool getIswhite() {return this->Iswhite;}
    bool getIsalive() {return this->Isalive;}

    virtual bool move_valid(Position final) {
        return true;
    }    // this function checks, depending on the move rules for every piece, if a move is valid to a certain position

    virtual PieceType Piecetype() {
//        std::cout << "King" << std::endl;
        return NONE;
    }

    virtual void setPieceNo(int) {
        // return 0;
    }

    virtual int getPieceNo() {
        return 0;
    }

};



// now for all the subpieces that inherit from the mother class Piece

// the king is a special piece, once it is attacked with no possibility of being rescued, the game is over.

class King: public Piece {
public:
    King(bool iswhite) : Piece(iswhite) {}
    King() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) override {
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

    PieceType Piecetype() override {
//        std::cout << "Type King" << std::endl;
        return KING;
    }

};


class Queen: public Piece {
public:
    Queen(bool iswhite) : Piece(iswhite) {}
    Queen() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) override {
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

    PieceType Piecetype() override {
//        std::cout << "Type Queen" << std::endl;
        return QUEEN;
    }

};


class Rook: public Piece {
private:
    int PieceNo;
public:
    Rook(bool iswhite) : Piece(iswhite) {}
    Rook() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) override {
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

    PieceType Piecetype() override {
//        std::cout << "Type Rook" << std::endl;
        return ROOK;
    }

    void setPieceNo(int i) override {
        if (i<0 or i>1) {
            this->PieceNo = -1;
        }
        this->PieceNo = i;
    }

    int getPieceNo() override {
        return this->PieceNo;
    }

};


class Knight: public Piece {
private:
    int PieceNo;
public:
    Knight(bool iswhite) : Piece(iswhite) {}
    Knight() {Piece();}
    // check, when a certain move is valid!
    bool move_valid(Position final) override {
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

    PieceType Piecetype() override {
//        std::cout << "Type Knight" << std::endl;
        return KNIGHT;
    }

    void setPieceNo(int i) override {
        if (i<0 or i>1) {
            this->PieceNo = -1;
        }
        this->PieceNo = i;
    }

    int getPieceNo() override {
        return this->PieceNo;
    }

};


class Bishop: public Piece {
private:
    int PieceNo;
public:
    Bishop(bool iswhite) : Piece(iswhite) {}
    Bishop() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) override {
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

    PieceType Piecetype() override {
//        std::cout << "Type Bishop" << std::endl;
        return BISHOP;
    }

    void setPieceNo(int i) override {
        if (i<0 or i>1) {
            this->PieceNo = -1;
        }
        this->PieceNo = i;
    }

    int getPieceNo() override {
        return this->PieceNo;
    }

};


class Pawn: public Piece {
private:
    bool Capturepossible = false;
    int PieceNo;
public:

//    void setFirstmove(bool firstmove) {this->Firstmove = firstmove;}
//    bool getFirstmove() {return this->Firstmove;}

    Pawn(bool iswhite) : Piece(iswhite) {}
    Pawn() {Piece();}

    // check, when a certain move is valid!
    bool move_valid(Position final) override {
        if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}
        bool result = false;


        int x = this->getPos().getX();
        int y = this->getPos().getY();

        if (this->getFirstmove() and x == final.getX() and y+2 == final.getY()) {result = true;}
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


    PieceType Piecetype() override {
//        std::cout << "Type Pawn" << std::endl;
        return PAWN;
    }

    void setPieceNo(int i) override {
        if (i<0 or i>7) {
            this->PieceNo = -1;
        }
        this->PieceNo = i;
    }

    int getPieceNo() override {
        return this->PieceNo;
    }

};


#endif // PIECE_H
