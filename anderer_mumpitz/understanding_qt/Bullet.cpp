#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>


Bullet::Bullet() {
    // we just create the bullet, draw the rect
    setRect(0,0, 10, 50);

    // connect
    QTimer * timer = new QTimer();
    // object whose slot we want connected = this
    // connects timeout function of the timer to the move slot of the bullet, every this much time the move function will be called
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // every 50 milliseconds its timeout function will be emitted
    timer->start(50);
}

void Bullet::move() {
    // move bullet up
    setPos(this->x(), this->y() - 10);
    if (pos().y() + this->rect().height() < 0) {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Bullet deleted";
    }
}
