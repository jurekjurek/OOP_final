#include "game.h"

// Chessgame has two players, Black and White. Black has color Black and White has color white
// Those two players are the players White and Black on the Chessboard
ChessGame::ChessGame() : Black(false), White(true), Board(&White, &Black) {
    this->Whoseturn = true;
//    this->White = &Board.getPlayerWhite();
//    this->Black = &Board.getPlayerBlack();
//    this->Board.setPlayerWhite(this->White);
//    this->Board.setPlayerBlack(this->Black);
}

// The maketurn function merely makes the move that was approved by the checkmove function
bool ChessGame::Maketurn(Piece* pieceOne, Position pos2) {

            if (pieceOne == nullptr) {
                this->error = NOPIECE;
                return false;
            }

//            ChessBoard Board_copy = this->Board;
//            Position pos1_copy = pieceOne->getPos();
            Player* Current;
            Player* Other;



            Position pos1 = Position(pieceOne->getPos().getX(), pieceOne->getPos().getY());
//            Position pos2 = move.getLast();

            // get pieces in spot one and two
//            Piece* pieceOne = this->Board.getPiece(pos1);
            Piece* pieceTwo = this->Board.getPiece(pos2);


            if (this->Whoseturn == true) {Current = Board.getPlayerWhite(); Other = Board.getPlayerBlack();}
            else {Other = Board.getPlayerWhite(); Current = Board.getPlayerBlack();}



            // for enpassant and castles later
            int x1 = pos1.getX();
            int x2 = pos2.getX();
            int y1 = pos1.getY();
            int y2 = pos2.getY();
            int x1x2 = abs(x1-x2);
            int y1y2 = abs(y1-y2);

            Move move = Move(pos1, pos2);

            // here, we want to know not if a certain piece can attack this spot, but if a given piece can move to this spot, so we choose [0]
            bool ok = this->Checkmove(pos2, pieceOne)[0];



            if (!ok) {qDebug() << "NO VALID MOVE"; return false;}

            if (this->Whoseturn != pieceOne->getColor()) {
                this->error = WRONGCOLOR;
                return false;
            }

            // THE MOVE HAS BEEN VALIDATED, GO ON TO CAPTURE THE PIECE IN DESTINATION SPOT AND MOVE THE PIECE

            //  if there is a piece at the second spot, kill it
            if (pieceTwo != nullptr) {
//                pieceTwo->setPos(Position(8,8));
                pieceTwo->setAlive(false);
//                Board.setPiece(nullptr, pos2, Current);
            }


            // if enpassant happened, kill the captured pawn
            if (this->enpassant)  {
                cout << "Position of the enpassanted piece: " << pos2.getX() << " " << pos1.getY() << endl;

                this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->setAlive(false);
                this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->setPos(Position(8,8));
                this->Board.setPiece(nullptr, Position(pos2.getX(), pos1.getY()));
            }

            // /////// //
            // CASTLES //
            // /////// //
            if (pieceOne->Piecetype() == KING and x1x2 == 2) {

                // WHITE and it has to be the Kings first move
                if (pieceOne->getColor() and pieceOne->getFirstmove()) {

                    // KINGSIDE, WHITE
                    if (x1 < x2 and Board.getPiece(Position(5,0)) == nullptr and Board.getPiece(Position(6,0)) == nullptr and Board.getPiece(Position(7,0)) != nullptr) {

                        // if the rook has already moved before
                        if (!Board.getPiece(Position(7,0))->getFirstmove() or Board.getPiece(Position(7,0))->Piecetype() != ROOK) {
                            this->error = NOVALIDMOVE;
                            return false;
                        }

                        // The king cannot be attacked, neither can the squares the king is moving over
                        if (!Attack(Position(4,0), Other) and !Attack(Position(5,0), Other) and !Attack(Position(6,0), Other)) {
                            qDebug() << "Castling Kingside, white.";
                            this->castlestate = WHITEKINGSIDE;

                            // change position of rook and king
                            this->Board.getPiece(Position(7,0))->setPos(Position(5,0));
                            this->Board.getPiece(Position(4,0))->setPos(Position(6,0));

                            // change position of rook and king on the board
                            this->Board.setPiece(this->Board.getPiece(Position(7,0)), Position(5,0));
                            this->Board.setPiece(this->Board.getPiece(Position(4,0)), Position(6,0));
                            this->Board.setPiece(nullptr, Position(7,0));
                            this->Board.setPiece(nullptr, Position(4,0));

                            // immediately return true, we don't have to check anything else. We know that the king is not in check, since
                            // neither of the squares the king moved over or is in can be attacked by the other player, as ensured above
                            return true;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }

                    // QUEENSIDE, WHITE
                    if (x1 > x2 and Board.getPiece(Position(1,0)) == nullptr and Board.getPiece(Position(2,0)) == nullptr and Board.getPiece(Position(3,0)) == nullptr and Board.getPiece(Position(0,0)) != nullptr) {

                        // If the rook has moved before
                        if (!Board.getPiece(Position(0,0))->getFirstmove() or Board.getPiece(Position(0,0))->Piecetype() != ROOK) {
                            this->error = NOVALIDMOVE;
                            return false;
                        }

                        // If the king is not in check and the squares the king is going to move over are not attacked:
                        if (!Attack(Position(1,0), Other) and !Attack(Position(2,0), Other) and !Attack(Position(3,0), Other) and !Attack(Position(4,0), Other)) {
                            qDebug() << "Castling Queenside, white.";
                            this->castlestate = WHITEQUEENSIDE;

                            // change position of rook and king
                            this->Board.getPiece(Position(0,0))->setPos(Position(3,0));
                            this->Board.getPiece(Position(4,0))->setPos(Position(2,0));

                            // change position of rook and king on the board
                            this->Board.setPiece(this->Board.getPiece(Position(0,0)), Position(3,0));
                            this->Board.setPiece(this->Board.getPiece(Position(4,0)), Position(2,0));
                            this->Board.setPiece(nullptr, Position(0,0));
                            this->Board.setPiece(nullptr, Position(0,0));

                            // immediately return true
                            return true;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }
                } // white over

                // BLACK and it has to be the Kings first move
                else if (!pieceOne->getColor() and pieceOne->getFirstmove()) {

                    // KINGSIDE, BLACK
                    if (x1 < x2 and Board.getPiece(Position(5,7)) == nullptr and Board.getPiece(Position(6,7)) == nullptr and Board.getPiece(Position(7,7)) != nullptr) {

                        // if the rook has already moved before
                        if (!Board.getPiece(Position(7,7))->getFirstmove() or Board.getPiece(Position(7,7))->Piecetype() != ROOK) {
                            this->error = NOVALIDMOVE;
                            return false;
                        }

                        // The king cannot be attacked, neither can the squares the king is moving over
                        if (!Attack(Position(4,7), Other) and !Attack(Position(5,7), Other) and !Attack(Position(6,7), Other)) {
                            qDebug() << "Castling Kingside, white.";
                            this->castlestate = BLACKKINGSIDE;

                            // change position of rook and king
                            this->Board.getPiece(Position(7,7))->setPos(Position(5,7));
                            this->Board.getPiece(Position(4,7))->setPos(Position(6,7));

                            // change position of rook and king on the board
                            this->Board.setPiece(this->Board.getPiece(Position(7,7)), Position(5,7));
                            this->Board.setPiece(this->Board.getPiece(Position(4,7)), Position(6,7));
                            this->Board.setPiece(nullptr, Position(7,7));
                            this->Board.setPiece(nullptr, Position(4,7));

                            // immediately return true, we don't have to check anything else. We know that the king is not in check, since
                            // neither of the squares the king moved over or is in can be attacked by the other player, as ensured above
                            return true;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }

                    // QUEENSIDE, BLACK
                    if (x1 > x2 and Board.getPiece(Position(1,7)) == nullptr and Board.getPiece(Position(2,7)) == nullptr and Board.getPiece(Position(3,7)) == nullptr and Board.getPiece(Position(0,7)) != nullptr) {

                        // If the rook has moved before
                        if (!Board.getPiece(Position(0,7))->getFirstmove() or Board.getPiece(Position(0,7))->Piecetype() != ROOK) {
                            this->error = NOVALIDMOVE;
                            return false;
                        }

                        // If the king is not in check and the squares the king is going to move over are not attacked:
                        if (!Attack(Position(1,7), Other) and !Attack(Position(2,7), Other) and !Attack(Position(3,7), Other) and !Attack(Position(4,7), Other)) {
                            qDebug() << "Castling Queenside, white.";
                            this->castlestate = BLACKQUEENSIDE;

                            // change position of rook and king
                            this->Board.getPiece(Position(0,7))->setPos(Position(3,7));
                            this->Board.getPiece(Position(4,7))->setPos(Position(2,7));

                            // change position of rook and king on the board
                            this->Board.setPiece(this->Board.getPiece(Position(0,7)), Position(3,7));
                            this->Board.setPiece(this->Board.getPiece(Position(4,7)), Position(2,7));
                            this->Board.setPiece(nullptr, Position(0,7));
                            this->Board.setPiece(nullptr, Position(0,7));

                            // immediately return true
                            return true;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }
                } // black over
                else {
                        this->error = NOVALIDMOVE;
                        return false;
                    }

            }





            // THE  BOARD NOW ALSO GETS THE INFORMATION OF THE NEW POSITION OF PIECE ONE
            // the setpiece method of the board also tells the piece where it is on the board
            this->Board.setPiece(pieceOne, pos2);
            this->Board.setPiece(nullptr, pos1);

            pieceOne->setPos(pos2);


            // KINGUNSAFE

            // now, this move that we just made is only valid if our king (so the king of the current player) is still safe
            // so not in check
            bool kingUnSafe = Check(Other, Current);

            // if king is not safe -> abort
             if (kingUnSafe) {
                pieceOne->setPos(pos1);
                this->Board.setPiece(pieceOne, pos1);
                if (pieceTwo != nullptr) {
//                    pieceTwo->setPos(pos2);
                    pieceTwo->setAlive(true);

                    this->Board.setPiece(pieceTwo, pos2);
                }
                else {
                    this->Board.setPiece(nullptr, pos2);
                }
                this->error = KINGUNSAFE;
                return false;
            }



            // in the case of Rook, Pawn and King it is important to know for specific rules if the piece has moved before (castling, movement of pawn, enpassant)
            pieceOne->setFirstmove(false);


            // set enpassant to false for all pieces on the board
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
//                    cout << i << " " << j << endl;
                    if (Board.getPiece(Position(i,j)) != nullptr) {Board.getPiece(Position(i,j))->setEnPassant(false);}
                }
            }


            // important: if the piece was a pawn, we set its enpassant to false
            if (pieceOne->Piecetype() == PAWN) {

//                pieceOne->setEnPassant(false);
                if (y1y2 == 2) {pieceOne->setEnPassant(true);}
            }
    //            this->Board = Board;

            // check if Pawn can be promoted
            if (pieceOne->Piecetype() == PAWN and pos2.getY() == 7 or pieceOne->Piecetype() == PAWN and pos2.getY() == 0 ) {
                this->promotion(pos2, Current, "");
                this->Promotion = true;
            }

            Board.printBoard();
            return true;
}



// is a certain move valid for a Player curr given a certain constellation of the board?
// this function returns an array of two booleans, one stating if Pieceone can attack!! pos2, the other if it can move to pos2
bool* ChessGame::Checkmove(Position pos2, Piece* pieceOne) {

    Position pos1 = pieceOne->getPos();
//    Position pos2 = move.getLast();

    bool* movearray = new bool[2];
    // is this move allowed to make?
    movearray[0] = true;

    // vs. Can the piece attack this spot?
    // So, for the pawns, if the spot on the diagonal is empty, the pawn cannot move there, but is attacking the spot!
    movearray[1] = true;

    // MAKE A LAMBDA FUNCTION OUT OF THIS
    int x1 = pos1.getX();
    int x2 = pos2.getX();
    int y1 = pos1.getY();
    int y2 = pos2.getY();
    int x1x2 = abs(x1-x2);
    int y1y2 = abs(y1-y2);

    // if either start or destination position is not valid -> error
    if (!pos1.getValid() or !pos1.getValid()) {
        this->error = NOVALIDPOS;
//        return false;
        movearray[0] = false;
        movearray[1] = false;
    }

    // get pieces in spot one and two
//    Piece* pieceOne = this->Board.getPiece(pos1);
    Piece* pieceTwo = this->Board.getPiece(pos2);

//    // if there is no piece at spot one
//    if (pieceOne == nullptr) {
//        this->error = NOPIECE;
////        return false;
//        movearray[0] = false;
//        movearray[1] = false;
//    }

//    // if the color of the current player is not equal to the color of the piece
//    if (this->Whoseturn != pieceOne->getIswhite()) {
//        this->error = WRONGCOLOR;
//        return false;
//    }

    // if piece at destination and piece at source have the same color
    // Only look at case of not Pawn, because for pawn pieceTwo != nullptr can be not allowed, independent of the color of piecetwo
    // Pawn can only hit diagonally
    if (pieceOne->Piecetype() != PAWN) {
        if (pieceTwo != nullptr and pieceTwo->getColor() == pieceOne->getColor()) {
            this->error = SPOTBLOCKED;
//            return false;
            movearray[0] = false;
            movearray[1] = false;
        }
    }

    // all of the obvious cases have been looked at, now to look at the specific rules for the pieces
    // Is it allowed for the piece at pos1 to move to pos2?
    bool checkMove = pieceOne->move_valid(pos2);

    // if the move is not valid -> exit
    if (!checkMove) {
        this->error = NOVALIDMOVE;
//        return false;
        movearray[0] = false;
        movearray[1] = false;
    }

    // EXTRA RULES FOR PAWN - HITTING DIAGONALLY, ENPASSANT

    if (pieceOne->Piecetype() == PAWN) {
        // if the pawn moves diagonally and there's no piece on that spot, it is not allowed.
        // only if there is a pawn next to it which has the same Y coordinate as he does, its allowed
        // and the same x coord of the final position
        if (pos1.getX() != pos2.getX() and pieceTwo == nullptr) {

            // Enpassant
            if (this->Board.getPiece(Position(pos2.getX(), pos1.getY())) != nullptr and this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->getEnPassant()) {
                qDebug() << "Enpassant!!";
                this->enpassant = true;
//                movearray[0] = true;
//                movearray[1] = true;
            }

            // All other cases not allowed
            else {
                this->error = NOVALIDMOVE;
//                return false;
                movearray[0] = false;
//                movearray[1] = true;
            }
        }
        // Pawn cannot hit in a straigt line, if theres a piece in front of the pawn, the pawn cannot move
        else if (pos1.getX() == pos2.getX()) {
            this->error = NOVALIDMOVE;
//            return false;

            // can never attack if not diagonal
            movearray[1] = false;
            if (pieceTwo != nullptr) {movearray[0] = false;}
        }

        // Pawn cannot hit pieces of its own color
        else if (pos1.getX() != pos2.getX() and pieceTwo != nullptr and pieceTwo->getColor() == pieceOne->getColor()) {
            this->error = NOVALIDMOVE;
//            return false;
            movearray[0] = false;
            movearray[1] = false;
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
            if (Board.getPiece(Position(min(x1,x2)+i , y1)) != nullptr) {freeway = false;}
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
            if (Board.getPiece(Position(x1+i , y1+i)) != nullptr) {freeway = false;}
        }
    }
    //  piece one on the upper right of piece two
    else if (x2<x1 and y2<y1) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x2+i , y2+i)) != nullptr) {freeway = false;}
        }
    }
    //  piece one on the lower right of piece two
    else if (x2<x1 and y1<y2) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x2+i , y2-i)) != nullptr) {freeway = false;}
        }
    }
    //  piece one on the upper left of piece two
    else if (x1<x2 and y2<y1) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x1+i , y1-i)) != nullptr) {freeway = false;}
        }
    }

    if (!freeway) {
        this->error = PIECEINWAY;
        movearray[0] = false;
        movearray[1] = false;
//        return false;
    }

    // if the piece is a king, moving two squares could be generally allowed (due to castles), *but* a king will never be able to attack this spot
    if (pieceOne->Piecetype() == KING and x1x2 == 2) {
        movearray[1] = false;
        movearray[0] = true;

    }

    return movearray;
}




// Does the Player Current attack the spot dest?
// In other words, can the player move a piece, that is NOT a pawn to that spot?
bool ChessGame::Attack(Position dest, Player* Current) {
//    qDebug() << "Attack function executed";
    vector<Piece*> AlivePieces = Current->getAlivePieces();

    bool attack = false;

    for (Piece* alivepiece : AlivePieces) {
        if (Checkmove(dest, alivepiece)[1]) {attack = true;}
    }
    return attack;
}



bool ChessGame::Check(Player* Current, Player* Other)  {
    Position kingPos = Other->getKing()->getPos();
    if (Attack(kingPos, Current)) {qDebug() << "CHECKKKKK"; return true;}
    else {
        return false;
    }
}


bool ChessGame::CheckMate(Player* Current, Player* Other)  {
    // okay, so what we'll do here is create a copy of the board, manipulate this copy and look if certain moves can be made.
    // If they cannot be made, checkmate

    // only check for the case that current is checking other, because other can not be in check at this point
    if (!Check(Current, Other)) {return false;}
    vector<Piece*> AlivePieces = Other->getAlivePieces();

    bool checkMate = true;

    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
                for (Piece* alivepiece : AlivePieces) {
                    Position alivepiece_pos = alivepiece->getPos();
                    if (Checkmove(Position(i,j), alivepiece)[0]) {


                        // if the piece is a king, the checkmove function will return true if the king moves two to the right or left
                        // because of castles. This is not a valid move.
                        if (alivepiece->Piecetype() == KING and abs(alivepiece->getPos().getX() - i) == 2) {
                            continue;
                        }

                        Piece* pieceTwo = this->Board.getPiece(Position(i,j));
                        if (pieceTwo != nullptr) {
                            pieceTwo->setAlive(false);
                        }
//                        Current->
                        // erase the space that the piece is in and put it to the other space
                        this->Board.setPiece(nullptr, alivepiece->getPos());
                        this->Board.setPiece(alivepiece, Position(i,j));
//                        alivepiece->setPos(Position(i,j));

                        if (!Check(Current, Other)) {
                            qDebug() << "In this Boardconstellation it is not checkmate apparently:";
                            Board.printBoard();
                            checkMate = false;
                        }



                        Board.setPiece(alivepiece, alivepiece_pos);

                        if (pieceTwo != nullptr) {
                            Board.setPiece(pieceTwo, Position(i,j));
                            pieceTwo->setAlive(true);
                        }
                        else {
                            Board.setPiece(nullptr, Position(i,j));
                        }
                    }
                }
        }
    }
    return checkMate;
//    return false;
}


bool ChessGame::StaleMate(Player* Current, Player *Other) {
    // If Current is checking other, it is not stalemate
    if (Check(Current, Other)) {return false;}
    vector<Piece*> AlivePieces = Other->getAlivePieces();

    bool draw = true;

    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
                for (Piece* alivepiece : AlivePieces) {
                    Position alivepiece_pos = alivepiece->getPos();
                    if (Checkmove(Position(i,j), alivepiece)[0]) {

                        Piece* pieceTwo = this->Board.getPiece(Position(i,j));
                        if (pieceTwo != nullptr) {
                            pieceTwo->setAlive(false);
                        }
//                        Current->
                        // erase the space that the piece is in and put it to the other space
                        this->Board.setPiece(nullptr, alivepiece->getPos());
                        this->Board.setPiece(alivepiece, Position(i,j));
//                        alivepiece->setPos(Position(i,j));

                        if (!Check(Current, Other)) {
                            draw = false;
                        }



                        Board.setPiece(alivepiece, alivepiece_pos);

                        if (pieceTwo != nullptr) {
                            Board.setPiece(pieceTwo, Position(i,j));
                            pieceTwo->setAlive(true);
                        }
                        else {
                            Board.setPiece(nullptr, Position(i,j));
                        }
                    }
                }
        }
    }
    return draw;

}
            // king is not attacked
            // but make_move does not work, because all of the fields are attacked
            // and the player can not move any other piece, so make_move does not work for any other piece either





void ChessGame::promotion(Position pos, Player* Current, QString inputstring)  {
    qDebug() << "PROMOTING!!! To a " << inputstring;
    std::string promotiontype = inputstring.toStdString();
    // set default to Queen

    if (promotiontype == "Knight") {
        Board.setPiece(Current->getKnight(2), pos);
//        Current->getKnight(2)->setPos(pos);
        Current->getKnight(2)->setAlive(true);
    }
    else if (promotiontype == "Bishop") {
        Board.setPiece(Current->getBishop(2), pos);
        Current->getBishop(2)->setAlive(true);
    }
    else if (promotiontype == "Rook") {
        Board.setPiece(Current->getRook(2), pos);
        Current->getRook(2)->setAlive(true);
    }
    else if (promotiontype == "Queen") {
        Board.setPiece(Current->getQueen(1), pos);
//        Current->getQueen(1)->setPos(pos);
        Board.getPiece(pos)->setPos(pos);
        Current->getQueen(1)->setAlive(true);
    }
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
    qDebug() << "String received from Display: " << input;

    // First, here: Handle promotions

    if (input == "Queen" or input == "Bishop" or input == "Knight" or input == "Rook") {
        int moves_played = move_list.size();
        Position promotionpos = Position(move_list[moves_played-2], move_list[moves_played-1]);
        if (this->Whoseturn) {
            this->promotion(promotionpos, this->Board.getPlayerBlack(), input);
        }
        else {
            this->promotion(promotionpos, this->Board.getPlayerWhite(), input);
        }
        Board.printBoard();
        std::string position_string_1 = std::to_string(move_list[moves_played-2]);
        std::string position_string_2 = std::to_string(move_list[moves_played-1]);

        const std::string sendstring = "P" + position_string_1 + position_string_2 + input.toStdString();
        QString qstr = QString::fromStdString(sendstring);

        sendResponse(qstr);

        // If either Player is checking either player, send Check to the display function
        if (this->Check(Board.getPlayerBlack(), Board.getPlayerWhite()) or this->Check(Board.getPlayerWhite(), Board.getPlayerBlack())) {
            sendResponse("Check");
        }
    }



    else if (move1 == "")
    {
        move1 = input.toStdString();
    }
    // If this is the second click, store it in move2
    else if (move2 == "")
    {
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

        Position pos1 = Position(x1,y1);
        Position pos2 = Position(x2,y2);

        if (pos1.getX() == 6 and pos1.getY() == 6) {
            cout << "test" << endl;
        }



        Piece* pieceOne = Board.getPiece(pos1);
//        this->White = Board.getPlayerWhite();
//        this->Black = Board.getPlayerBlack();


        Player* Current;
        Player* Other;
//        if (this->Whoseturn == true) {this->Current = this->White; this->Other = this->Black;}
//        else {this->Other = this->White; this->Current = this->Black;}
        if (this->Whoseturn == true) {Current = Board.getPlayerWhite(); Other = Board.getPlayerBlack();}
        else {Other = Board.getPlayerWhite(); Current = Board.getPlayerBlack();}
//        if (this->Whoseturn == true) {cout << "WHITEE" << endl; this->White = this->Current; this->Black = this->Other;}
//        else {cout << "BLACKK" << endl; this->White = this->Other; this->Black = this->Current;}

        if (Current->getRook(2)->getAlive()) {
            cout << "test" << endl;
        }


        // here, manipulate is true.


        bool ok = this->Maketurn(pieceOne, pos2);

        if (ok) {qDebug() << "Thank you. This is a valid move given the constellation of pieces on the board.";}

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












        // after white, it's black and after black, it's white.
        this->Whoseturn = !Whoseturn;

        cout << "TESTESTESTESTESTESTEST:::" << this->enpassant << this->Promotion << endl;

        // the provided move was valid. Tell the gui to show the move on the board.
        if (this->enpassant) {
            QString sendStr = "";
            QString part1 = QString::fromStdString(move1);
            QString part2 = QString::fromStdString(move2);
            sendStr += part1;
            sendStr += part2;
            QString part3 = ", Enpassant";
            sendStr += part3;
            emit sendResponse(sendStr);
        }

        else if (this->Promotion) {
            qDebug() << "There is a promotion happening.";
            QString sendStr = "";
            QString part1 = QString::fromStdString(move1);
            QString part2 = QString::fromStdString(move2);
            sendStr += part1;
            sendStr += part2;
            QString part3 = ", Promotion";
            sendStr += part3;
            emit sendResponse("Promotion");
            emit sendResponse(sendStr);
        }

        else if (this->castlestate == WHITEKINGSIDE) {emit sendResponse("Castle White Kingside");}
        else if (this->castlestate == WHITEQUEENSIDE) {emit sendResponse("Castle White Queenside");}
        else if (this->castlestate == BLACKKINGSIDE) {emit sendResponse("Castle Black Kingside");}
        else if (this->castlestate == BLACKQUEENSIDE) {emit sendResponse("Castle Black Queenside");}
        else {
            // Send QString response containing the two spaces of the valid move
            QString sendStr = "";
            QString part1 = QString::fromStdString(move1);
            QString part2 = QString::fromStdString(move2);
            sendStr += part1;
            sendStr += part2;
            emit sendResponse(sendStr);
        }

        // CHECK
        bool Checkstate = this->Check(Current, Other);
        if (Checkstate) {
            qDebug() << "CHECK!!!";
            QString sendcheck = "Check";
            emit sendResponse(sendcheck);
        }

        // We want to let the player know that they can choose a piece
//        if (this->Promotion) {
//            emit sendResponse("Promotion");
//        }


        //         DRAW
        bool draw = this->StaleMate(Current, Other);
        if (draw) {
            sendResponse("Draw");
            return;
        }
//        if (!draw) {
//            sendResponse("No stalemate. The game goes on. ");
//        }

        //         CHECKMATE
        bool gameOver = this->CheckMate(Current, Other);
        if (gameOver) {
            if (this->Whoseturn) {emit sendResponse("Checkmate"); resetMoves(); return;}
            else {emit sendResponse("Checkmate"); resetMoves(); return;}
        }



        this->move_list.push_back(move.getFrom().getX());
        this->move_list.push_back(move.getFrom().getY());
        this->move_list.push_back(move.getTo().getX());
        this->move_list.push_back(move.getTo().getY());
//        this->move_count += 1;

        // set enpassant to false again
        qDebug() << "We set enpassant to false again";
        this->enpassant = false;
        this->Promotion = false;

        this->castlestate = NOCASTLES;
        this->enpassant = false;

        resetMoves();
        this->Board.printBoard();
    }


}



