#include "game.h"

// Initialize the Players with the respective colors and set up the board with these players
ChessGame::ChessGame() : Board() {

    // Upon initialization, it's whites turn
    this->Turn= true;
}

// This function actually sets pieces and deletes pieces on the chessboard. For this, it has to get the permission of the Checkmove function
// which checks if a certain move is allowed or not.
// The maketurn function gets called as soon as the two positions that were provided by the GUI are available
// This function takes as input a two positions, and moves the piece from position one to position two (if Castlestate == NOCASTLES) and capturing the appropriate pieces
bool ChessGame::Maketurn(Position pos1, Position pos2) {

            // get the pieces at the respective positions
            Piece* pieceOne = this->Board.getPiece(pos1);
            Piece* pieceTwo = this->Board.getPiece(pos2);

            // if there is no piece at the first position, the move is not valid
            // an appropriate error message is returned for every error
            // Different errors lead to different error messages in the GUI
            if (pieceOne == nullptr) {
                this->error = NOPIECE;
                return false;
            }

            // Declare Pointers to the two players, Current is the player whose turn it currently is and Other is the other player
            Player* Current;
            Player* Other;

            // if it is whites turn
            if (this->Turn == true) {
                Current = Board.getPlayerWhite();
                Other = Board.getPlayerBlack();
            }
            // if it is blacks turn
            else {
                Other = Board.getPlayerWhite();
                Current = Board.getPlayerBlack();
            }


//            Move move = Move(pos1, pos2);

            // here, we want to know not if a certain piece can attack this spot, but if a given piece can move to this spot, so we choose [0]
            bool ok = this->Checkmove(pos2, pieceOne)[0];



            if (!ok) {qDebug() << "NO VALID MOVE"; return false;}

            if (this->Turn!= pieceOne->getColor()) {
                this->error = WRONGCOLOR;
                return false;
            }





            // if enpassant happened, kill the captured pawn
            if (this->enpassant)  {

                // the position of the Pawn that is captured en passant is the x position of the second piece and the y position of the first piece
                // kill this piece and set a nullptr at the position
                this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->setAlive(false);
                this->Board.setPiece(nullptr, Position(pos2.getX(), pos1.getY()));
            }

            // /////// //
            // CASTLES //
            // /////// //

            // in order to reason about castles we have to know if the king moved two steps to the right or left
            int x1 = pos1.getX();
            int x2 = pos2.getX();
            int x1x2 = abs(x1-x2);

            // If the king moves two to the left or right, the player tries to castle
            if (pieceOne->Piecetype() == KING and x1x2 == 2) {

                // First case: white tries to castle
                // if the king has moved before, castles is not allowed anymore.
                if (pieceOne->getColor() and pieceOne->getFirstmove()) {
                    // there's two types of Castles a player can make. King- and queenside castle.

                    // First the Kingside castle. There can be no pieces between the rook and the king.
                    if (x1 < x2 and Board.getPiece(Position(5,0)) == nullptr and Board.getPiece(Position(6,0)) == nullptr and Board.getPiece(Position(7,0)) != nullptr) {

                        // if the rook has already moved before, castling is not allowed
                        if (!Board.getPiece(Position(7,0))->getFirstmove() or Board.getPiece(Position(7,0))->Piecetype() != ROOK) {
                            this->error = NOVALIDMOVE;
                            return false;
                        }

                        // The king cannot be attacked. None of the spots the king is going to move over or move to can be attacked by the other player
                        if (!Attack(Position(4,0), Other) and !Attack(Position(5,0), Other) and !Attack(Position(6,0), Other)) {

                            // We are allowed to castle kingside
                            qDebug() << "Castling Kingside, white.";

                            // adjust the castlestate
                            this->castlestate = WHITEKINGSIDE;

                            // change position of the pieces
//                            this->Board.getPiece(Position(7,0))->setPos(Position(5,0));
//                            this->Board.getPiece(Position(4,0))->setPos(Position(6,0));

                            // set position of rook and king on the board, ultimately changing the positions assigned to the pieces as well
                            this->Board.setPiece(this->Board.getPiece(Position(7,0)), Position(5,0));
                            this->Board.setPiece(this->Board.getPiece(Position(4,0)), Position(6,0));

                            // and erase king and rook from their former squares
                            this->Board.setPiece(nullptr, Position(7,0));
                            this->Board.setPiece(nullptr, Position(4,0));

                            // immediately return true, we don't have to check anything else. We know that the king is not in check, since
                            // neither of the squares the king moved over or is in can be attacked by the other player, as ensured above
                            return true;
                        }
                        else {
                            this->error = NOVALIDMOVE;
                            return false;
                        }
                    }

                    // Queenside castle, same procedure as Kingside castle
                    // Here, there are have to be three empty squares between king and rook
                    if (x1 > x2 and Board.getPiece(Position(1,0)) == nullptr and Board.getPiece(Position(2,0)) == nullptr and Board.getPiece(Position(3,0)) == nullptr and Board.getPiece(Position(0,0)) != nullptr) {

                        // If the rook has moved before
                        if (!Board.getPiece(Position(0,0))->getFirstmove() or Board.getPiece(Position(0,0))->Piecetype() != ROOK) {
                            this->error = NOVALIDMOVE;
                            return false;
                        }

                        // If the king is not in check and the squares the king is going to move over are not attacked: (King is not going to move over or end up on square (1,0), so this square can be attacked)
                        if (!Attack(Position(2,0), Other) and !Attack(Position(3,0), Other) and !Attack(Position(4,0), Other)) {
                            qDebug() << "Castling Queenside, white.";
                            this->castlestate = WHITEQUEENSIDE;

                            // change position of rook and king
//                            this->Board.getPiece(Position(0,0))->setPos(Position(3,0));
//                            this->Board.getPiece(Position(4,0))->setPos(Position(2,0));

                            // change position of rook and king on the board
                            this->Board.setPiece(this->Board.getPiece(Position(0,0)), Position(3,0));
                            this->Board.setPiece(this->Board.getPiece(Position(4,0)), Position(2,0));
                            this->Board.setPiece(nullptr, Position(0,0));
                            this->Board.setPiece(nullptr, Position(4,0));

                            // immediately return true
                            return true;
                        }
                        else {
                            this->error = NOVALIDMOVE;
                            return false;
                        }
                    }
                }

                // For the case that BLACK wants to castle, same procedure as for white
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
                        if (!Attack(Position(2,7), Other) and !Attack(Position(3,7), Other) and !Attack(Position(4,7), Other)) {
                            qDebug() << "Castling Queenside, white.";
                            this->castlestate = BLACKQUEENSIDE;

                            // change position of rook and king
                            this->Board.getPiece(Position(0,7))->setPos(Position(3,7));
                            this->Board.getPiece(Position(4,7))->setPos(Position(2,7));

                            // change position of rook and king on the board
                            this->Board.setPiece(this->Board.getPiece(Position(0,7)), Position(3,7));
                            this->Board.setPiece(this->Board.getPiece(Position(4,7)), Position(2,7));
                            this->Board.setPiece(nullptr, Position(0,7));
                            this->Board.setPiece(nullptr, Position(4,7));

                            // immediately return true
                            return true;
                        }
                        else {this->error = NOVALIDMOVE; return false;}
                    }
                }
                // if either Black or White want to castle but the respective  King has moved before
                else {
                        this->error = NOVALIDMOVE;
                        return false;
                    }

            }


            // if checkmove approved the move, kill the piece on the second spot
            if (pieceTwo != nullptr) {
                pieceTwo->setAlive(false);
            }

            // set pieceOne to position 2
            // and erase pieceOne from position1
            this->Board.setPiece(pieceOne, pos2);
            this->Board.setPiece(nullptr, pos1);




            // this move is only valid if the player is not in check after the move
            bool kingUnSafe = Check(Other, Current);

            // if king is not safe -> reset pieceOne to position 1 and set Piecetwo to position 2, if the second spot was empty, set a nullptr to position 2
             if (kingUnSafe) {

                pieceOne->setPos(pos1);
                this->Board.setPiece(pieceOne, pos1);
                if (pieceTwo != nullptr) {
                    pieceTwo->setAlive(true);

                    this->Board.setPiece(pieceTwo, pos2);
                }
                else {
                    this->Board.setPiece(nullptr, pos2);
                }

                // appropriate error message
                this->error = KINGUNSAFE;
                return false;
            }


            // set enpassant to false for all pieces on the board, we will set enpassant = true later if appropriate
            // Iterate through the list of alive pieces for the current and the other player
            for (Piece * alivePiece : Current->getAlivePieces()) {
                if (alivePiece->Piecetype() == PAWN) {
                    alivePiece->setEnPassant(false);
                }
            }
            for (Piece * alivePiece : Other->getAlivePieces()) {
                if (alivePiece->Piecetype() == PAWN) {
                    alivePiece->setEnPassant(false);
                }
            }



            // Every pawn has its enpassantvalue which indicates if it could be, in the next move, captured enpassant by another pawn in the appropriate position
            // if this is the first move of the Pawn, in other words, if it has moved two squares up or down, its enpassant value is set to true
            if (pieceOne->Piecetype() == PAWN) {
                int y1 = pos1.getY();
                int y2 = pos2.getY();
                int y1y2 = abs(y1-y2);
                if (y1y2 == 2) {
                    pieceOne->setEnPassant(true);
                }
            }

            // check if Pawn can be promoted
            // if a pawn is on the 7th or 0th rank, it can be promoted
            if (pieceOne->Piecetype() == PAWN and pos2.getY() == 7 or pieceOne->Piecetype() == PAWN and pos2.getY() == 0 ) {
                // the pawn will be promoted later. The GUI will provide a piecetype to promote to
                // to use for the GUI
                this->Promotion = true;
            }

            // in the case of Rook, Pawn and King it is important to know for specific rules if the piece has moved before (castling, movement of pawn, enpassant)
            pieceOne->setFirstmove(false);

            // debugging reasons
            Board.printBoard();
            return true;
}



// is a certain move valid for a Player curr given a certain constellation of the board?
// this function returns an array of two booleans, one stating if Pieceone can attack pos2, the other if it can move to pos2
bool* ChessGame::Checkmove(Position pos2, Piece* pieceOne) {

    Position pos1 = pieceOne->getPos();
    Piece* pieceTwo = this->Board.getPiece(pos2);

    bool* movearray = new bool[2];
    // is this move allowed to make?
    movearray[0] = true;

    // vs. Can the piece attack this spot?
    // So, for the pawns, if the spot on the diagonal is empty, the pawn cannot move there, but is attacking the spot!
    movearray[1] = true;



    // if either start or destination position is not valid -> error
    if (!pos1.getValid() or !pos1.getValid()) {
        this->error = NOVALIDPOS;
        movearray[0] = false;
        movearray[1] = false;
    }


    // if piece at destination and piece at source have the same color
    // Only look at case of not Pawn, because for pawn pieceTwo != nullptr can be not allowed, independent of the color of piecetwo
    // Pawn can only hit diagonally
    if (pieceOne->Piecetype() != PAWN) {
        if (pieceTwo != nullptr and pieceTwo->getColor() == pieceOne->getColor()) {
            this->error = SPOTBLOCKED;
            movearray[0] = false;
            movearray[1] = false;
        }
    }


    // Is it allowed, according to the rules of moving for this piece, for the piece at pos1 to move to pos2?
    bool checkMove = pieceOne->move_valid(pos2);

    // if the move is not valid -> exit
    if (!checkMove) {
        this->error = NOVALIDMOVE;
        movearray[0] = false;
        movearray[1] = false;
    }

    // EXTRA RULES FOR PAWN - HITTING DIAGONALLY, ENPASSANT
    if (pieceOne->Piecetype() == PAWN) {

        // If a pawn hits diagonally and theres no piece at the second spot, only if there is a pawn next to it which has the same Y coordinate as he does
        // and the same x coord of the final position, the move is allowed. This is called En passant.
        if (pos1.getX() != pos2.getX() and pieceTwo == nullptr) {

            // If enpassant is true for this piece next to the Pawn (which is also a pawn)
            if (this->Board.getPiece(Position(pos2.getX(), pos1.getY())) != nullptr and this->Board.getPiece(Position(pos2.getX(), pos1.getY()))->getEnPassant()) {
                qDebug() << "Enpassant!!";
                this->enpassant = true;
            }

            // All other cases not allowed
            else {
                movearray[0] = false;

                // movearray[1] is still true, because the Pawn is actively attacking this spot
            }
        }
        // Pawn cannot hit in a straigt line, if theres a piece in front of the pawn, the pawn cannot move
        else if (pos1.getX() == pos2.getX()) {

            // can never attack if not diagonal
            movearray[1] = false;

            // and if there is a piece in front of it, it cannot move, independent of the color of that piece
            if (pieceTwo != nullptr) {
                movearray[0] = false;
            }
        }

        // Pawn cannot hit pieces of its own color
        else if (pos1.getX() != pos2.getX() and pieceTwo != nullptr and pieceTwo->getColor() == pieceOne->getColor()) {
            movearray[0] = false;
            movearray[1] = false;
        }


    }



    // Check if there are pieces in the way of moving from position 1 to position 2
    int x1 = pos1.getX();
    int x2 = pos2.getX();
    int y1 = pos1.getY();
    int y2 = pos2.getY();
    int x1x2 = abs(x1-x2);
    int y1y2 = abs(y1-y2);

    //  x1x2 and y1y2 are either equal or one is zero.
    bool freeway = true;
    if (x1x2 == 1 or y1y2 == 1) {
        freeway = true;
    }

    // a knights path cannot be blocked by other pieces, it jumps
    else if (pieceOne->Piecetype() == KNIGHT) {
        freeway = true;
    }

    // First Case: Moving in straigh lines (Rook and Queen)
    //  pieces are on the same row
    else if (y1y2 == 0) {
        // starting at 2, since the case 1 is taken care of, there can be no piece at the destination square
        // and 0 also, a piece is not allowed to not move
        for (int i = 1; i < x1x2; i++) {

            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(min(x1,x2)+i , y1)) != nullptr) {
                freeway = false;
            }
        }
    }
    //  pieces are on the same column
    else if (x1x2 == 0) {
        for (int i = 1; i < y1y2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x1 , min(y1,y2)+i)) != nullptr) {
                freeway = false;
            }
        }
    }

    // Second case: moving diagonally (Bishop and Queen)
    // Distinguish four cases of the destination spot and source spot to each other
    // 1. piece one on the lower left of piece two
    else if (x1<x2 and y1<y2) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x1+i , y1+i)) != nullptr) {
                freeway = false;
            }
        }
    }
    // 2. piece one on the upper right of piece two
    else if (x2<x1 and y2<y1) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x2+i , y2+i)) != nullptr) {
                freeway = false;
            }
        }
    }
    // 3. piece one on the lower right of piece two
    else if (x2<x1 and y1<y2) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x2+i , y2-i)) != nullptr) {
                freeway = false;
            }
        }
    }
    // 4. piece one on the upper left of piece two
    else if (x1<x2 and y2<y1) {
        for (int i = 1; i < x1x2; i++) {
            // look at all the squares between x1 and x2 and see if theres a piece on that spot
            if (Board.getPiece(Position(x1+i , y1-i)) != nullptr) {
                freeway = false;
            }
        }
    }

    // if the path is blocked, set the appropriate error
    if (!freeway) {
        this->error = PIECEINWAY;
        movearray[0] = false;
        movearray[1] = false;
    }

    // if the piece is a king, moving two squares could be generally allowed (due to castles), *but* a king will never be able to attack this spot
    if (pieceOne->Piecetype() == KING and x1x2 == 2) {
        movearray[1] = false;
        movearray[0] = true;

    }

    return movearray;
}




// Does the Player Current attack the spot dest?
bool ChessGame::Attack(Position dest, Player* Current) {

    // get the vector of alive pieces of the current player
    vector<Piece*> AlivePieces = Current->getAlivePieces();

    bool attack = false;

    // iterate over the alivepieces, if one of them is able to attack the Position dest, set the bool attack to true
    for (Piece* alivepiece : AlivePieces) {
        if (Checkmove(dest, alivepiece)[1]) {
            attack = true;
        }
    }
    return attack;
}


// Is the Current player checking the other player? Is he attacking Other players king?
bool ChessGame::Check(Player* Current, Player* Other)  {
    Position kingPos = Other->getKing()->getPos();

    // if one of Current players pieces can attack Other players king, a check is on the board
    if (Attack(kingPos, Current)) {
        return true;
    }
    else {
        return false;
    }
}

// To investigate if a checkmate is on the board (Current player is checkmating other player)
//
bool ChessGame::CheckMate(Player* Current, Player* Other)  {

    // if there is no check on the board, it cannot be checkmate
    if (!Check(Current, Other)) {
        return false;
    }

    // get the alive pieces of the other player
    vector<Piece*> AlivePieces = Other->getAlivePieces();

    bool checkMate = true;

    // and see if one of these alive pieces can move in such a way that there is no check on the board anymore after the move.
    // iterate over all positions on the board
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
                for (Piece* alivepiece : AlivePieces) {
                    Position alivepiece_pos = alivepiece->getPos();

                    // Check if this particular alive piece can move to this particular spot
                    if (Checkmove(Position(i,j), alivepiece)[0]) {


                        if (i == 5 and j == 5 and Board.getPlayerWhite()->getQueen(0)->getPos().getY() == 2) {
                            cout << "was?" << endl;
                        }

                        // if the piece is a king, the checkmove function will return true if the king moves two to the right or left
                        // because of the castle rule. This is not a valid move.
                        if (alivepiece->Piecetype() == KING and abs(alivepiece->getPos().getX() - i) == 2) {
                            continue;
                        }

                        // now, reset the pieces on the board. Alivepiece to the particular position and erase the square alivepiece was in

                        Piece* pieceTwo = this->Board.getPiece(Position(i,j));
                        if (pieceTwo != nullptr) {
                            pieceTwo->setAlive(false);
                        }

                        // erase the space that the piece is in and put it to the other space
                        this->Board.setPiece(alivepiece, Position(i,j));
                        this->Board.setPiece(nullptr, alivepiece_pos);

                        // If, now that a possible move has been made, there is no more check on the board, checkmate is false
                        if (!Check(Current, Other)) {
                            checkMate = false;
                        }

                        // reset the original position on the board
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

}

// staleMate follows the exact same implementation as checkMate, but the Other player cannot be in check
bool ChessGame::StaleMate(Player* Current, Player *Other) {
    // If Current is checking other, it cannot be stalemate
    if (Check(Current, Other)) {
        return false;
    }

    vector<Piece*> AlivePieces = Other->getAlivePieces();

    bool draw = true;

    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
                for (Piece* alivepiece : AlivePieces) {
                    Position alivepiece_pos = alivepiece->getPos();
                    if (Checkmove(Position(i,j), alivepiece)[0]) {

                        if (alivepiece->Piecetype() == KING and abs(alivepiece->getPos().getX() - i) == 2) {
                            continue;
                        }



                        Piece* pieceTwo = this->Board.getPiece(Position(i,j));
                        if (pieceTwo != nullptr) {
                            pieceTwo->setAlive(false);
                        }

                        this->Board.setPiece(nullptr, alivepiece->getPos());
                        this->Board.setPiece(alivepiece, Position(i,j));

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



// Current Players Pawn at position pos is promoted according to the QString inputstring coming from the space.cpp file.
void ChessGame::promotion(Position pos, Player* Current, QString inputstring)  {
    qDebug() << "PROMOTING!!! To a " << inputstring;
    std::string promotiontype = inputstring.toStdString();

    // note that we can only promote each piece once, because for each piece, there is only one more piece of the same kind

    if (promotiontype == "Knight") {
        Board.setPiece(Current->getKnight(2), pos);
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
        Board.getPiece(pos)->setPos(pos);
        Current->getQueen(1)->setAlive(true);
    }
}



// This function is a Qt slot, a function designed to receive QObject signals.
// It receives a signal from the Display whenever a space is clicked. Upon collecting
// two spaces, the move can be executed if it is valid, or ignored if not.
void ChessGame::Game(QString input)
{
    qDebug() << "String received from Display: " << input;

    // First, here: Handle promotions
    // we want to promote, given a certain inputstring
    if (input == "Queen" or input == "Bishop" or input == "Knight" or input == "Rook") {

        // for that, get the position that was last moved to. This is the position that the promotion will be happening at
        int moves_played = move_list.size();
        Position promotionpos = Position(move_list[moves_played-2], move_list[moves_played-1]);

        // With this position, promote the players Pawn at this position to a given piece, defined by the input string.
        // The player whose piece is promoted is Black, if it is now whites turn and white if it is now blacks turn.
        // This is because the move was made in the last turn, and the Colors switched after that.
        if (this->Turn) {
            this->promotion(promotionpos, this->Board.getPlayerBlack(), input);
        }
        else {
            this->promotion(promotionpos, this->Board.getPlayerWhite(), input);
        }

        // assemble a string to send to the GUI in order for the GUI to display the correct promoted piece
        std::string position_string_1 = std::to_string(move_list[moves_played-2]);
        std::string position_string_2 = std::to_string(move_list[moves_played-1]);

        // the string that is sent to the GUI is assembled as follows:
        const std::string sendstring = "P" + position_string_1 + position_string_2 + input.toStdString();
        QString qstr = QString::fromStdString(sendstring);

        emit sendResultingBoard(qstr);

        // In order to display if a check is on the board:
        // if either Player is checking either player, send Check to the display function
        if (this->Check(Board.getPlayerBlack(), Board.getPlayerWhite()) or this->Check(Board.getPlayerWhite(), Board.getPlayerBlack())) {
            emit sendResultingBoard("Check");
        }
    }


    // Now, for the ChessGame.
    // We receive a String from the GUI and we assign this string to our variables position1 and position2

    // if there was nothing stored in position1 yet, store the string in position1
    else if (position1 == "")
    {
        position1 = input.toStdString();
    }
    // if position1 already contains a position, store the next string in position2
    else if (position2 == "")
    {
        // convert the QString into an std::string
        position2 = input.toStdString();

        // Convert the positions into values that are not strings
        int x1, y1, x2, y2;
        for (int i = 0; i < 8; i++) {
            if (position1[0] == '0') {x1 = 0;}
            if (position1[0] == '1') {x1 = 1;}
            if (position1[0] == '2') {x1 = 2;}
            if (position1[0] == '3') {x1 = 3;}
            if (position1[0] == '4') {x1 = 4;}
            if (position1[0] == '5') {x1 = 5;}
            if (position1[0] == '6') {x1 = 6;}
            if (position1[0] == '7') {x1 = 7;}
            if (position1[1] == '0') {y1 = 0;}
            if (position1[1] == '1') {y1 = 1;}
            if (position1[1] == '2') {y1 = 2;}
            if (position1[1] == '3') {y1 = 3;}
            if (position1[1] == '4') {y1 = 4;}
            if (position1[1] == '5') {y1 = 5;}
            if (position1[1] == '6') {y1 = 6;}
            if (position1[1] == '7') {y1 = 7;}

            if (position2[0] == '0') {x2 = 0;}
            if (position2[0] == '1') {x2 = 1;}
            if (position2[0] == '2') {x2 = 2;}
            if (position2[0] == '3') {x2 = 3;}
            if (position2[0] == '4') {x2 = 4;}
            if (position2[0] == '5') {x2 = 5;}
            if (position2[0] == '6') {x2 = 6;}
            if (position2[0] == '7') {x2 = 7;}
            if (position2[1] == '0') {y2 = 0;}
            if (position2[1] == '1') {y2 = 1;}
            if (position2[1] == '2') {y2 = 2;}
            if (position2[1] == '3') {y2 = 3;}
            if (position2[1] == '4') {y2 = 4;}
            if (position2[1] == '5') {y2 = 5;}
            if (position2[1] == '6') {y2 = 6;}
            if (position2[1] == '7') {y2 = 7;}
        }

        // store the information in positions
        Position pos1 = Position(x1,y1);
        Position pos2 = Position(x2,y2);


        // create pointers to player whose turn it currently is and other player
        Player* Current;
        Player* Other;

        // if it is whites turn, current is white and other is black and vice versa
        if (this->Turn == true) {
            Current = Board.getPlayerWhite();
            Other = Board.getPlayerBlack();
        }
        else {
            Other = Board.getPlayerWhite();
            Current = Board.getPlayerBlack();
        }

        // Check if Player Current is allowed to move his or her piece from position pos1 to pos2
        bool ok = this->Maketurn(pos1, pos2);

        // if it is not allowed, depending on the error we got, send different responses to the GUI so it can display the different errors
        if (!ok) {
            if (this->error == NOVALIDPOS) {
                qDebug() << "You did not provide a valid position.";
                emit sendResultingBoard("Invalid Move");
                position1 = "";
                position2 = "";
                return;
            }
            else if (this->error == NOPIECE) {
                qDebug() << "There is no piece at the spot you want to move from. ";
                emit sendResultingBoard("You have not selected a piece.");
                position1 = "";
                position2 = "";
                return;
            }
            else if (this->error == PIECEINWAY) {
                qDebug() << "There is a piece in the way and your piece cannot jump, since it is not a knight. ";
                emit sendResultingBoard("There is a piece in the way.");
                position1 = "";
                position2 = "";
                return;
            }
            else if (this->error == WRONGCOLOR) {
                qDebug() << "This piece has the wrong color.";
                emit sendResultingBoard("This piece has the wrong color.");
                position1 = "";
                position2 = "";
                return;
            }
            else if (this->error == SPOTBLOCKED) {
                qDebug() << "The spot you are trying to move to is blocked by a piece of your color. ";
                emit sendResultingBoard("This spot is blocked.");
                position1 = "";
                position2 = "";
                return;
            }
            else if (this->error == SPOTBLOCKED_PAWN) {
                qDebug() << "The spot you are trying to move to is blocked by a piece of your color. The Pawn can only hit diagonally. ";
                emit sendResultingBoard("The Pawn can only hit diagonally.");
                position1 = "";
                position2 = "";
                return;
            }
            else if (this->error == NOVALIDMOVE) {
                qDebug() <<  "The move you provided is against the rules of moving for this piece. " ;
                emit sendResultingBoard("This is not a valid move for this piece.");
                position1 = "";
                position2 = "";
                return;
            }
            else if (this->error == KINGUNSAFE) {
                qDebug() << "The move you are trying to make would leave your king in check. ";
                emit sendResultingBoard("This move would leave your king in check.");
                position1 = "";
                position2 = "";
                return;
            }
        }


        // the provided move was valid. Tell the GUI to show the move on the board.

        // if there is an en passant capture happening on the board, send the two positions together with the word enpassant as a QString
        if (this->enpassant) {
            QString pos1 = QString::fromStdString(position1);
            QString pos2 = QString::fromStdString(position2);
            QString other = ", Enpassant";
            QString finalStr = pos1 + pos2 + other;
            emit sendResultingBoard(finalStr);
        }

        // if there is a promotion happening, let the GUI know
        else if (this->Promotion) {
            QString pos1 = QString::fromStdString(position1);
            QString pos2 = QString::fromStdString(position2);
            QString other = ", Promotion";
            QString finalStr = pos1 + pos2 + other;
            emit sendResultingBoard("Promotion");
            emit sendResultingBoard(finalStr);
        }

        // if there was a castling, tell the GUI by sending the appropriate QString
        else if (this->castlestate == WHITEKINGSIDE) {
            emit sendResultingBoard("Castle White, Kingside");
        }
        else if (this->castlestate == WHITEQUEENSIDE) {
            emit sendResultingBoard("Castle White, Queenside");
        }
        else if (this->castlestate == BLACKKINGSIDE) {
            emit sendResultingBoard("Castle Black, Kingside");
        }
        else if (this->castlestate == BLACKQUEENSIDE) {
            emit sendResultingBoard("Castle Black, Queenside");
        }

        // if it is just a 'normal' move, send back only the string made up of the positions of the two pieces
        else {
            QString pos1 = QString::fromStdString(position1);
            QString pos2 = QString::fromStdString(position2);
            QString finalStr = pos1 + pos2;
            emit sendResultingBoard(finalStr);
        }

        // At this point, all the important move information has been transmitted.
        // Further, one has to check for check, checkmate or stalemate

        // CHECK
        bool Checkstate = this->Check(Current, Other);

        // if Current is checking other, send the appropriate string to the GUI
        if (Checkstate) {
            emit sendResultingBoard("Check");
        }

        // If the game is drawn, send the appropriate string
        bool draw = this->StaleMate(Current, Other);
        if (draw) {
            sendResultingBoard("Draw");
            position1 = "";
            position2 = "";
            return;
        }

        // If Current checkmated Other, send appropriate string
        bool gameOver = this->CheckMate(Current, Other);
        if (gameOver) {
            emit sendResultingBoard("Checkmate");
            position1 = "";
            position2 = "";
            return;
        }




        // Add the current move to the vector of played moves
        this->move_list.push_back(x1);
        this->move_list.push_back(y1);
        this->move_list.push_back(x2);
        this->move_list.push_back(y2);

        // set enpassant and promotion to false and set castlestate to NOCASTLES
        this->enpassant = false;
        this->Promotion = false;
        this->castlestate = NOCASTLES;

        // Turn switches after every move
        this->Turn= !Turn;

        // reset the strings that contain the positions. They will be filled with the positions in the next move.
        position1 = "";
        position2 = "";

        // for debugging reasons
        this->Board.printBoard();
    }


}



