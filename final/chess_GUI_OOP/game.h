#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <sstream>
#include <QDebug>
#include <QObject>
#include <QString>

/*
 *  This class is responsible for connecting all those other classes Board, Player, Piece, Position, to form a chessgame
 *
*/

// There are several Errors that can Occur, each of them displayed when appropriate
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


// We have to differentiate between the four different kinds of Castles that can Occur.
// This happens in order for the GUI to be able to adjust the pieces on the Board accordingly.
enum Castles
{
    NOCASTLES,
    WHITEKINGSIDE,
    BLACKKINGSIDE,
    WHITEQUEENSIDE,
    BLACKQUEENSIDE
};


// Because this Class has a Qt slot called getInput,
// the Class chessGame has to inherit from QObject in order for the class to be able to handle signals and slots

class ChessGame : public QObject{
    Q_OBJECT
private:

    // Every game has a Board
    ChessBoard Board;

    // Whose turn is it? If it is whites turn -> Turn = true, if black -> Turn = false
    bool Turn;

    // to keep track of the errors made while trying to execute a move
    MaketurnError error;

    // store the moves that were made in a vector
    vector<int> move_list;

    // If enpassant is on the board
    bool enpassant = false;

    // Is there castles on the board? If so, what kind?
    Castles castlestate = NOCASTLES;

    // Is there a piece to promote?
    bool Promotion = false;

    // for the QT part, both moves are going to be saved as strings
    std::string position1;
    std::string position2;

public:
    // Constructor
    ChessGame();

    //  the maketurn function checks if a certain move can be made by a certain player
    // if so, it places the pieces on the board
    bool Maketurn(Position, Position);

    // the Checkmove function checks if, only given the constellation of the board, a move can be made.
    // It does not consider if the player is in check after the move is made
    // it does not move pieces on the board
    bool* Checkmove(Position, Piece*);


    // this function is checking if a given player is able to attack a certain spot (important for the check, checkmate and stalemate functions)
    bool Attack(Position, Player*);

    // Is Player Current checking Player Other
    bool Check(Player* Current, Player* Other);

    // Is there a checkmate on the board, thus has player Current won the game?
    bool CheckMate(Player* Current, Player* Other);

    // is the game a draw?
    bool StaleMate(Player*, Player*);

    // if there is a promotion to be dealt with, this function is called, setting the appropriate piece (determined by inputstring)
    // of the appropriate player to the appropriate position
    void promotion(Position, Player*, QString inputstring);


    // Qt Signals and Slots
public slots:

    // The game method gets as input Qstrings from the Class Space
    void Game(QString input);

signals:

    // And as a corresponding signal it sends the current Board state and other information to the Class display.h
    void sendResultingBoard(QString response);

};

#endif // GAME_H

