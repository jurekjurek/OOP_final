#include "display.h"


Display::Display()
{
    // Connect Game signal with Display slot
    // who is the sender? (What part of what QObject sends?) Game. What is the signal that Game sends? Always SIGNAL(actual signal)
    // who is the receiver? This displayclass. The slot is the getresonse function of the display class
    QObject::connect(&game, SIGNAL(sendResponse(QString)), this, SLOT(getResponse(QString)));

    // create the scene that the whole chessgame takes place in
    DisplayScene = new QGraphicsScene();

    // setup the board, create the QT Layout
    setup();

    // Place the pictures of the pieces on the respective Squares
    placePieces();

    // White goes first
    turnColor = WHITE;
}

void Display::setup()
{
    int j = 0;
    int k = 0;
    bool black = true;
    for(int i=0; i<64; i++)
    {
        // spaces holds the names of the squares, get the first out of those spaces (07)
        QString spacename = spaces[i];
        // create an instance of Space(), for the first one Space(0,7)
        Space * s = new Space(j,k);
        // Space derives from QTRectangle(), so we set a rectangle of size 60x60 pixles with its upper left corner in the position (0,0) for all 64 Squares
        s->setRect(j,k,60,60); //x loc, y loc, width, height

        // Each of those squares gets a specific color
        // In every iteration of the for loop, black changes, besides on the rim. If we are on the rim, the same color gets repeated once.
        if (i % 8 == 0)
        {
            black = !black;
        }

        if (black)
        {
            s->setBrush(Qt::darkGreen);
        }
        black = !black;

        // we assign the name "07" to the particular space
        s->setName(spacename);
        spaceList.append(s);

        // Here is where we add the PixMapItem to the scene!
        DisplayScene->addItem(s);


        // We connect the space QObject, which sends signals via sendSignal
        // with the game QObject which gets this Input as a Qstring
        QObject::connect(s, SIGNAL(sendSignal(QString)), &game, SLOT(getInput(QString)));


        // Change this, easy
        j += 60;
        if (j == 480)
        {
            j = 0;
            k += 60;
        }
    }

//    QString matchText = "Good Luck!";
//    QGraphicsTextItem * match = new QGraphicsTextItem();
//    match->setPlainText(matchText);
//    match->setPos(500, 0);
//    DisplayScene->addItem(match);

    QString toMove = "White's turn";
    turn = new QGraphicsTextItem();
    turn->setPlainText(toMove);
    turn->setPos(500, 100);
    DisplayScene->addItem(turn);

    QString state = "";
    alert = new QGraphicsTextItem();
    alert->setPlainText(state);
    alert->setPos(500, 200);
    DisplayScene->addItem(alert);


    // add promotion interface
    button1 = new Space(500, 300);
    button1->setRect(500,300,40,40);
//    DisplayScene->addItem(button1);
    button1->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight_40px.png");
    button1->setName("Knight");

    button2 = new Space(550, 300);
    button2->setRect(550,300,40,40);
//    DisplayScene->addItem(button2);
    button2->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook_40px.png");
    button1->setName("Rook");

    button3 = new Space(500, 350);
    button3->setRect(500,350,40,40);
//    DisplayScene->addItem(button3);
    button3->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen_40px.png");
    button1->setName("Queen");

    button4 = new Space(550, 350);
    button4->setRect(550,350,40,40);
//    DisplayScene->addItem(button4);
    button4->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop_40px.png");
    button1->setName("Bishop");

}

void Display::resetColor() {
    int j = 0;
    int k = 0;
    bool black = true;
    for(int i=0; i<64; i++)
    {

        // Each of those squares gets a specific color
        // In every iteration of the for loop, black changes, besides on the rim. If we are on the rim, the same color gets repeated once.
        if (i % 8 == 0)
        {
            black = !black;
        }

        if (!black) {
            spaceList[i]->setBrush(Qt::white);
        }

        if (black)
        {
            spaceList[i]->setBrush(Qt::darkGreen);
        }
        black = !black;

        // Change this, easy
        j += 60;
        if (j == 480)
        {
            j = 0;
            k += 60;
        }
    }
}





void Display::placePieces()
{
    // use the setimage method from QGraphicsPixmapItem!!

    // pictures from https://github.com/EmmanuelleBouchard/chessGame/tree/master/image
    qDebug() << "Placing Pieces";
    spaceList[0]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
    spaceList[1]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
    spaceList[2]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
    spaceList[3]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_queen.png");
    spaceList[4]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_king.png");
    spaceList[5]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
    spaceList[6]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
    spaceList[7]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
    spaceList[8]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    spaceList[9]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    spaceList[10]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    spaceList[11]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    spaceList[12]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    spaceList[13]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    spaceList[14]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    spaceList[15]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");

    spaceList[48]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[49]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[50]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[51]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[52]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[53]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[54]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[55]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    spaceList[56]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");
    spaceList[57]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
    spaceList[58]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
    spaceList[59]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen.png");
    spaceList[60]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_king.png");
    spaceList[61]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
    spaceList[62]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
    spaceList[63]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");
}


QGraphicsScene* Display::getScene()
{
    // Getscene for execution in main.cpp
    return DisplayScene;
}

// Get a response from game.cpp and change the
// images of pieces on the board appropriately
void Display::getResponse(QString response)
{

    // if there was a promotion the turn before, remove items

    DisplayScene->removeItem(button1);
    DisplayScene->removeItem(button2);
    DisplayScene->removeItem(button3);
    DisplayScene->removeItem(button4);






    std::string responseString = response.toStdString();

    if (responseString == "Check")
    {
//        qDebug() << "qdebug in displayfct says: Check";
        alert->setPlainText("Check!");
    }
    else
    {
        alert->setPlainText("");
    }

    // If response was "Invalid Move", ignore it
    if (responseString.compare("Invalid Move") == 0)
    {
        qDebug() << "Invalid Move";
        alert->setPlainText("Not a valid move.");
        resetColor();
        return;
    }
    else if (responseString.compare("Checkmate") == 0)
    {
        qDebug() << "Checkmate!";
        alert->setPlainText("Checkmate!");
        resetColor();
        return;
    }
    else if (responseString.compare("Stalemate") == 0)
    {
        qDebug() << "Stalemate!";
        alert->setPlainText("Stalemate!");
        resetColor();
        return;
    }
    // Otherwise, use the response from Game to move the correct pieces
    else
    {
        qDebug() << "The response Game sent back was " << response;
        if (response == "Castle White Kingside")
        {
            QString tempKing = spaceList[60]->getImage();
            spaceList[60]->clearImage();
            QString tempRook = spaceList[63]->getImage();
            spaceList[63]->clearImage();

            spaceList[62]->setImage(tempKing);
            spaceList[61]->setImage(tempRook);
        } else if (response == "Castle White Queenside")
        {
            QString tempKing = spaceList[60]->getImage();
            spaceList[60]->clearImage();
            QString tempRook = spaceList[56]->getImage();
            spaceList[56]->clearImage();

            spaceList[58]->setImage(tempKing);
            spaceList[59]->setImage(tempRook);
        } else if (response == "Castle Black Kingside")
        {
            QString tempKing = spaceList[4]->getImage();
            spaceList[4]->clearImage();
            QString tempRook = spaceList[7]->getImage();
            spaceList[7]->clearImage();

            spaceList[6]->setImage(tempKing);
            spaceList[5]->setImage(tempRook);
        } else if (response == "Castle Black Queenside")
        {
            QString tempKing = spaceList[4]->getImage();
            spaceList[4]->clearImage();
            QString tempRook = spaceList[0]->getImage();
            spaceList[0]->clearImage();

            spaceList[2]->setImage(tempKing);
            spaceList[3]->setImage(tempRook);
        }

        else
        {
            QString firstSpace = "";
            QString secondSpace = "";
            firstSpace += response[0];
            firstSpace += response[1];
            secondSpace += response[2];
            secondSpace += response[3];

            QString temp;
            for (int i=0; i<spaceList.length(); i++ )
            {
                // if we have found the space corresponding to a certain position
                if (spaceList[i]->getName() == firstSpace)
                {
                    // we clear the image of the piece that is moved
                    // temp is just a string, so is image. Image is a Qstring holding the path of an image
                    temp = spaceList[i]->getImage();
                    spaceList[i]->clearImage();
                }
            }
            for (int i=0; i<spaceList.length(); i++ )
            {
                if (spaceList[i]->getName() == secondSpace)
                {
                    // and we set that image of the piece we removed from the first square to the second square!
                    spaceList[i]->setImage(temp);
                }
            }

            // check if enpassant, format 1111, Enpassant
            if (response[6] == "E") {
                QString Enpassantspace = "";
                // the enpassant space, so the space of the piece that is going to be erased from the board is the x component of the second square (response(2)) and the y component of the first square (response[1])
                Enpassantspace += response[2];
                Enpassantspace += response[1];
//                qDebug() << "The display function says: Enpassant is happening!";
                for (int i=0; i<spaceList.length(); i++ )
                {
                    if (spaceList[i]->getName() == Enpassantspace)
                    {
                        spaceList[i]->clearImage();
                    }
                }
            }

            // PPROMOTION

            if (response[6] == "P") {

                // add promotion interface
                DisplayScene->addItem(button1);

                DisplayScene->addItem(button2);

                DisplayScene->addItem(button3);

                DisplayScene->addItem(button4);

                QObject::connect(button1, SIGNAL(sendSignal(QString)), &game, SLOT(getInput(QString)));
                QObject::connect(button2, SIGNAL(sendSignal(QString)), &game, SLOT(getInput(QString)));
                QObject::connect(button3, SIGNAL(sendSignal(QString)), &game, SLOT(getInput(QString)));
                QObject::connect(button4, SIGNAL(sendSignal(QString)), &game, SLOT(getInput(QString)));

                QString Promotionspace = secondSpace;
                for (int i=0; i<spaceList.length(); i++ )
                {
                    if (spaceList[i]->getName() == Promotionspace)
                    {
                        if (turnColor == WHITE) {
                            spaceList[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen.png");
                        }
                        else {
                            spaceList[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_queen.png");
                        }
                    }
                }
            }

        }




        resetColor();

        if (turnColor == WHITE)
        {
            qDebug() << "Switching turncolor to BLACK";
            this->turnColor = BLACK;
            turn->setPlainText("Black to move");
        }
        else if (turnColor == BLACK)
        {
            qDebug() << "Switching turncolor to WHITE";
            turnColor = WHITE;
            turn->setPlainText("White to move");
        }
    }

}
