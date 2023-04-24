#include <iostream>

//#include "position.h"
//#include "piece.h"
//#include "player.h"
//#include "board.h"
#include "test.h"
using namespace std;

/*
 *  Okay, let's structure this bad boy
 *  this is the main class.
 *  What we essentially do here, is instantiate the start_game class
 *
*/

int main()
{
//    cout << "Hello World!" << endl;
    Position position(1,1);
    Position position2(1,2);
    Move move(position, position2);
//    bool iswhite = true;
//    Player white(true);
//    Player black(false);
//    white.getBishop(0);
//    ChessBoard Board;
//    Board = ChessBoard(white, black);
//    cout << Board.getPiece(position)->getIswhite() << endl;
//    cout << Board.getPiece(position)->getPos().getX() << " and " << Board.getPiece(position)->getPos().getY() << endl;
//    cout << Board.getPiece(position)->getIsalive() << endl;
//    Board.printBoard();
//    Piece* pieceOne = Board.getPiece(position);
//    cout << "Ist hier das Problem??" << pieceOne->getPos().getX() << " and " << pieceOne->getPos().getY() << "color " << pieceOne->getIswhite() <<  endl;
//    Board.getPiece(position)->Piecetype();
    ChessGame game;
    Player white = game.getPlayerWhite();
    Player black = game.getPlayerBlack();
    game.Maketurn(white, black, move);
    return 0;
}
