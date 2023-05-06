#include <QApplication>
#include <QGraphicsScene>
//#include <QGraphicsRectItem>              // we can replace this with the custom myrect
#include "MyRect.h"

#include <QGraphicsView>



/*
Most important things:
QGraphicsScene  put player, put tree, put whatever into a scene, Scene is kind of a map or a world
Only QGraphicsItems and its subclasses can go into a scene!
QGraphicsItem, only derive from it - QGraphicsRectItem
QGraphicsView is a widget used to visualize the scene

Important:
Event (mouse or key)


*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a scene

    QGraphicsScene * scene = new QGraphicsScene();

    // create item into the scene
    MyRect * player = new MyRect();
    player->setRect(0,0, 100, 100);

    // add item to the scene
    scene->addItem(player);

    // now alone, nothing happens if we press the key
    // we have to make the item focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    // and set the focus to rect
    player->setFocus();


    // to visualize the scene we have to add a view
    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // either initialize in constructor (above) or via method (below)
//    view->setScene(scene);

    view->show();
    view->setFixedSize(800,600);
    scene->setSceneRect(0,0, 800, 600);             // both view and scene should be 800 x 600 and should have their origin at 0,0

    player->setPos(view->width()/2, view->height() - player->rect().height() );

    return a.exec();
}
