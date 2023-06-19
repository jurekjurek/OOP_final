#include "square.h"

// Everytime we construct an instance of Square we assign a certain X and Y coordinate to it
Square::Square(int x, int y)
{
    this->X = x;
    this->Y = y;
    piece.setParentItem(this);
}

// When clicked, the position of this particular squere on the board is sent to Display slot
void Square::mousePressEvent(QGraphicsSceneMouseEvent *ev){
    if(ev->buttons() == Qt::LeftButton){
        qDebug() << "You clicked " << position;
        this->setBrush(Qt::red);
    }
    // this sendSignal command directly gets transfered to the game
    emit sendPosition(position);
}



void Square::setPosition(QString Position){
    this->position = Position;
}

QString Square::getPosition(){
    return position;
}

void Square::setImage(QString path)
{
    image = path;
    piece.setPixmap(path);
    piece.setPos(X, Y);
    piece.show();
}

QString Square::getImage()
{
    return image;

}
void Square::clearImage()
{
    piece.hide();
}
