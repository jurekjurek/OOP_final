#ifndef BOARD_H
#define BOARD_H
#include "player.h"

/*  The Borad class is an 8x8 array of pointers to pieces.
 *
 *  This class is responsible for nothing more than being a board, so being able to hold pieces and set pieces to given positions
 *
 *
*/

class ChessBoard {
private:
    Piece* Board[8][8];
    Player* Black;
    Player* White;
public:
    // constructor sets all the pointers to zero
    ChessBoard(Player*, Player*);

    // default constructor

    ChessBoard();

    Player* getPlayerBlack();
    Player* getPlayerWhite();

    void setPlayerWhite(Player*);
    void setPlayerBlack(Player*);

    void printBoard();


    Piece* getPiece(Position);


    // set piece with given color to some position
    void setPiece(Piece*, Position, Player*);

};




#endif // BOARD_H

