#ifndef SPACE_H
#define SPACE_H

#include <QDebug>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QBrush>
#include <string>
#include <QGraphicsScene>



// Space inherits from QObject and QGrapphicsRectItem to handle signals and Slots and of course, A space is on the chessBoard just a Rectangle
class Space: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    // constructor
    Space(int x, int y);

    void setName(QString );
    QString getName();
    void setImage(QString path);
    QString getImage();
    void clearImage();

private:
    // Every space has a name, which is his x and y coordinate in a QString
    QString name;
    // Every space carries a piece, which is an item in this Scene
    // The QGraphicsPixmapItem is an item that is especially suited for being shown as an Image on the screen!
    QGraphicsPixmapItem piece;
    // Every space has a certain image of that piece
    QString image;
    // And every Space has X and Y coordinates
    int xCoord;
    int yCoord;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);

    // We want to connect the space to the Game
    // If we click on a certain space, the Game should get the information (x and y coordinate of the space )
    // and do something to it
signals:
    QString sendPosition(QString name);
};

#endif // SPACE_H
