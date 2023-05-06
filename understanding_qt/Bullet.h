#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>

// slot is a reaction to a certain signal!!
// slot is a regular member function but you have to put it under public slots!! instead of just public
// ANY CLASS THAT USES SIGNALS AND SLOTS HAS TO DERIVE FROM QOBJECT!!

class Bullet: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Bullet();
public slots:
    void move();
};



#endif // BULLET_H
