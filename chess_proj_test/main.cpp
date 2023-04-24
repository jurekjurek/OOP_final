#include <iostream>

//#include "position.h"
//#include "piece.h"
//#include "player.h"
#include "board.h"
//#include "game.h"
//#include "test.h"
using namespace std;

/*
 *  Okay, let's structure this bad boy
 *  this is the main class.
 *  What we essentially do here, is instantiate the start_game class
 *
*/

int main()
{
    cout << "Hello World!" << endl;
    Position position(6,6);
    bool iswhite = true;
    Player white(true);
    Player black(false);
    ChessBoard Board(white, black);
    cout << Board.getPiece(position).getIswhite() << endl;
    cout << Board.getPiece(position).getPos().getX() << " and " << Board.getPiece(position).getPos().getY() << endl;
    cout << Board.getPiece(position).getIsalive() << endl;
    Board.getPiece(position).Piecetype();
    Board.printBoard();
}
