#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

class MyRect: public QGraphicsRectItem {
public:
    // this member function will allow the object MyRect to react when the key is being pressed
    void keyPressEvent(QKeyEvent * event);



};



#endif // MYRECT_H
