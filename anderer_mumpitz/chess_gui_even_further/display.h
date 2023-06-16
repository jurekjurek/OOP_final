#ifndef DISPLAY_H
#define DISPLAY_H

#include "space.h"
#include "game.h"

#include <QGraphicsScene>
#include <QObject>


class Display: public QObject
{
    Q_OBJECT
private:
    QGraphicsScene * DisplayScene;
    ChessGame game;
    QList<Space *> spaceList;
    QString move;
    void setup();
    void placePieces();
    Color turnColor;
    QGraphicsTextItem * turn;
    QGraphicsTextItem * check;

//    const QString spaces[64] =
//    {
//        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
//        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
//        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
//        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
//        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
//        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
//        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
//        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
//    };

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

public:
    Display();
    QGraphicsScene* getScene();

public slots:
    void getResponse(QString response);

};


#endif // DISPLAY_H
