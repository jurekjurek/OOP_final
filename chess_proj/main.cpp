#include <iostream>

//#include "position.h"
//#include "piece.h"
//#include "player.h"
//#include "board.h"
#include "game.h"
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
    Position position(1,1);
    Position position2(1,3);
    bool iswhite = true;
//    Move movee;
//    movee.setFirst(position);
//    movee.setLast(position2);
//    cout << movee.getFirst().getX() << endl;
//    Rook rook(true);
//    King king(true);
//    king.setPos(position);
//    Pawn pawn(true);
//    pawn.setPos(position);
//    pawn.setFirstmove(true);
//    rook.setPos(position);
//    cout << pawn.move_valid(position2) << endl;
//    Player player1(iswhite);
//    Player player2(!iswhite);
//    cout << player2.getIswhite() << " and " << player1.getIswhite() << endl;
//    cout << "What do we get? " << player.getBishop(2) << endl;            // returns a pointer
//    ChessBoard board(player1, player2);
//    cout << board.getPiece(Position(1,1))->getIswhite() << " and " << board.getPiece(Position(1,7))->getIswhite() << endl;
    ChessGame test_game;
    return 0;
}
