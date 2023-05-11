#include "game.h"


ChessGame::ChessGame() : Black(false), White(true), Board(&White, &Black) {
    this->Whoseturn = true;
//    this->White = &Board.getPlayerWhite();
//    this->Black = &Board.getPlayerBlack();
//    this->Board.setPlayerWhite(this->White);
//    this->Board.setPlayerBlack(this->Black);
//    this->state = ACTIVE;
}

Player ChessGame::getPlayerWhite() {return this->White;}

Player ChessGame::getPlayerBlack() {return this->Black;}

bool ChessGame::Maketurn(Move move) {

            Position pos1 = move.getFirst();
            Position pos2 = move.getLast();

            // get pieces in spot one and two
            Piece* pieceOne = this->Board.getPiece(pos1);
            Piece* pieceTwo = this->Board.getPiece(pos2);

            // for enpassant later
            int y1 = pos1.getY();
            int y2 = pos2.getY();
            int y1y2 = abs(y1-y2);

            bool ok = this->Checkmove(move);

            if (!ok) {qDebug() << "NO VALID MOVE"; return false;}


            // THE MOVE HAS BEEN VALIDATED, GO ON TO CAPTURE THE PIECE IN DESTINATION SPOT AND MOVE THE PIECE

            //  if there is a piece at the second spot, kill it
            if (pieceTwo != nullptr) {
                pieceTwo->setPos(Position(8,8));
                pieceTwo->setIsalive(false);
//                Board.setPiece(nullptr, pos2, Current);
            }


            // if enpassant happened, kill the captured pawn
            if (this->enpassant)  {
                cout << "Position of the enpassanted piece: " << pos2.getX() << " " << pos1.getY() << endl;
                this->Board.setPiece(nullptr, Position(pos2.getX(), pos1.getY()), Other);
                this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->setIsalive(false);
                this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->setPos(Position(0,0));
            }



            // THE  BOARD NOW ALSO GETS THE INFORMATION OF THE NEW POSITION OF PIECE ONE

            // switched them, maybe that fixes it?
            this->Board.setPiece(pieceOne, pos2, Current);
            this->Board.setPiece(nullptr, pos1, Current);

            // PIECE ONE GETS A NEW POSITION
            pieceOne->setPos(pos2);


            // KINGUNSAFE

            // now, this move that we just made is only valid if our king (so the king of the current player) is still safe
            // so not in check
            bool kingStillSafe = !Check(this->Other, this->Current);

            // if king is not safe -> abort
            if (!kingStillSafe) {
                pieceOne->setPos(pos1);
                this->Board.setPiece(pieceOne, pos1, Current);
                if (pieceTwo != nullptr) {
                    pieceTwo->setPos(pos2);
                    pieceTwo->setIsalive(true);

                    // we have to provide the reference to a certain piece, not the piece itself
                    this->Board.setPiece(pieceTwo, pos2, Current);
                }
                else {this->Board.setPiece(nullptr, pos2, Current);}
                this->error = KINGUNSAFE;
                return false;
            }



            // in the case of Rook, Pawn and King it is important to know for specific rules if the piece has moved before (castling, movement of pawn, enpassant)
            pieceOne->setFirstmove(false);

            // important: if the piece was a pawn, we set its enpassant to false
            if (pieceOne->Piecetype() == PAWN) {

                pieceOne->setEnPassant(false);
                if (y1y2 == 2) {pieceOne->setEnPassant(true);}
            }
    //            this->Board = Board;

            // check if Pawn can be promoted
            if (pieceOne->Piecetype() == PAWN and pieceOne->getPromotion()) {
                this->promotion(pos2);
            }

            cout << "This is a test, where is the Queen of the current Player?? " << this->Current->getQueen()->getPos().getX() << " " << this->Current->getQueen()->getPos().getY() << endl;
            cout << "This is a test, where is the Queen of the current Player?? " << this->White.getQueen()->getPos().getX() << " " << this->White.getQueen()->getPos().getY() << endl;

            Board.printBoard();
            return true;
}




bool ChessGame::Checkmove(Move move) {
    Position pos1 = move.getFirst();
    Position pos2 = move.getLast();


    // MAKE A LAMBDA FUNCTION OUT OF THIS
    int x1 = pos1.getX();
    int x2 = pos2.getX();
    int y1 = pos1.getY();
    int y2 = pos2.getY();
    int x1x2 = abs(x1-x2);
    int y1y2 = abs(y1-y2);


    if (!pos1.getValid() or !pos1.getValid()) {this->error = NOVALIDPOS; return false;}

    // get pieces in spot one and two
    Piece* pieceOne = this->Board.getPiece(pos1);
    Piece* pieceTwo = this->Board.getPiece(pos2);

    if (pieceOne == nullptr) {
        this->error = NOPIECE;
        return false;
    }

    if (this->Current->getIswhite() != pieceOne->getIswhite()) {
        this->error = WRONGCOLOR;
        return false;
    }

    // if piece at destination and piece at source have the same color -> error
    if (pieceOne->Piecetype() != PAWN) {
        if (pieceTwo != nullptr and pieceTwo->getIswhite() == pieceOne->getIswhite()) {
            this->error = SPOTBLOCKED;
            return false;
        }
    }

    bool checkMove = pieceOne->move_valid(move.getLast());

    // if the move is not valid -> exit
    if (!checkMove) {
        this->error = NOVALIDMOVE;
        return false;
    }

    // EXTRA RULES FOR PAWN - HITTING DIAGONALLY, ENPASSANT

    if (pieceOne->Piecetype() == PAWN) {
        // if the pawn moves diagonally and there's no piece on that spot, it is not allowed.
        // only if there is a pawn next to it which has the same Y coordinate as he does, its allowed
        // and the same x coord of the final position
        if (pos1.getX() != pos2.getX() and pieceTwo == nullptr) {
            if (Board.getPiece(Position(pos2.getX(), pos1.getY()))->getEnPassant() != true) {
                this->error = NOVALIDMOVE;
                return false;
            }
        }
        else if (pos1.getX() == pos2.getX() and pieceTwo != nullptr) {
            this->error = NOVALIDMOVE;
            return false;
        }
    }



    //  PIECES IN WAY
    //  x1x2 and y1y2 are either equal or one is zero.
    bool freeway = true;
    if (x1x2 == 1 or y1y2 == 1) {freeway = true;}

    else if (pieceOne->Piecetype() == KNIGHT) {freeway = true;}

    //  ROOK OR QUEEN, MOVING IN STRAIGHT LINES
    //  pieces are on the same row
    else if (y1y2 == 0) {
        // starting at 2, since the case 1 is taken care of, there can be no piece at the destination square
        // and 0 also, a piece is not allowed to not move
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(min(x1,x2)+i , y1)) != nullptr) {cout << "Problem: Straight 1, " << "i" << endl; freeway = false;}
        }
    }
    //  pieces are on the same column
    else if (x1x2 == 0) {
        for (int i = 1; i < y1y2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x1 , min(y1,y2)+i)) != nullptr) {cout << "Problem: Straight 2, " << "i" << endl; freeway = false;}
        }
    }

    //  BISHOP AND QUEEN, MOVING DIAGONALLY
    //  distinguish four cases of the destination spot and source spot to each other
    //  piece one on the lower left of piece two
    else if (x1<x2 and y1<y2) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x1+i , y1+i)) != nullptr) {cout << "Problem: Diagonal 1, " << i << endl; freeway = false;}
        }
    }
    //  piece one on the upper right of piece two
    else if (x2<x1 and y2<y1) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x2+i , y2+i)) != nullptr) {cout << "Problem: Diagonal 2, " << i << endl; freeway = false;}
        }
    }
    //  piece one on the lower right of piece two
    else if (x2<x1 and y1<y2) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x2+i , y2-i)) != nullptr) {cout << "Problem: Diagonal 3, " << i << endl; freeway = false;}
        }
    }
    //  piece one on the upper left of piece two
    else if (x1<x2 and y2<y1) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x1+i , y1-i)) != nullptr) {cout << "Problem: Diagonal 4, " << i << endl; freeway = false;}
        }
    }

    if (!freeway) {
        this->error = PIECEINWAY;
        return false;
    }


    return true;
}



bool ChessGame::Attack(Position dest, Player* curr) {
//    qDebug() << "Attack function executed";
    bool attack = false;
    // when a piece is allowed to move. Look at all the potential attacking pieces.
//    cout << "Position of currents Queen: " << Current->getQueen()->getPos().getX() << " " << Current->getQueen()->getPos().getY() << endl;
//    cout << Maketurn(current, other, Move(Current->getQueen()->getPos(), Position(4,7))) << " Is this zero????" << endl;

    cout << "The destination position is: " << dest.getX() << " " << dest.getY() << endl;

    if (Checkmove(Move(curr->getKing()->getPos(), dest))) {qDebug() << "The other players King can attack this spot."; attack = true;}
    // can the queen attack the position dest?
    if (Checkmove(Move(curr->getQueen()->getPos(), dest))) {qDebug() << "The other players Queen can attack this spot."; attack = true;}
    // can either rook attack the position dest?
    if (Checkmove(Move(curr->getRook(0)->getPos(), dest))) {qDebug() << "The other players Rook can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getRook(1)->getPos(), dest))) {qDebug() << "The other players Rook can attack this spot."; attack = true;}
    // can either bishop attack the position dest?
    if (Checkmove(Move(curr->getBishop(0)->getPos(), dest))) {qDebug() << "The other players Bishop can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getBishop(1)->getPos(), dest))) {qDebug() << "The other players Bishop can attack this spot."; attack = true;}
    // can either knight attack the position dest?
    if (Checkmove(Move(curr->getKnight(0)->getPos(), dest))) {qDebug() << "The other players Knight can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getKnight(1)->getPos(), dest))) {qDebug() << "The other players Knight can attack this spot."; attack = true;}
    // can either pawn attack the position dest? Remember: the pawn is the only piece that has a special capturing direction
    if (Checkmove(Move(curr->getPawn(0)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getPawn(1)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getPawn(2)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getPawn(3)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getPawn(4)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getPawn(5)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getPawn(6)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}
    if (Checkmove(Move(curr->getPawn(7)->getPos(), dest))) {qDebug() << "The other players Pawn can attack this spot."; attack = true;}

    return attack;
}



bool ChessGame::Check(Player* curr, Player* oth)  {
    Position kingPos = oth->getKing()->getPos();
    if (Attack(kingPos, curr)) {qDebug() << "CHECKKKKK"; return true;}
    else {
        return false;
    }
}


bool ChessGame::CheckMate(Player* curr, Player* oth)  {
    // only check for the case that current is checking other, because other can not be in check at this point
    if (!Check(curr, oth)) {return false;}
    Position kingPos = oth->getKing()->getPos();

    // here maybe a lambda function to iterate over all possible positions the king can be in
    for (int i = -1; i<2; i++) {
        for (int j = -1; j<2; j++) {
            // if every spot around the king is either attacked or blocked by a piece of the same color
            // the getPiece method takes a pos
            // if one spot is NOT attacked and the spot is either free or a piece of the other color is on it, then it is not checkmate
            if (!Attack(kingPos.shiftPos(i, j), curr) and this->Board.getPiece(kingPos.shiftPos(i, j)) == nullptr ) {return false;}
            else if (!Attack(kingPos.shiftPos(i, j), curr) and this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == curr->getIswhite()) {return false;}
        }
    }
    return true;

}
    // if king is attacked
    // and make_move does not work for any spot for the king
    // and there is no piece that can move in front of the king


bool ChessGame::StaleMate() {
    //        if (Check(current, other)) {return false;}
    //        Position kingPos = Other->getKing()->getPos();
    //        // here maybe a lambda function to iterate over all possible positions the king can be in
    //        for (int i = -1; i<2; i++) {
    //            for (int j = -1; j<2; j++) {
    //                // if every spot around the king is either attacked or blocked by a piece of the same color
    //                // the getPiece method takes a pos
    ////                if (!Attack(current, kingPos.shiftPos(i, j)) or this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == Other->getIswhite() ) {return false;}
    //                if (!Attack(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j)) == nullptr ) {return false;}
    //                else if (!Attack(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == Current->getIswhite()) {return false;}
    //                // here, we have to iterate over the pieces on the board and see if any of them can move.
    //                else if (true) {return false;}
    //            }
    //        }
            return false;

        }
            // king is not attacked
            // but make_move does not work, because all of the fields are attacked
            // and the player can not move any other piece, so make_move does not work for any other piece either





void ChessGame::promotion(Position pos)  {
    int promotion_type;
    cout << "Your pawn can be promoted. Please provide the peace you want to promote to. Provide a number as follows: " << endl;
    cout << "Queen: 1" << endl << "Rook: 2" << endl << "Knight: 3" << endl << "Bishop: 4" << endl;
    cin >> promotion_type;
    switch (promotion_type) {
    case 1:
        Board.setPiece(this->Current->getQueen(), pos, Current);
    case 2:
        Board.setPiece(this->Current->getRook(0), pos, Current); // Board.setPiece(Current->getRook(this->promotion_count + 3), pos, current);
    case 3:
        Board.setPiece(this->Current->getKnight(0), pos, Current);
    case 4:
        Board.setPiece(this->Current->getBishop(0), pos, Current);
    }
    this->promotion_count += 1;
}




// Clear move1 and move2 strings
void ChessGame::resetMoves()
{
    move1 = "";
    move2 = "";
}



// This function is a Qt slot, a function designed to receive QObject signals.
// It receives a signal from the Display whenever a space is clicked. Upon collecting
// two spaces, the move can be executed if it is valid, or ignored if not.
void ChessGame::getInput(QString input)
{
//    this->move_count = 0;
    if (this->Whoseturn) {qDebug() << "White's move";}
    if (!this->Whoseturn) {qDebug() << "Blacks turn";}
//    qDebug() << "Game saw that " << input << "was clicked, and will now respond.";

    // If this is the first click, store it in move1
    if (move1 == "")
    {
//        qDebug() << "First position recognized.";
        move1 = input.toStdString();
    }
    // If this is the second click, store it in move2
    else
    {
//        qDebug() << "Second position recognized.";
        move2 = input.toStdString();

        // We can now pass the move to the Game
        int x1, y1, x2, y2;
        for (int i = 0; i < 8; i++) {
            if (move1[0] == '0') {x1 = 0;}
            if (move1[0] == '1') {x1 = 1;}
            if (move1[0] == '2') {x1 = 2;}
            if (move1[0] == '3') {x1 = 3;}
            if (move1[0] == '4') {x1 = 4;}
            if (move1[0] == '5') {x1 = 5;}
            if (move1[0] == '6') {x1 = 6;}
            if (move1[0] == '7') {x1 = 7;}
            if (move1[1] == '0') {y1 = 0;}
            if (move1[1] == '1') {y1 = 1;}
            if (move1[1] == '2') {y1 = 2;}
            if (move1[1] == '3') {y1 = 3;}
            if (move1[1] == '4') {y1 = 4;}
            if (move1[1] == '5') {y1 = 5;}
            if (move1[1] == '6') {y1 = 6;}
            if (move1[1] == '7') {y1 = 7;}

            if (move2[0] == '0') {x2 = 0;}
            if (move2[0] == '1') {x2 = 1;}
            if (move2[0] == '2') {x2 = 2;}
            if (move2[0] == '3') {x2 = 3;}
            if (move2[0] == '4') {x2 = 4;}
            if (move2[0] == '5') {x2 = 5;}
            if (move2[0] == '6') {x2 = 6;}
            if (move2[0] == '7') {x2 = 7;}
            if (move2[1] == '0') {y2 = 0;}
            if (move2[1] == '1') {y2 = 1;}
            if (move2[1] == '2') {y2 = 2;}
            if (move2[1] == '3') {y2 = 3;}
            if (move2[1] == '4') {y2 = 4;}
            if (move2[1] == '5') {y2 = 5;}
            if (move2[1] == '6') {y2 = 6;}
            if (move2[1] == '7') {y2 = 7;}
        }
        Move move(Position(x1,y1), Position(x2,y2));

//        this->White = Board.getPlayerWhite();
//        this->Black = Board.getPlayerBlack();

//        if (this->Whoseturn == true) {this->Current = this->White; this->Other = this->Black;}
//        else {this->Other = this->White; this->Current = this->Black;}
        if (this->Whoseturn == true) {this->Current = Board.getPlayerWhite(); this->Other = Board.getPlayerBlack();}
        else {this->Other = Board.getPlayerWhite(); this->Current = Board.getPlayerBlack();}
//        if (this->Whoseturn == true) {cout << "WHITEE" << endl; this->White = this->Current; this->Black = this->Other;}
//        else {cout << "BLACKK" << endl; this->White = this->Other; this->Black = this->Current;}




        // here, manipulate is true.
        bool ok = this->Maketurn(move);

        if (ok) {emit sendResponse("Thank you. This is a valid move given the constellation of pieces on the board.");}

        if (!ok) {
            if (this->error == NOVALIDPOS) {
                qDebug() << "You did not provide a valid position.";
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
            else if (this->error == NOPIECE) {
                qDebug() << "There is no piece at the spot you want to move from. ";
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
            else if (this->error == PIECEINWAY) {
                qDebug() << "There is a piece in the way and your piece cannot jump, since it is not a knight. ";
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
            else if (this->error == WRONGCOLOR) {
                qDebug() << "This piece has the wrong color.";
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
            else if (this->error == SPOTBLOCKED) {
                qDebug() << "The spot you are trying to move to is blocked by a piece of your color. ";
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
            else if (this->error == SPOTBLOCKED_PAWN) {
                qDebug() << "The spot you are trying to move to is blocked by a piece of your color. The Pawn can only hit diagonally. ";
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
            else if (this->error == NOVALIDMOVE) {
                qDebug() <<  "The move you provided is against the rules of moving for this piece. " ;
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
            else if (this->error == KINGUNSAFE) {
                qDebug() << "The move you are trying to make would leave your king in check. ";
                emit sendResponse("Invalid Move");
                resetMoves();
                return;
            }
        }

        // CHECK
        bool Checkstate = this->Check(this->Current, this->Other);
        if (Checkstate) {
            qDebug() << "CHECK!!!";
        }


        cout << "Test 4" << endl;
        cout << "Queens position of current player: " << this->Current->getQueen()->getPos().getX() << " " << this->Current->getQueen()->getPos().getY() << endl;
        cout << "Queens position of other player: " << this->Other->getQueen()->getPos().getX() << " " << this->Other->getQueen()->getPos().getY() << endl;




        // CHECKMATE
//        bool gameOver = this->CheckMate(current, other);
//        if (gameOver) {
//            if (this->Whoseturn) {state = WHITEWINS; sendResponse("Checkmate. White wins."); return;}
//            else {state = BLACKWINS; sendResponse("Checkmate. Black wins."); return;}
//        }



        // DRAW
//        bool draw = this->StaleMate(current, other);
//        if (draw) {sendResponse("The game is drawn."); return;}
//        if (!draw) {sendResponse("No stalemate. The game goes on. ");}


        // after white, it's black and after black, it's white.
        this->Whoseturn = !Whoseturn;


        // the provided move was valid. Tell the gui to show the move on the board.

        // Send QString response containing the two spaces of the valid move
        QString sendStr = "";
        QString part1 = QString::fromStdString(move1);
        QString part2 = QString::fromStdString(move2);
        sendStr += part1;
        sendStr += part2;
        sendResponse(sendStr);


        this->move_list.push_back(move.getFirst().getX());
        this->move_list.push_back(move.getFirst().getY());
        this->move_list.push_back(move.getLast().getX());
        this->move_list.push_back(move.getLast().getY());
        this->move_count += 1;

        // set enpassant to false again
        qDebug() << "We set enpassant to false again";
        this->enpassant = false;

        resetMoves();
    }

}



