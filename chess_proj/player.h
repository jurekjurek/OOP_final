#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"



// different GameStates:

enum GameState {
    ACTIVE,
    ERROR,
    CHECK,
    DRAW,
    WHITEWINS,
    BLACKWINS
};



class Player {
private:
    bool Iswhite;
    King KinG;
    Queen QueeN;
    Rook Rooks[2];
    Bishop Bishops[2];
    Knight Knights[2];
    Pawn Pawns[8];

public:
    // default constructor
    Player() {}
    Player(bool iswhite) {
        this->Iswhite = iswhite;
        this->Rooks[0]      = new Rook(iswhite);
        this->Rooks[1]      = new Rook(iswhite);
        this->Bishops[0]    = new Bishop(iswhite);
        this->Bishops[1]    = new Bishop(iswhite);
        this->Knights[0]    = new Knight(iswhite);
        this->Knights[1]    = new Knight(iswhite);
        this->Pawns[0]      = new Pawn(iswhite);
        this->Pawns[1]      = new Pawn(iswhite);
        this->Pawns[2]      = new Pawn(iswhite);
        this->Pawns[3]      = new Pawn(iswhite);
        this->Pawns[4]      = new Pawn(iswhite);
        this->Pawns[5]      = new Pawn(iswhite);
        this->Pawns[6]      = new Pawn(iswhite);
        this->Pawns[7]      = new Pawn(iswhite);
    }

    bool getIswhite() {return this->Iswhite;}
    void setIswhite(bool iswhite) {this->Iswhite = iswhite;}

    // now, we need a possibility of accessing the pieces of the player
    // we need a method to return a certain piece, or rather a pointer to a given piece

    // we need these methods in the player class because each piece belongs to one particular player

    King* getKing() {return &KinG;}

    Queen* getQueen() {return &QueeN;}

    // For these Pieces, we have two, so we have to pick a piece, each piece has a number assigned to it
    Rook* getRook(int i) {
        // if(i<0 or i>1) {std::cout << "There are only two rooks." << std::endl; return nullptr;}
        return &Rooks[i];
    }
    Bishop* getBishop(int i) {
        if(i<0 or i>1) {std::cout << "There are only two bishops." << std::endl; return nullptr;}
        return &Bishops[i];
    }
    Knight* getKnight(int i) {
        if(i<0 or i>1) {std::cout << "There are only two knights." << std::endl; return nullptr;}
        return &Knights[i];
    }


    Pawn* getPawn(int i) {
        if(i<0 or i>7) {std::cout << "There are only eight pawns." << std::endl; return nullptr;}
        return &Pawns[i];
    }

    // we somehow have to get user input.
    // I will adapt this using the QT framework later. Now only to use cin and see if everything works.
    // we have to return a move
    Move getMove() {
        int x1, y1, x2, y2;
        std::cout << "Enter four numbers, the first two corresponding to x1, y1, the second two to x2, y2" << std::endl;
        std::cin >> x1 >> y1 >> x2 >> y2;
        Position pos1 = Position(x1, y1);
        Position pos2 = Position(x2, y2);
        Move move(pos1, pos2);
        return move;
    }

    // why is this here?
    void showOutput() {
        GameState status;
        switch (status) {
            case ACTIVE:
                std::cout << "Game active" << std::endl;
                break;
            case ERROR:
                std::cout << "ERROR" << std::endl;
                break;
            case CHECK:
                std::cout << "You're in check!" << std::endl;
                break;
            case DRAW:
                std::cout << "Game is drawn" << std::endl;
                break;
            case WHITEWINS:
                std::cout << "White wins" << std::endl;
                break;
            case BLACKWINS:
                std::cout << "Black wins" << std::endl;
                break;
        }
    }

};






#endif // PLAYER_H
