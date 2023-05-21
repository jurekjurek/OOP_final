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
    King* KinG;
    Queen* QueeN;
    Rook* Rooks[2];
    Bishop* Bishops[2];
    Knight* Knights[2];
    Pawn* Pawns[8];

public:
    // default constructor
    Player();
    Player(bool);

    ~Player();

    bool getIswhite();
    void setIswhite(bool);

    // now, we need a possibility of accessing the pieces of the player
    // we need a method to return a certain piece, or rather a pointer to a given piece

    // we need these methods in the player class because each piece belongs to one particular player

    King* getKing();

    Queen* getQueen();

    // For these Pieces, we have two, so we have to pick a piece, each piece has a number assigned to it
    Rook* getRook(int);

    Bishop* getBishop(int);

    Knight* getKnight(int);

    Pawn* getPawn(int);

};






#endif // PLAYER_H
