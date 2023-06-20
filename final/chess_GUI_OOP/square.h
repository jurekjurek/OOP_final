#ifndef SQUARE_H
#define SQUARE_H

#include <QDebug>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QBrush>
#include <string>
#include <QGraphicsScene>

/*
 * This class resembles one square on the chessboard. To actually set up a GUI with a full board, there will be 64 instances of the square class created.
 * Every square has a position respective to the board and it has a piece assigned to it in the form of a picture.
 * We want to be able to manipulate the picture (delete it, set another picture (of another piece)) in the course of the game. This is what the methods are for
*/

// Space inherits from QObject and QGrapphicsRectItem to handle signals and Slots and of course, A space is on the chessBoard just a Rectangle
class Square: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    // Every space has a Position corresponding to its X and Y coordinate on the chessBoard
    QString position;

    // Every space carries a piece, which is an PixmapItem
    // The QGraphicsPixmapItem is used to display a QPixmap inside a Scene
    QGraphicsPixmapItem piece;

    // PixmapItem (piece) is associated to a particular picture of that piece
    QString picture;

    // And every Square on the board has X and Y coordinates
    int X;
    int Y;
public:
    // constructor
    Square(int x, int y);

    // getters and setters for private variables
    void setPosition(QString );
    QString getPosition();
    void setPicture(QString path);
    QString getPicture();

    // this method deletes the picture of a particular piece
    void clearPicture();

protected:
    // once the mouse is pressed, sendPosition will be executed
    void mousePressEvent(QGraphicsSceneMouseEvent *e);

signals:
    // send the position of a clicked Square to the game function
    QString sendPosition(QString position);
};

#endif // SQUARE_H
