#include "square.h"

// Everytime we construct an instance of Square we assign a certain X and Y coordinate to it
Square::Square(int x, int y)
{
    this->X = x;
    this->Y = y;

    // establish the position of piece inside the Qt scene hierarchy.
    // Since this class (square) inherits from QGraphicsRectItem,
    // the item Square is one step above the item piece in the Qt hierarchy
    piece.setParentItem(this);
}

// When clicked, the position of this particular square on the board is sent to Game slot
void Square::mousePressEvent(QGraphicsSceneMouseEvent *ev){
    if(ev->buttons() == Qt::LeftButton){

        // when clicked, color the square red
        this->setBrush(Qt::red);
    }

    // this sendSignal command directly gets transfered to the game
    emit sendPosition(this->position);
}



void Square::setPosition(QString Position){
    this->position = Position;
}

QString Square::getPosition(){
    return this->position;
}

void Square::setPicture(QString path)
{
    // picture is a QString of a path to a picture
    this->picture = path;

    // the PixmapItem piece gets a picture assigned to it
    this->piece.setPixmap(path);

    // where to put the picture on the board?
    this->piece.setPos(this->X, this->Y);

    // show the picture to the respective scene
    this->piece.show();
}

QString Square::getPicture()
{
    return this->picture;

}
void Square::clearPicture()
{
    this->piece.hide();
}
