#include "MyRect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"

#include <QDebug>

void MyRect::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        setPos(x() - 10, y());
        qDebug() << "Move left!";
    }
    else if (event->key() == Qt::Key_Right) {
        setPos(x() + 10, y());
        qDebug() << "Move right!";
    }
    else if (event->key() == Qt::Key_Up) {
        setPos(x(), y() - 10);
        qDebug() << "Move up!";
    }
    else if (event->key() == Qt::Key_Down) {
        setPos(x(), y() + 10);
        qDebug() << "Move down!";
    }
    else if (event->key() == Qt::Key_Space) {
        // create a bullet pointer
        Bullet * bullet = new Bullet();
//        qDebug() << "Bullet created!";
        // now, lets add the bullet to the scene
        bullet->setPos(x(), y());
        scene()->addItem(bullet);
    }

    // now we want the rectangle to actually move
    // we want the bullet to be in the same scene that the MyRect is in


}



// Each QGraphicsItem has a pointer to the scene that it is in!!
