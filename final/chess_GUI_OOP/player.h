#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"


/*
 * Every Player has a set of pieces and a Color. The Pieces have the same color as the Player.
*/

class Player {
private:
    bool Color;
    King* KinG;
    Queen* Queens[2];
    Rook* Rooks[3];
    Bishop* Bishops[3];
    Knight* Knights[3];
    Pawn* Pawns[8];

public:
    // default constructor
    Player();
    Player(bool);

//    ~Player();

    bool getColor();
    void setColor(bool);

    // now, we need a possibility of accessing the pieces of the player
    // we need a method to return a certain piece, or rather a pointer to a given piece

    // we need these methods in the player class because each piece belongs to one particular player

    King* getKing();

    Queen* getQueen(int);

    // For these Pieces, we have two, so we have to pick a piece, each piece has a number assigned to it
    Rook* getRook(int);

    Bishop* getBishop(int);

    Knight* getKnight(int);

    Pawn* getPawn(int);

    vector<Piece*> getAlivePieces();

};






#endif // PLAYER_H
