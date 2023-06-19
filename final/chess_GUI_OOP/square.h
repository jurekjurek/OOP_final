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



// Space inherits from QObject and QGrapphicsRectItem to handle signals and Slots and of course, A space is on the chessBoard just a Rectangle
class Square: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    // Every space has a name, which is his x and y coordinate in a QString
    QString position;
    // Every space carries a piece, which is an item in this Scene
    // The QGraphicsPixmapItem is an item that is especially suited for being shown as an Image on the screen!
    QGraphicsPixmapItem piece;
    // Every square on the board has a certain image of that piece
    QString image;
    // And every Square on the board has X and Y coordinates
    int X;
    int Y;
public:
    // constructor
    Square(int x, int y);

    void setPosition(QString );
    QString getPosition();
    void setImage(QString path);
    QString getImage();
    void clearImage();

protected:
    // once the mouse is pressed, sendPosition will be executed
    void mousePressEvent(QGraphicsSceneMouseEvent *e);

signals:
    QString sendPosition(QString position);
};

#endif // SQUARE_H
