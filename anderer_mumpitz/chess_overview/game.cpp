#include "game.h"


ChessGame::ChessGame() : Black(false), White(true), Board(White, Black) {
    this->Whoseturn = true;
    this->state = ACTIVE;
}

Player ChessGame::getPlayerWhite() {return this->White;}

Player ChessGame::getPlayerBlack() {return this->Black;}

bool ChessGame::Maketurn(Player current, Player other, Move move) {
    //        std::cout << "Maketurn function executed" << std::endl;

            Position pos1 = move.getFirst();
            Position pos2 = move.getLast();

            if (!pos1.getValid() or !pos1.getValid()) {this->error = NOVALIDPOS; return false;}

            Piece* pieceOne = this->Board.getPiece(pos1);

            // Now, piece in spot two?
            Piece* pieceTwo = this->Board.getPiece(pos2);

            if (pieceTwo == nullptr) {
    //            std::cout << "No Piece at destination spot" << std::endl;
            }

            if (pieceOne == nullptr) {
                this->error = NOPIECE;
                return false;
            }

            if (current.getIswhite() != pieceOne->getIswhite()) {
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
            else if (pieceOne->Piecetype() == PAWN) {
                if (pieceTwo != nullptr) {
                    this->error = SPOTBLOCKED_PAWN;
                    return false;
                }
            }

            bool checkMove = pieceOne->move_valid(move.getLast());

    //        if (pieceOne->Piecetype() == PAWN)

            // if the move is not valid -> exit
            if (!checkMove) {
                this->error = NOVALIDMOVE;
                return false;
            }


            // MAKE A LAMBDA FUNCTION OUT OF THIS
            int x1 = pos1.getX();
            int x2 = pos2.getX();
            int y1 = pos1.getY();
            int y2 = pos2.getY();
            int x1x2 = abs(x1-x2);
            int y1y2 = abs(y1-y2);

                // x1x2 and y1y2 are either equal or one is zero.
                // the knight case is not being taken into account, since the knight jumps

                // when the pieces are next to each other
                // == 0 taken care of already
            if (x1x2 == 1 or y1y2 == 1) {checkMove == true;}

                // if its 2 fields connected by a straight line
                // pieces are on the same row
            if (y1y2 == 0) {
                    // starting at 2, since the case 1 is taken care of, there can be no piece at the destination square
                    // and 0 also, a piece is not allowed to not move
                for (int i = 1; i < x1x2; i++) {
                    // look at all the squares between x1 and x2 and see if theres a piece on that spot
                    if (Board.getPiece(Position(min(x1,x2)+i , y1)) != nullptr) {checkMove = false;}
                }
            }
                // pieces are on the same column
            else if (x1x2 == 0) {
                for (int i = 1; i < y1y2; i++) {
                    // look at all the squares between x1 and x2 and see if theres a piece on that spot
                    if (Board.getPiece(Position(x1 , min(y1,y2)+i)) != nullptr) {checkMove = false;}
                }
            }
                // piece one on the lower left of piece two
            else if (x1<x2 and y1<y2) {
                for (int i = 1; i < x1x2; i++) {
                    // look at all the squares between x1 and x2 and see if theres a piece on that spot
                    if (Board.getPiece(Position(x1+i , y1+i)) != nullptr) {checkMove = false;}
                }
            }
                // piece one on the upper right of piece two
            else if (x2<x1 and y2<y1) {
                for (int i = 1; i < x1x2; i++) {
                    // look at all the squares between x1 and x2 and see if theres a piece on that spot
                    if (Board.getPiece(Position(x2+i , y2+i)) != nullptr) {checkMove = false;}
                }
            }
                // piece one on the lower right of piece two
            else if (x2<x1 and y1<y2) {
                for (int i = 1; i < x1x2; i++) {
                    // look at all the squares between x1 and x2 and see if theres a piece on that spot
                    if (Board.getPiece(Position(x2+i , y1+i)) != nullptr) {checkMove = false;}
                }
            }
                // piece one on the upper left of piece two
            else if (x1<x2 and y2<y1) {
                for (int i = 1; i < x1x2; i++) {
                    // look at all the squares between x1 and x2 and see if theres a piece on that spot
                    if (Board.getPiece(Position(x1+i , y2+i)) != nullptr) {checkMove = false;}
                }
            }
            if (!checkMove) {
                this->error = PIECEINWAY;
                return false;
            }

            // if there is a piece at the second spot, kill it
            if (pieceTwo != nullptr) {
                pieceTwo->setPos(Position(0,0));
                pieceTwo->setIsalive(false);
            }

            // PIECE ONE GETS A NEW POSITION
            pieceOne->setPos(pos2);

            cout << "this is probably it!" << endl;

            // THE BOARD NOW ALSO GETS THE INFORMATION OF THE NEW POSITION OF PIECE ONE
            this->Board.setPiece(nullptr, pos1, current);
            cout << "test " << endl;
            this->Board.setPiece(pieceOne, pos2, current);


            // now, this move that we just made is only valid if our king (so the king of the current player) is still safe
            // so not in check
            bool kingStillSafe = !Check(other, current);

            // if king is not safe -> abort
            if (!kingStillSafe) {
                pieceOne->setPos(pos1);
                if (pieceTwo != nullptr) {
                    pieceTwo->setPos(pos2);
                    pieceTwo->setIsalive(true);

                    // we have to provide the reference to a certain piece, not the piece itself
                    this->Board.setPiece(pieceTwo, pos2, current);
                }
                else {this->Board.setPiece(nullptr, pos2, current);}
                this->error = KINGUNSAFE;
                return false;
            }

            // important: if the piece was a pawn, we set its first move to false, now it can no longer do two squares at once.
            if (pieceOne->Piecetype() == PAWN) {pieceOne->setFirstmove(false);}
            this->Board = Board;

            // check if Pawn can be promoted
            if (pieceOne->Piecetype() == PAWN and pieceOne->getPromotion()) {
                this->promotion(current, other, pos2);
            }



            return true;

        }           // make turn function is over




bool ChessGame::Attack(Player current, Player other, Position dest) {

    bool attack = false;
    // when a piece is allowed to move. Look at all the potential attacking pieces.
    if (Maketurn(current, other, Move(current.getKing()->getPos(), dest))) {attack = true;}
    // can the queen attack the position dest?
    if (Maketurn(current, other, Move(current.getQueen()->getPos(), dest))) {attack = true;}
    // can either rook attack the position dest?
    if (Maketurn(current, other, Move(current.getRook(0)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getRook(1)->getPos(), dest))) {attack = true;}
    // can either bishop attack the position dest?
    if (Maketurn(current, other, Move(current.getBishop(0)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getBishop(1)->getPos(), dest))) {attack = true;}
    // can either knight attack the position dest?
    if (Maketurn(current, other, Move(current.getKnight(0)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getKnight(1)->getPos(), dest))) {attack = true;}
    // can either pawn attack the position dest? Remember: the pawn is the only piece that has a special capturing direction
    if (Maketurn(current, other, Move(current.getPawn(0)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getPawn(1)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getPawn(2)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getPawn(3)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getPawn(4)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getPawn(5)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getPawn(6)->getPos(), dest))) {attack = true;}
    if (Maketurn(current, other, Move(current.getPawn(7)->getPos(), dest))) {attack = true;}

    return attack;
}



bool ChessGame::Check(Player current, Player other)  {
    Position kingPos = other.getKing()->getPos();
    if (Attack(current, other, kingPos)) {return true;}
    else {
        return false;
    }
}


bool ChessGame::CheckMate(Player current, Player other)  {
    // only check for the case that current is checking other, because other can not be in check at this point
    if (!Check(current, other)) {return false;}
    Position kingPos = other.getKing()->getPos();

    // here maybe a lambda function to iterate over all possible positions the king can be in
    for (int i = -1; i<2; i++) {
        for (int j = -1; j<2; j++) {
            // if every spot around the king is either attacked or blocked by a piece of the same color
            // the getPiece method takes a pos
            // if one spot is NOT attacked and the spot is either free or a piece of the other color is on it, then it is not checkmate
            if (!Attack(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j)) == nullptr ) {return false;}
            else if (!Attack(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == current.getIswhite()) {return false;}
        }
    }
    return true;

}
    // if king is attacked
    // and make_move does not work for any spot for the king
    // and there is no piece that can move in front of the king


bool ChessGame::StaleMate(Player current, Player other) {
    //        if (Check(current, other)) {return false;}
    //        Position kingPos = other.getKing()->getPos();
    //        // here maybe a lambda function to iterate over all possible positions the king can be in
    //        for (int i = -1; i<2; i++) {
    //            for (int j = -1; j<2; j++) {
    //                // if every spot around the king is either attacked or blocked by a piece of the same color
    //                // the getPiece method takes a pos
    ////                if (!Attack(current, kingPos.shiftPos(i, j)) or this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == other.getIswhite() ) {return false;}
    //                if (!Attack(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j)) == nullptr ) {return false;}
    //                else if (!Attack(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == current.getIswhite()) {return false;}
    //                // here, we have to iterate over the pieces on the board and see if any of them can move.
    //                else if (true) {return false;}
    //            }
    //        }
            return false;

        }
            // king is not attacked
            // but make_move does not work, because all of the fields are attacked
            // and the player can not move any other piece, so make_move does not work for any other piece either





void ChessGame::promotion(Player current, Player other, Position pos)  {
    int promotion_type;
    cout << "Your pawn can be promoted. Please provide the peace you want to promote to. Provide a number as follows: " << endl;
    cout << "Queen: 1" << endl << "Rook: 2" << endl << "Knight: 3" << endl << "Bishop: 4" << endl;
    cin >> promotion_type;
    switch (promotion_type) {
    case 1:
        Board.setPiece(current.getQueen(), pos, current);
    case 2:
        Board.setPiece(current.getRook(0), pos, current); // Board.setPiece(current.getRook(this->promotion_count + 3), pos, current);
    case 3:
        Board.setPiece(current.getKnight(0), pos, current);
    case 4:
        Board.setPiece(current.getBishop(0), pos, current);
    }
    this->promotion_count += 1;
}



void ChessGame::Game() {
    bool ok;
    this->move_count = 0;
    GameState state = ACTIVE;
    while (state == ACTIVE or state == CHECK) {

        if (state == CHECK) {std::cout << "You are in check. React." << std::endl;}

        // create two players, current and other
        Player current;
        Player other;
        if (this->Whoseturn == true) {current = Board.getPlayerWhite(); other = Board.getPlayerBlack(); cout << "WHITES MOVE, move number " << move_count << endl;}
        else {other = Board.getPlayerWhite(); current = Board.getPlayerBlack(); cout << "BLACKS MOVE, move number " << move_count  << endl;}

        Move move = current.getMove();

        Position pos1 = move.getFirst();
        Position pos2 = move.getLast();

        cout << "You picked a piece of type ";
        if (Board.getPiece(pos1)->Piecetype() == PAWN) {cout << "Pawn" << endl;}
        else if (Board.getPiece(pos1)->Piecetype() == KNIGHT) {cout << "Knight" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == BISHOP) {cout << "Bishop" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == ROOK) {cout << "Rook" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == KING) {cout << "King" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == QUEEN) {cout << "Queen" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == NONE) {cout << "none" << " "<< endl;}
        else {cout << "i dont know" << endl;}
        cout << " and you want to move it from " << pos1.getX() << " " << pos1.getY() << " to " << pos2.getX() << " " << pos2.getY() << endl;

        // Remember: Maketurn takes the input from the current player and judges if the move is valid
        // judging by how the board is set up in this moment

        ok = this->Maketurn(current, other, move);


        cout << "Maketurn function over." << endl;

        if (ok) {cout << "Thank you. This is a valid move given the constellation of pieces on the board." << endl;}

//            break;

        // I want the player to reenter the move, until the move is valid.
        while (!ok) {
//                state = ERROR;
            cout << "ERROR." << endl;
            if (this->error == NOVALIDPOS) {cout << "You did not provide a valid position. " << endl;}
            else if (this->error == NOPIECE) {cout << "There is no piece at the spot you are trying to access. " << endl;}
            else if (this->error == PIECEINWAY) {cout << "There is a piece in the way and your piece cannot jump, since it is not a knight. " << endl;}
            else if (this->error == WRONGCOLOR) {cout << "This piece has the wrong color. " << endl;}
            else if (this->error == SPOTBLOCKED) {cout << "The spot you are trying to move to is blocked by a piece of your color. " << endl;}
            else if (this->error == SPOTBLOCKED_PAWN) {cout << "The spot you are trying to move to is blocked by a piece of your color. The Pawn can only hit diagonally. " << endl;}
            else if (this->error == NOVALIDMOVE) {cout << "The move you provided is against the rules of moving for this piece. " << endl;}
            else if (this->error == KINGUNSAFE) {cout << "The move you are trying to make would leave your king in check. " << endl;}
            cout << "Try again!" << endl;
            Move move = current.getMove();
            ok = this->Maketurn(current, other, move);
            if (ok) {cout << "Thank you. This is a valid move given the constellation of pieces on the board." << endl;}// state == ACTIVE;}
            if (!ok) {cout << "Try again!" << endl;}
        }





        bool gameOver = this->CheckMate(current, other);

        // if the game is over, determine the winner and break the while loop
        if (gameOver) {
            if (this->Whoseturn) {state = WHITEWINS; std::cout << "Checkmate. White won." << std::endl; current.showOutput(state);}
            else {state = BLACKWINS; std::cout << "Checkmate. Black won." << std::endl; current.showOutput(state);}
            Board.printBoard();
            break;
        }
        if (!gameOver) {cout << "No Checkmate, game continues." << endl;}

        cout << "TEST AFTER GAMEOVER CHECK" << endl;

        bool draw = this->StaleMate(current, other);

        cout << "checkcheckcheck" << endl;


        if (draw) {std::cout << "The game is drawn." << std::endl; state = DRAW; current.showOutput(state); break; }

        if (!draw) {cout << "No Stalemate, game continues." << endl;}

        cout << "TEST AFTER DRAW CHECK" << endl;

        // after white, it's black and after black, it's white.
        bool ischeck = this->Check(current, other);
        if (ischeck) {
            std::cout << "Your move is valid. The other player is in check and has to respond to that." << std::endl;
            current.showOutput(state);
            continue;
        }
        std::cout << "Your move is valid. There is no checking happening whatsoever. The game continues." << std::endl;
        this->Whoseturn = !Whoseturn;
        current.showOutput(state);

        Board.printBoard();


        this->move_list.push_back(move.getFirst().getX());
        this->move_list.push_back(move.getFirst().getY());
        this->move_list.push_back(move.getLast().getX());
        this->move_list.push_back(move.getLast().getY());
        this->move_count += 1;
    }
}





