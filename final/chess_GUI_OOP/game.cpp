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

            ChessBoard Board_copy = this->Board;
            Position pos1_copy = pieceOne->getPos();
            Player* Current;
            Player* Other;



            Position pos1 = Position(pieceOne->getPos().getX(), pieceOne->getPos().getY());
//            Position pos2 = move.getLast();

            // get pieces in spot one and two
//            Piece* pieceOne = this->Board.getPiece(pos1);
            Piece* pieceTwo = this->Board.getPiece(pos2);

            if (pieceOne != nullptr and this->Whoseturn != pieceOne->getIswhite()) {
                this->error = WRONGCOLOR;
                return false;
            }


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

            // this is relevant only in the maketurn function because only here we have an actual game flow
            // we acutally have a player that is moving a piece
            // if the color of the current player is not equal to the color of the piece
//            if (manipulate and pieceOne != nullptr and this->Whoseturn != pieceOne->getIswhite()) {
//                this->error = WRONGCOLOR;
//                return false;
//            }

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

                this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->setIsalive(false);
                this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->setPos(Position(8,8));
                this->Board.setPiece(nullptr, Position(pos2.getX(), pos1.getY()));
            }

            // /////// //
            // CASTLES //
            // /////// //
            if (pieceOne->Piecetype() == KING and x1x2 == 2) {
                qDebug() << "IS THIS EXECUTED????? ";
                // in case white wants to castle
                // if the rooks are still on the board, otherwise programm collapses
//                if (Board.getPiece(Position(7,0)) == nullptr or Board.getPiece(Position(0,0)) == nullptr or  or Board.getPiece(Position(7,7)) == nullptr) {
//                    cout << "No rooks..." << endl;
//                    this->error = NOVALIDMOVE;
//                    return false;
//                }
                if (pieceOne->getIswhite() and pieceOne->getFirstmove()) {
                    // castles kingside
                    // if there is no piece in the way and if the king as well as the rook have not moved so far
                    if (x1 < x2 and Board.getPiece(Position(5,0)) == nullptr and Board.getPiece(Position(6,0)) == nullptr and Board.getPiece(Position(0,7)) != nullptr and Board.getPiece(Position(7,0))->getFirstmove()) {
                        if (!Attack(Position(5,0), Other) and !Attack(Position(6,0), Other) and !Attack(Position(7,0), Other)) {
                            qDebug() << "Castling Kingside, white.";
                            this->castlestate = WHITEKINGSIDE;
                            Piece* temprook = this->Board.getPiece(Position(7,0));
                            temprook->setPos(Position(5,0));
                            this->Board.setPiece(nullptr, Position(7,0));
                            this->Board.setPiece(temprook, Position(5,0));
//                            delete temprook;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }
                    // castles queenside
                    if (x1 > x2 and Board.getPiece(Position(1,0)) == nullptr and Board.getPiece(Position(2,0)) == nullptr and Board.getPiece(Position(3,0)) == nullptr and Board.getPiece(Position(0,0)) != nullptr and Board.getPiece(Position(0,0))->getFirstmove()) {
                        if (!Attack(Position(1,0), Other) and !Attack(Position(2,0), Other) and !Attack(Position(3,0), Other) and !Attack(Position(0,0), Other)) {
                            qDebug() << "Castling Queenside, white.";
                            this->castlestate = WHITEQUEENSIDE;
                            Piece* temprook = this->Board.getPiece(Position(0,0));
                            temprook->setPos(Position(3,0));
                            this->Board.setPiece(nullptr, Position(0,0));
                            this->Board.setPiece(temprook, Position(3,0));
//                            delete temprook;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }
                }

                // in case black wants to castle
                else if (!pieceOne->getIswhite() and pieceOne->getFirstmove()) {
                    // castles kingside
                    // if there is no piece in the way and if the king as well as the rook have not moved so far
                    if (x1 < x2 and Board.getPiece(Position(5,7)) == nullptr and Board.getPiece(Position(6,7)) == nullptr and Board.getPiece(Position(7,7)) != nullptr and Board.getPiece(Position(7,7))->getFirstmove()) {
                        if (!Attack(Position(5,7), Other) and !Attack(Position(6,7), Other)) {
                            qDebug() << "Castling Kingside, black.";
                            this->castlestate = BLACKKINGSIDE;
                            Piece* temprook = this->Board.getPiece(Position(7,7));
                            temprook->setPos(Position(5,7));
                            this->Board.setPiece(nullptr, Position(7,7));
                            this->Board.setPiece(temprook, Position(5,7));
//                            delete temprook;
                        }

                        // if one of the spots is attacked
                        else {cout << "this is the error hopefully" << endl; this->error = NOVALIDMOVE; return false;}
                    }
                    // castles queenside
                    if (x1 > x2 and Board.getPiece(Position(1,7)) == nullptr and Board.getPiece(Position(2,7)) == nullptr and Board.getPiece(Position(3,7)) == nullptr and Board.getPiece(Position(7,0)) != nullptr and Board.getPiece(Position(7,0))->getFirstmove()) {
                        if (!Attack(Position(1,7), Other) and !Attack(Position(2,7), Other) and !Attack(Position(3,7), Other)) {
                            qDebug() << "Castling Queenside, black.";
                            this->castlestate = BLACKQUEENSIDE;
                            Piece* temprook = this->Board.getPiece(Position(0,7));
                            temprook->setPos(Position(3,7));
                            this->Board.setPiece(nullptr, Position(0,7));
                            this->Board.setPiece(temprook, Position(3,7));
//                            delete temprook;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }
                }

                else {this->error = NOVALIDMOVE; return false;}

            }





            // THE  BOARD NOW ALSO GETS THE INFORMATION OF THE NEW POSITION OF PIECE ONE
            // the setpiece method of the board also tells the piece where it is on the board
            this->Board.setPiece(pieceOne, pos2);
            this->Board.setPiece(nullptr, pos1);

            // PIECE ONE GETS A NEW POSITION
//            pieceOne->setPos(pos2);


            // KINGUNSAFE

            // now, this move that we just made is only valid if our king (so the king of the current player) is still safe
            // so not in check
            bool kingUnSafe = Check(Other, Current);

            // if king is not safe -> abort
             if (kingUnSafe) {
                pieceOne->setPos(pos1);
                this->Board.setPiece(pieceOne, pos1);
                if (pieceTwo != nullptr) {
                    pieceTwo->setPos(pos2);
                    pieceTwo->setIsalive(true);

                    this->Board.setPiece(pieceTwo, pos2);
                }
                else {this->Board.setPiece(nullptr, pos2);}
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
            if (pieceOne->Piecetype() == PAWN and pos2.getY() == 7) {
                this->promotion(pos2, Current);
                this->Promotion = true;
            }

//            cout << "This is a test, where is the Queen of the current Player?? " << this->Current->getQueen()->getPos().getX() << " " << this->Current->getQueen()->getPos().getY() << endl;
//            cout << "This is a test, where is the Queen of the current Player?? " << this->White.getQueen()->getPos().getX() << " " << this->White.getQueen()->getPos().getY() << endl;

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

    // if there is no piece at spot one
    if (pieceOne == nullptr) {
        this->error = NOPIECE;
//        return false;
        movearray[0] = false;
        movearray[1] = false;
    }

//    // if the color of the current player is not equal to the color of the piece
//    if (this->Whoseturn != pieceOne->getIswhite()) {
//        this->error = WRONGCOLOR;
//        return false;
//    }

    // if piece at destination and piece at source have the same color
    // Only look at case of not Pawn, because for pawn pieceTwo != nullptr can be not allowed, independent of the color of piecetwo
    // Pawn can only hit diagonally
    if (pieceOne->Piecetype() != PAWN) {
        if (pieceTwo != nullptr and pieceTwo->getIswhite() == pieceOne->getIswhite()) {
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
        else if (pos1.getX() != pos2.getX() and pieceTwo != nullptr and pieceTwo->getIswhite() == pieceOne->getIswhite()) {
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

//// this function returns a list of alive pieces for the player with color color
//bool ChessGame::CanMove(Player * curr) {
//    // can the piece curr move to any position?
//    // player curr has a certain color, if he has the wrong color, the Maketurn function will return false
////    Board.getPiece(Position(->getPos()));
//    for (int i = 0; i<7; i++) {
//        for (int j = 0; j<7; j++) {
//            if (Checkmove(Move(curr->getPos(), Position(i,j)), curr) == true) {return true;}
//            else {return false;}
//        }
//    }

//}


bool ChessGame::CheckMate(Player* Current, Player* Other)  {
    // okay, so what we'll do here is create a copy of the board, manipulate this copy and look if certain moves can be made.
    // If they cannot be made, checkmate

    // only check for the case that current is checking other, because other can not be in check at this point
    if (!Check(Current, Other)) {return false;}
//    Position kingPos = Other->getKing()->getPos();
    vector<Piece*> AlivePieces = Other->getAlivePieces();

    bool attack = false;

    cout << "is this checkmate?" << endl;

    cout << "ThiSAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAASIDGKDFKGJK" << endl;
    // here maybe a lambda function to iterate over all possible positions the king can be in

//    if (Current->getQueen()->getPos().getX() == 7 and  Current->getQueen()->getPos().getY() == 4) {
//        cout << "Now" << endl;
//    }

    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            //if (Current->getQueen()->getPos().getX() == 6 and  Current->getQueen()->getPos().getY() == 7) {i = 6; j =5; cout << "now" << endl;}
                for (Piece* alivepiece : AlivePieces) {
                    if (Checkmove(Position(i,j), alivepiece)[0]) {
                        if (Current->getQueen()->getPos().getX() == 6 and  Current->getQueen()->getPos().getY() == 7 and i == 7 and j == 3) {
                            cout << "test" << endl;
                        }
                        bool ok = Maketurn(alivepiece, Position(i,j));
                        if (ok) {
//                            if (Current->getQueen()->getPos().getX() == 6 and  Current->getQueen()->getPos().getY() == 7) {
//                                cout << "test" << endl;
//                            }
                            cout << "" << endl;
                            return false;
                        }

                    }
                }
        }
    }
//    if (Current->getQueen()->getPos().getX() == 6 and  Current->getQueen()->getPos().getY() == 7) {
//        cout << "test" << endl;
//    }
    cout << "this is after the for loop" << endl;
    // otherwise, it is
    return false;
//    return true;

}


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





void ChessGame::promotion(Position pos, Player* Current)  {
//    int promotion_type;
    cout << "Your pawn can be promoted. Please provide the peace you want to promote to. Provide a number as follows: " << endl;
    cout << "Queen: 1" << endl << "Rook: 2" << endl << "Knight: 3" << endl << "Bishop: 4" << endl;
//    cin >> promotion_type;
//    switch (promotion_type) {
//    case 1:
//        Board.setPiece(Current->getQueen(), pos);
//    case 2:
//        Board.setPiece(Current->getRook(0), pos); // Board.setPiece(Current->getRook(this->promotion_count + 3), pos, current);
//    case 3:
//        Board.setPiece(Current->getKnight(0), pos);
//    case 4:
//        Board.setPiece(Current->getBishop(0), pos);
//    }
    // for now, only promote to a queen:
    Board.setPiece(Current->getQueen(), pos);
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





//         CHECKMATE
        bool gameOver = this->CheckMate(Current, Other);
        if (gameOver) {
            if (this->Whoseturn) {emit sendResponse("Checkmate."); return;}
            else {emit sendResponse("Checkmate. Black wins."); return;}
        }



        // DRAW
//        bool draw = this->StaleMate(current, other);
//        if (draw) {sendResponse("The game is drawn."); return;}
//        if (!draw) {sendResponse("No stalemate. The game goes on. ");}


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



        this->move_list.push_back(move.getFirst().getX());
        this->move_list.push_back(move.getFirst().getY());
        this->move_list.push_back(move.getLast().getX());
        this->move_list.push_back(move.getLast().getY());
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



