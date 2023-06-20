#include "main_GUI.h"


GUI::GUI()
{

    // create the scene that the whole chessgame takes place in
    Scene_GUI = new QGraphicsScene();

    // setup the board, create the QT Layout
    initialize_interface();

    // Connect Game signal with with this GUI class
    // who is the sender? (What part of what QObject sends?) Game. What is the signal that Game sends? Always SIGNAL(actual signal)
    // who is the receiver? The function (slot) getResultingBoard in the GUI class.
    QObject::connect(&game, SIGNAL(sendResultingBoard(QString)), this, SLOT(getResultingBoard(QString)));

    // White goes first
    this->Color = true;
}

void GUI::initialize_interface() {
    int j = 100;
    bool green = true;
    for(int i=0; i<64; i++)
    {
        // spaces holds the names of the squares, get the first out of those spaces (07)
        QString pos = positions[i];
        // create an instance of Square(), for the first one Square(0,7)
        Square * square = new Square((i%8)*60, j);

        // Space inherits from QTRectangle(), so we set a rectangle of size 60x60 pixles with its upper left corner in the position (0,0) for all 64 squares
        square->setRect((i%8)*60, j, 60, 60);

        // Each of those squares gets a specific color
        // In every iteration of the for loop, black changes, besides on the rim. If we are on the rim, the same color gets repeated once.
        if (i % 8 == 0)
        {
            green = !green;
        }


        if (green)
        {
            square->setBrush(Qt::darkGreen);
        }
        green = !green;

        // we assign the position "07" to the particular space
        square->setPosition(pos);
        squares.append(square);

        // Here is where we add the Square to the scene!
        Scene_GUI->addItem(square);


        // We connect the space QObject, which sends signals via sendSignal
        // with the game QObject which gets this Input as a Qstring
        QObject::connect(square, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));

        // once we hit the last square of a particular row, increase j
        if ((i % 8) == 7)
        {
            j += 60;
        }
    }

    // textitem to indicate whose move it is
    QString toMove = "White to move";
    turn = new QGraphicsTextItem();
    turn->setPlainText(toMove);
    turn->setPos(10, 50);
    QFont font;
    font.setPointSize(13);
    turn->setFont(font);
    Scene_GUI->addItem(turn);

    // Is there an invalid move? Check? Checkmate? Stalemate?
    QString warning = "";
    alert = new QGraphicsTextItem();
    alert->setPlainText(warning);
    alert->setPos(150, 50);
    alert->setFont(font);
    alert->setDefaultTextColor(Qt::red);
    Scene_GUI->addItem(alert);


    // add promotion interface

    // four buttons with the pictures of four pieces
    // these buttons are instances of the class square as well, and they will be connected to the Game slot of the ChessGame class
    button1 = new Square(300, 600);
    button1->setRect(300,600,40,40);
    button1->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight_40px.png");
    button1->setPosition("Knight");

    button2 = new Square(350, 600);
    button2->setRect(350,600,40,40);
    button2->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook_40px.png");
    button2->setPosition("Rook");

    button3 = new Square(300, 650);
    button3->setRect(300,650,40,40);
    button3->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen_40px.png");
    button3->setPosition("Queen");

    button4 = new Square(350, 650);
    button4->setRect(350,650,40,40);
    button4->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop_40px.png");
    button4->setPosition("Bishop");

    // Textitem that tells the player to choose a piece
    QString choice = "Choose a piece";
    prom = new QGraphicsTextItem();
    prom->setPlainText(choice);
    prom->setPos(120, 630);
    prom->setFont(font);


    // placing the respective pieces on the squares
    // use the setPicture method from QGraphicsPixmapItem!!

    // pictures from https://github.com/EmmanuelleBouchard/chessGame/tree/master/Picture
    qDebug() << "Placing Pieces";
    squares[0]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
    squares[1]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
    squares[2]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
    squares[3]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_queen.png");
    squares[4]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_king.png");
    squares[5]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
    squares[6]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
    squares[7]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
    squares[8]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[9]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[10]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[11]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[12]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[13]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[14]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");
    squares[15]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_pawn.png");

    squares[48]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[49]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[50]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[51]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[52]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[53]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[54]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[55]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_pawn.png");
    squares[56]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");
    squares[57]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
    squares[58]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
    squares[59]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen.png");
    squares[60]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_king.png");
    squares[61]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
    squares[62]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
    squares[63]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");

}

void GUI::resetColor() {
    bool green = true;
    for(int i=0; i<64; i++)
    {

        // Each of those squares gets a specific color
        // In every iteration of the for loop, black changes, besides on the rim. If we are on the rim, the same color gets repeated once.
        if (i % 8 == 0)
        {
            green = !green;
        }

        if (!green) {
            squares[i]->setBrush(Qt::white);
        }

        if (green)
        {
            squares[i]->setBrush(Qt::darkGreen);
        }
        green = !green;

    }
}



QGraphicsScene* GUI::getScene()
{
    // Getscene for execution in main.cpp
    return Scene_GUI;
}

// Get a response from game.cpp and change the
// Pictures of pieces on the board appropriately
void GUI::getResultingBoard(QString response)
{

    // if there was a promotion the turn before, remove items
    if (button1->scene() != nullptr and button2->scene() != nullptr and button3->scene() != nullptr and button4->scene() != nullptr and prom->scene() != nullptr) {
        Scene_GUI->removeItem(button1);
        Scene_GUI->removeItem(button2);
        Scene_GUI->removeItem(button3);
        Scene_GUI->removeItem(button4);
        Scene_GUI->removeItem(prom);
    }
    // reset the alert text
    alert->setPlainText("");


    if (response == "Check")
    {
        alert->setPlainText("Check!");
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
        turn->setPlainText("Choose a piece to promote your pawn to!");
    }
    else if (response == "Draw")
    {
        qDebug() << "Draw!";
        alert->setPlainText("Stalemate!");
        resetColor();
        return;
    }


    // handle the signal we get back after promoting
    else if (response[0] == "P") {
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
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_queen.png");
                    }
                    if (response[3] == "B") {
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_bishop.png");
                    }
                    if (response[3] == "K") {
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_knight.png");
                    }
                    if (response[3] == "R") {
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/white_rook.png");
                    }
                }
                if (this->Color) {
                    if (response[3] == "Q") {
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_queen.png");
                    }
                    if (response[3] == "B") {
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_bishop.png");
                    }
                    if (response[3] == "K") {
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_knight.png");
                    }
                    if (response[3] == "R") {
                        squares[i]->setPicture("C:/Users/Jurekk/Documents/Brussels/Uni/sem_2/OOP/pics_/black_rook.png");
                    }
                }

            }
        }

    }

    // Otherwise (if there was no promotion or warning), use the response from Game to move the correct pieces
    else
    {
        // Handle Castles
        if (response == "Castle White, Kingside") {
            QString tempKing = squares[60]->getPicture();
            squares[60]->clearPicture();
            QString tempRook = squares[63]->getPicture();
            squares[63]->clearPicture();

            squares[62]->setPicture(tempKing);
            squares[61]->setPicture(tempRook);
        }
        else if (response == "Castle White, Queenside") {
            QString tempKing = squares[60]->getPicture();
            squares[60]->clearPicture();
            QString tempRook = squares[56]->getPicture();
            squares[56]->clearPicture();

            squares[58]->setPicture(tempKing);
            squares[59]->setPicture(tempRook);
        }
        else if (response == "Castle Black, Kingside") {
            QString tempKing = squares[4]->getPicture();
            squares[4]->clearPicture();
            QString tempRook = squares[7]->getPicture();
            squares[7]->clearPicture();

            squares[6]->setPicture(tempKing);
            squares[5]->setPicture(tempRook);
        }
        else if (response == "Castle Black, Queenside") {
            QString tempKing = squares[4]->getPicture();
            squares[4]->clearPicture();
            QString tempRook = squares[0]->getPicture();
            squares[0]->clearPicture();

            squares[2]->setPicture(tempKing);
            squares[3]->setPicture(tempRook);
        }

        // if it was a 'normal' move
        else {
            QString Pos1 = "";
            QString Pos2 = "";
            Pos1 += response[0];
            Pos1 += response[1];
            Pos2 += response[2];
            Pos2 += response[3];

            // to save the moving piece
            QString temp_piece;
            for (int i=0; i<squares.length(); i++ )
            {
                // if we have found the space corresponding to a certain position
                if (squares[i]->getPosition() == Pos1)
                {
                    // we clear the Picture of the piece that is moved
                    // temp_piece is just a string that holds the path to the Picture
                    temp_piece = squares[i]->getPicture();
                    squares[i]->clearPicture();
                }
            }
            for (int i=0; i<squares.length(); i++ )
            {
                if (squares[i]->getPosition() == Pos2)
                {
                    // and we set that Picture of the piece we removed from the first square to the second square!
                    squares[i]->setPicture(temp_piece);
                }
            }

            // check if enpassant. If so, we have to delete the picture that is stored on the square next to the initial pawn
            if (response[6] == "E") {
                QString Enpassantsquare = "";
                // the enpassant space, so the space of the piece that is going to be erased from the board is the x component of the second square (response(2)) and the y component of the first square (response[1])
                Enpassantsquare += response[2];
                Enpassantsquare += response[1];
                for (int i=0; i<squares.length(); i++ )
                {
                    if (squares[i]->getPosition() == Enpassantsquare)
                    {
                        squares[i]->clearPicture();
                    }
                }
            }

            // If there is a promotion on the board, so a pawn that hit either the 0th or the 7th rank, indicated by the string having a "Promotion" part
            if (response[6] == "P") {

                // add promotion interface (defined in the constructor) to the scene
                Scene_GUI->addItem(button1);

                Scene_GUI->addItem(button2);

                Scene_GUI->addItem(button3);

                Scene_GUI->addItem(button4);

                Scene_GUI->addItem(prom);

                // connect the buttons to the game function, so the game function can promote accordingly
                QObject::connect(button1, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));
                QObject::connect(button2, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));
                QObject::connect(button3, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));
                QObject::connect(button4, SIGNAL(sendPosition(QString)), &game, SLOT(Game(QString)));
            }

        }



        // after each turn, we reset the colors. Every time a square is clicked, it turns red, so we clean that up
        resetColor();

        // If we set a promoted piece, we are only promoting, its not a real move, so if we set a piece due to promotion, the colors do not switch
        if (response[0] != "P" and response != "Promotion" and response != "Check") {
            this->Color = !Color;
            if (this->Color == 0) {
                turn->setPlainText("Black to move");
            }
            else {
                turn->setPlainText("White to move");
            }
        }
    }

}
