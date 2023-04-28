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
    Position position(1,0);
    Position position2(0,2);
    Move move(position, position2);
//    bool iswhite = true;
    Player white(true);
    Player black(false);
//    white.getBishop(0);
//    ChessBoard Board;
//    Board = ChessBoard(white, black);
//    ChessBoard Board(white, black);
//    cout << white.getKnight(0)->getPos().getX() << " and " << white.getKnight(0)->getPos().getY() << endl;
//    cout << Board.getPlayerBlack().getKnight(0)->getPos().getX() << " and " << Board.getPlayerBlack().getKnight(0)->getPos().getY() << endl;
//    cout << Board.getPiece(position)->getIswhite() << endl;
//    cout << Board.getPiece(position)->getPos().getX() << " and " << Board.getPiece(position)->getPos().getY() << endl;
//    cout << Board.getPiece(position)->getIsalive() << endl;
//    Board.printBoard();
//    Piece* pieceOne = Board.getPiece(position);
//    cout << "Ist hier das Problem??" << pieceOne->getPos().getX() << " and " << pieceOne->getPos().getY() << "color " << pieceOne->getIswhite() <<  endl;
//    Board.getPiece(position)->Piecetype();
    ChessGame game;
//    Player white = game.getPlayerWhite();
//    Player black = game.getPlayerBlack();
//    game.Maketurn(move);
    game.Game();
    return 0;
}
