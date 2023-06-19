#ifndef DISPLAY_H
#define DISPLAY_H

#include "space.h"
#include "game.h"

#include <QGraphicsScene>
#include <QObject>
#include <QPushButton>
#include <QWidget>
//#include <QGraphicsView>
//#include <QDragEnterEvent>
//#include <QDragMoveEvent>
//#include <QDragLeaveEvent>
//#include <QDropEvent>


// A chesspiece in the GUI can have two colors
enum Color
{
    WHITE,
    BLACK
};


class Display: public QObject //, public QGraphicsView
{
    // if this line of code is included, it tells us that we can use signals and slots for our widgets
    // Basically, this is here so C++ understands all the stuff that we write
    Q_OBJECT
private:
    // All QT logic goes inside the scene, we always need a scene
    QGraphicsScene * DisplayScene;
    // Of course we have to connect the game to QT somehow, get Game in there
    ChessGame game;
    // A list containing all the spaces, derived from class Space
    QList<Space *> spaceList;
    QString move;
    void setup();
    void placePieces();
    void resetColor();
    Color turnColor;
    QGraphicsTextItem * turn;
    QGraphicsTextItem * alert;
    QGraphicsTextItem * prom;

    const QString spaces[64] =
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
    Space *button1;
    Space *button2;
    Space *button3;
    Space *button4;

public:
    // constructor
    Display();
    QGraphicsScene* getScene();

//protected:
//    void dropEvent(QDropEvent *event);
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
//    void dragLeaveEvent(QDragLeaveEvent *event);

public slots:
    void getResultingBoard(QString response);


};


#endif // DISPLAY_H
