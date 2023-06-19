#ifndef BOARD_H
#define BOARD_H
#include "player.h"

/*
 *  This class is responsible for holding Players that hold pieces of different colors
 *  It holds Pointers to pieces that are arranged in a  8x8 matrix.
 *  To access a given Piece on the Board we access it by typing:
 *  Board[i][j] if we want to get the piece at position Position(i,j)
*/

class ChessBoard {
private:

    // This is an 8x8 Array of pointers to piece
    Piece* Board[8][8];

    // Two Pointers to players Black and White
    Player* Black;
    Player* White;
public:
    // constructor
    ChessBoard(Player*, Player*);

    // default constructor
    ChessBoard();

    // This will be important for the actual game when we have two players interacting
    Player* getPlayerBlack();
    Player* getPlayerWhite();

    void setPlayerWhite(Player*);
    void setPlayerBlack(Player*);

    // To debug, prints out the board in the console
    void printBoard();

    // getPiece and setPiece are very important methods
    // They are being used for every move that is made on the board.
    // Will return a pointer to a piece that is at a certain position on the board
    Piece* getPiece(Position);


    // sets the piece on the board to a given position and sets the position of the piece to this position as well
    void setPiece(Piece*, Position);

};




#endif // BOARD_H

