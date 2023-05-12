#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <sstream>
#include <QDebug>
#include <QObject>
#include <QString>

/*  The most important class
 *  Here, the game is being controlled.
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

enum Color
{
    WHITE,
    BLACK
};

class ChessGame : public QObject{
    Q_OBJECT
private:
    Player White;
    Player Black;
    Player *Current;
    Player *Other;
    ChessBoard Board;
    bool Whoseturn;         // true for white, false for black
    GameState state;
    MaketurnError error;
    vector<int> move_list;
    int move_count;
    int promotion_count;
    bool enpassant = false;
    std::string move1;
    std::string move2;
    void resetMoves();
public:
    // when the class is called, a new game is generated
    // Black is not white, White is white
    ChessGame();

    Player getPlayerWhite();
    Player getPlayerBlack();


    bool Maketurn(Move);

    bool Checkmove(Move, Player*);


    // Is Player current attacking spot dest??
    bool Attack(Position, Player*);

    // Is current player checking other player?
    // abaendern!!
    bool Check(Player*, Player*);


    bool CheckMate(Player*, Player*);
    // this function is quite similar to the CheckMate function
    // but actually, we have to make sure that no piece can move. Not a single one.


    bool StaleMate();


    void promotion(Position);



    // this method is responsible for keeping the game going
//    void Game();

    // Qt Signaling
public slots:
    void getInput(QString input);

signals:
    void sendResponse(QString response);

};

#endif // GAME_H

