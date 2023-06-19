#include "main_GUI.h"


Display::Display()
{
    // Connect Game signal with Display slot
    // who is the sender? (What part of what QObject sends?) Game. What is the signal that Game sends? Always SIGNAL(actual signal)
    // who is the receiver? This displayclass. The slot is the getresonse function of the display class
    QObject::connect(&game, SIGNAL(sendResultingBoard(QString)), this, SLOT(getResultingBoard(QString)));

    // create the scene that the whole chessgame takes place in
    DisplayScene = new QGraphicsScene();

    // setup the board, create the QT Layout
    setup();

    // Place the pictures of the pieces on the respective squares
    placePieces();

    // White goes first
    this->Color = true;
}

void Display::setup()
{
    int j = 0;
    int k = 100;
    bool black = true;
    for(int i=0; i<64; i++)
    {
        // spaces holds the names of the squares, get the first out of those spaces (07)
        QString spacename = positions[i];
        // create an instance of Space(), for the first one Space(0,7)
        Square * s = new Square(j,k);
        // Space derives from QTRectangle(), so we set a rectangle of size 60x60 pixles with its upper left corner in the position (0,0) for all 64 squares
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
        s->setPosition(spacename);
        squares.append(s);

        // Here is where we add the PixMapItem to the scene!
        DisplayScene->addItem(s);


        // We connect the space QObject, which sends signals via sendSignal
        // with the game QObject which gets this Input as a Qstring
        QObject::connect(s, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));


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

    QString toMove = "White to move";
    turn = new QGraphicsTextItem();
    turn->setPlainText(toMove);
    turn->setPos(10, 50);
    QFont font;
    font.setPointSize(13);
    turn->setFont(font);
    DisplayScene->addItem(turn);

    QString state = "";
    alert = new QGraphicsTextItem();
    alert->setPlainText(state);
    alert->setPos(150, 50);
    alert->setFont(font);
    alert->setDefaultTextColor(Qt::red);
    DisplayScene->addItem(alert);


    // add promotion interface
    button1 = new Square(300, 600);
    button1->setRect(300,600,40,40);
//    DisplayScene->addItem(button1);
    button1->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight_40px.png");
    button1->setPosition("Knight");

    button2 = new Square(350, 600);
    button2->setRect(350,600,40,40);
//    DisplayScene->addItem(button2);
    button2->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook_40px.png");
    button2->setPosition("Rook");

    button3 = new Square(300, 650);
    button3->setRect(300,650,40,40);
//    DisplayScene->addItem(button3);
    button3->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen_40px.png");
    button3->setPosition("Queen");

    button4 = new Square(350, 650);
    button4->setRect(350,650,40,40);
//    DisplayScene->addItem(button4);
    button4->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop_40px.png");
    button4->setPosition("Bishop");

    QString choice = "Choose a piece";
    prom = new QGraphicsTextItem();
    prom->setPlainText(choice);
    prom->setPos(120, 630);
    prom->setFont(font);
//    DisplayScene->addItem(prom);


//    QObject::connect(this, SIGNAL(itemDrop(QString)), &game, SLOT(getInput(QString)));


}

void Display::resetColor() {
    int j = 0;
    int k = 100;
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
            squares[i]->setBrush(Qt::white);
        }

        if (black)
        {
            squares[i]->setBrush(Qt::darkGreen);
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
    squares[0]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
    squares[1]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
    squares[2]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
    squares[3]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_queen.png");
    squares[4]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_king.png");
    squares[5]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
    squares[6]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
    squares[7]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
    squares[8]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[9]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[10]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[11]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[12]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[13]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[14]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[15]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");

    squares[48]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[49]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[50]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[51]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[52]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[53]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[54]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[55]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[56]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");
    squares[57]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
    squares[58]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
    squares[59]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen.png");
    squares[60]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_king.png");
    squares[61]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
    squares[62]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
    squares[63]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");
}


QGraphicsScene* Display::getScene()
{
    // Getscene for execution in main.cpp
    return DisplayScene;
}

// Get a response from game.cpp and change the
// images of pieces on the board appropriately
void Display::getResultingBoard(QString response)
{

    // if there was a promotion the turn before, remove items

    DisplayScene->removeItem(button1);
    DisplayScene->removeItem(button2);
    DisplayScene->removeItem(button3);
    DisplayScene->removeItem(button4);
    DisplayScene->removeItem(prom);



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
    if (response == "Invalid Move")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText("Not a valid move.");
        resetColor();
        return;
    }
    else if (response == "This piece has the wrong color.")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText(response);
        resetColor();
        return;
    }

    else if (response == "You have not selected a piece.")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText(response);
        resetColor();
        return;
    }

    else if (response == "There is a piece in the way.")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText(response);
        resetColor();
        return;
    }

    else if (response == "This spot is blocked.")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText(response);
        resetColor();
        return;
    }

    else if (response == "The Pawn can only hit diagonally.")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText(response);
        resetColor();
        return;
    }

    else if (response == "This is not a valid move for this piece.")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText(response);
        resetColor();
        return;
    }

    else if (response == "This move would leave your king in check.")
    {
        qDebug() << "Invalid Move";
        alert->setPlainText(response);
        resetColor();
        return;
    }

    else if (response == "Checkmate")
    {
        qDebug() << "Checkmate!";
        alert->setPlainText("Checkmate!");
        resetColor();
        return;
    }
    else if (response == "Promotion") {
        qDebug() << "KOmmt das an?";
        turn->setPlainText("Choose a piece to promote your pawn to!");
    }
    else if (responseString.compare("Draw") == 0)
    {
        qDebug() << "Draw!";
        alert->setPlainText("Draw!");
        resetColor();
        return;
    }


    // handle the signal we get back after promoting
    else if (response[0] == "P") {
        qDebug() << "Ist das executed?";
        QString secondSpace = "";
        secondSpace += response[1];
        secondSpace += response[2];


        for (int i=0; i<squares.length(); i++ )
        {
            // if we have found the space corresponding to a certain position
            if (squares[i]->getPosition() == secondSpace)
            {
                // If it's white to move that means that the turn before it was black to move.
                // We are promoting the piece of the player whose turn it is not!!
                if (!this->Color) {
                    if (response[3] == "Q") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen.png");
                    }
                    if (response[3] == "B") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
                    }
                    if (response[3] == "K") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
                    }
                    if (response[3] == "R") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");
                    }
                }
                if (this->Color) {
                    if (response[3] == "Q") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_queen.png");
                    }
                    if (response[3] == "B") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
                    }
                    if (response[3] == "K") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
                    }
                    if (response[3] == "R") {
                        squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
                    }
                }

            }
        }

    }

    // Otherwise, use the response from Game to move the correct pieces
    else
    {
        qDebug() << "The response Game sent back was " << response;
        if (response == "Castle White, Kingside")
        {
            QString tempKing = squares[60]->getImage();
            squares[60]->clearImage();
            QString tempRook = squares[63]->getImage();
            squares[63]->clearImage();

            squares[62]->setImage(tempKing);
            squares[61]->setImage(tempRook);
        } else if (response == "Castle White, Queenside")
        {
            QString tempKing = squares[60]->getImage();
            squares[60]->clearImage();
            QString tempRook = squares[56]->getImage();
            squares[56]->clearImage();

            squares[58]->setImage(tempKing);
            squares[59]->setImage(tempRook);
        } else if (response == "Castle Black, Kingside")
        {
            QString tempKing = squares[4]->getImage();
            squares[4]->clearImage();
            QString tempRook = squares[7]->getImage();
            squares[7]->clearImage();

            squares[6]->setImage(tempKing);
            squares[5]->setImage(tempRook);
        } else if (response == "Castle Black, Queenside")
        {
            QString tempKing = squares[4]->getImage();
            squares[4]->clearImage();
            QString tempRook = squares[0]->getImage();
            squares[0]->clearImage();

            squares[2]->setImage(tempKing);
            squares[3]->setImage(tempRook);
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
            for (int i=0; i<squares.length(); i++ )
            {
                // if we have found the space corresponding to a certain position
                if (squares[i]->getPosition() == firstSpace)
                {
                    // we clear the image of the piece that is moved
                    // temp is just a string, so is image. Image is a Qstring holding the path of an image
                    temp = squares[i]->getImage();
                    squares[i]->clearImage();
                }
            }
            for (int i=0; i<squares.length(); i++ )
            {
                if (squares[i]->getPosition() == secondSpace)
                {
                    // and we set that image of the piece we removed from the first square to the second square!
                    squares[i]->setImage(temp);
                }
            }

            // check if enpassant, format 1111, Enpassant
            if (response[6] == "E") {
                QString Enpassantspace = "";
                // the enpassant space, so the space of the piece that is going to be erased from the board is the x component of the second square (response(2)) and the y component of the first square (response[1])
                Enpassantspace += response[2];
                Enpassantspace += response[1];
//                qDebug() << "The display function says: Enpassant is happening!";
                for (int i=0; i<squares.length(); i++ )
                {
                    if (squares[i]->getPosition() == Enpassantspace)
                    {
                        squares[i]->clearImage();
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

                DisplayScene->addItem(prom);

                QObject::connect(button1, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));
                QObject::connect(button2, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));
                QObject::connect(button3, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));
                QObject::connect(button4, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));

//                QString Promotionspace = secondSpace;
//                for (int i=0; i<squares.length(); i++ )
//                {
//                    if (squares[i]->getName() == Promotionspace)
//                    {
//                        if (turnColor == WHITE) {
//                            squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen.png");
//                        }
//                        else {
//                            squares[i]->setImage("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_queen.png");
//                        }
//                    }
//                }
            }

        }




        resetColor();


        if (response[0] != "P" and response != "Promotion" and response != "Check") {
            this->Color = !Color;
            if (this->Color == 0) {
                turn->setPlainText("Black to move");
            }
            else {
                turn->setPlainText("White to move");
            }
        }

//        // If we set a promoted piece, we are only promoting, its not a real move, so if we set a piece due to promotion, the colors do not switch
//        if (this->Color and response[0] != "P" and response != "Promotion" and response != "Check")
//        {
//            qDebug() << "Switching turncolor to BLACK";
//            this->turnColor = BLACK;
//            turn->setPlainText("Black to move");
//        }
//        else if (turnColor == BLACK and response[0] != "P" and response != "Promotion" and response != "Check" )
//        {
//            qDebug() << "Switching turncolor to WHITE";
//            turnColor = WHITE;
//            turn->setPlainText("White to move");
//        }
    }

}
