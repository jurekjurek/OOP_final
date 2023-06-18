#include "space.h"

// Everytime we construct an instance of Space we assign a certain X and Y coordinate to it
Space::Space(int x, int y)
{
    xCoord = x;
    yCoord = y;
//    setFlag(QGraphicsItem::ItemIsFocusable);
//    setFocus();
    piece.setParentItem(this);
}

// When clicked, space name is sent to Display slot
void Space::mousePressEvent(QGraphicsSceneMouseEvent *ev){
    if(ev->buttons() == Qt::LeftButton){
        qDebug() << "You clicked " << name;
        this->setBrush(Qt::red);
    }
    // this sendSignal command directly gets transfered to the game
    emit sendSignal(name);
}

void Space::setName(QString n){
    name = n;
}

QString Space::getName(){
    return name;
}

void Space::setImage(QString path)
{
    image = path;
    piece.setPixmap(path);
    piece.setPos(xCoord, yCoord);
    piece.show();
}

QString Space::getImage()
{
    return image;

}
void Space::clearImage()
{
    piece.hide();
}
