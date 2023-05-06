#ifndef GAME_H
#define GAME_H

#include "board.h"

/*  The most important class
 *  Here, the game is being controlled.
 *
 *
 *
*/

enum MaketurnError {
    NOVALIDPOS,
    NOPIECE,
    PIECEINWAY,
    WRONGCOLOR,
    SPOTBLOCKED,
    SPOTBLOCKED_PAWN,
    NOVALIDMOVE,
    KINGUNSAFE
};

class ChessGame {
private:
    Player White, Black;
//    Player Black;
    ChessBoard Board;
    bool Whoseturn;         // true for white, false for black
    GameState state;
    MaketurnError error;
    vector<int> move_list;
    int move_count;
    int promotion_count;
public:
    // when the class is called, a new game is generated
    // Black is not white, White is white
    ChessGame();

    Player getPlayerWhite();
    Player getPlayerBlack();


    bool Maketurn(Player, Player, Move);


    // Is Player current attacking spot dest??
    bool Attack(Player, Player, Position);

    // Is current player checking other player?
    // abaendern!!
    bool Check(Player, Player);

    bool CheckMate(Player, Player);
    // this function is quite similar to the CheckMate function
    // but actually, we have to make sure that no piece can move. Not a single one.


    bool StaleMate(Player, Player);


    void promotion(Player, Player, Position);



    // this method is responsible for keeping the game going
    void Game();


};

#endif // GAME_H
