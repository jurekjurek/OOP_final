#ifndef MAIN_GUI_H
#define MAIN_GUI_H

#include "square.h"
#include "game.h"

#include <QGraphicsScene>
#include <QObject>
#include <QPushButton>
#include <QWidget>

/*
 * This class is responsible for handling everyting the GUI does.
 * It connects the square class to the game class and receives certain moves from the game class
 * to implement graphically. Furthermore, it receives strings indicating errors and warning messages the Game slot is emitting
 * Parts of the GUI implementation with Qt are inspired by https://github.com/djbauman/Qt-Chess
*/


class GUI: public QObject //, public QGraphicsView
{
    // if this line of code is included, it tells us that we can use signals and slots for our widgets
    // Basically, this is here so C++ understands all the stuff that we write
    Q_OBJECT
private:
    // All QT logic goes inside the scene, we always need a scene. This is what is going to be shown via View in the main function
    QGraphicsScene * Scene_GUI;

    // Of course we have to connect the game to QT somehow, get Game in there
    ChessGame game;

    // A list containing all the Squares on the Board, derived from class Square
    QList<Square *> squares;

    // to display the correct pieces depending on the location of the program on your computer
    QString PATH_QT;

    // sets up the board with the pieces
    void initialize_interface();

    // resets the color after each turn, square is colored red upon clicking on it
    void resetColor();

    // Keep track of whose turn it is (Color == true -> whites turn, Color == false -> blacks turn)
    bool Color;

    // Display warnings and information on the screen
    QGraphicsTextItem * whoseturn;
    QGraphicsTextItem * alert;
    QGraphicsTextItem * prom;

    // array of positions on the chessboard. To be assigned to the squares.
    const QString positions[64] =
    {
        "07", "17", "27", "37", "47", "57", "67", "77",
        "06", "16", "26", "36", "46", "56", "66", "76",
        "05", "15", "25", "35", "45", "55", "65", "75",
        "04", "14", "24", "34", "44", "54", "64", "74",
        "03", "13", "23", "33", "43", "53", "63", "73",
        "02", "12", "22", "32", "42", "52", "62", "72",
        "01", "11", "21", "31", "41", "51", "61", "71",
        "00", "10", "20", "30", "40", "50", "60", "70"
    };


    // for the different promotion possibilities
    Square *button1;
    Square *button2;
    Square *button3;
    Square *button4;

public:
    // constructor
    GUI();
    QGraphicsScene* getScene();


public slots:
    void getResultingBoard(QString response);


};


#endif // MAIN_GUI_H
