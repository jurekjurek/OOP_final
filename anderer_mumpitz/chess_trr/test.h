#ifndef TEST_H
#define TEST_H

#include "board.h"

/*  The most important class
 *  Here, the game is being controlled.
 *
 *
 *
*/

class ChessGame {
private:
    Player White, Black;
//    Player Black;
    ChessBoard Board;
    bool Whoseturn;         // true for white, false for black
    GameState state;
    vector<int> move_list;
    int move_count;
public:
    // when the class is called, a new game is generated
    // Black is not white, White is white
    ChessGame() : Black(false), White(true), Board(White, Black) {
//        this->Black = Player(false);
//        this->White = Player(true);
//        this->Board = ChessBoard(White, Black);
        this->Whoseturn = true;
        this->state = ACTIVE;
//        this->Board.printBoard();
    }

    Player getPlayerWhite() {return this->White;}
    Player getPlayerBlack() {return this->Black;}


    bool Maketurn(Player current, Player other, Move move) {
        std::cout << "Maketurn function executed" << std::endl;

//        Move move = current.getMove();



        Position pos1 = move.getFirst();
        Position pos2 = move.getLast();

//        cout << "test1" << endl;

        if (!pos1.getValid() or !pos1.getValid()) {cout << "Not a valid position! Make sure your input is correct" << endl; return false;}
//        this->Board.printBoard();

//        cout << "test1" << endl;

        Piece* pieceOne = this->Board.getPiece(pos1);

//        cout << "test1" << endl;

        // Now, piece in spot two?
        Piece* pieceTwo = this->Board.getPiece(pos2);

//        cout << "test1" << endl;

        if (pieceTwo == nullptr) {
            std::cout << "No Piece at destination spot" << std::endl;
        }

        if (pieceOne == nullptr) {
            std::cout << "There is no piece at the starting position! Pointer is nullptr." << std::endl;
            return false;
        }

//        std::cout << "Typeinfo " << typeid(pieceOne).name() << " Pos " << Board.getPiece(pos1)->getIsalive() << std::endl;

        if (Board.getPiece(pos1)->Piecetype() == PAWN) {cout << "Type Pawn" << endl;}
        else if (Board.getPiece(pos1)->Piecetype() == KNIGHT) {cout << "Knight" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == BISHOP) {cout << "Bishop" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == ROOK) {cout << "Rook" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == KING) {cout << "King" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == QUEEN) {cout << "Queen" << " "<< endl;}
        else if (Board.getPiece(pos1)->Piecetype() == NONE) {cout << "none" << " "<< endl;}
        else {cout << "i dont know" << endl;}

        // okay, lets test all kinds of things here

//        cout << "Does this work? I want to see where the piece of a specific player is. " << Board.getPlayerWhite().getKing()->getPos().getX() << " " << Board.getPlayerWhite().getKing()->getPos().getY() << endl;

        // std::cout << "Player colors, 1 " << current.getIswhite() <<  " 2 " << other.getIswhite() << " Piece colors, 1 " << pieceOne->getIswhite() << " 2 " << pieceTwo->getIswhite() << " Piece positions 1 x y " << pieceOne->getPos().getX() << pieceOne->getPos().getY() << " 2 x y " << pieceTwo->getPos().getX() << pieceTwo->getPos().getY() << std::endl;

        if (current.getIswhite() != pieceOne->getIswhite()) {
            std::cout << "color of current player is not equal to the color of the piece you're trying to move. Player: " << current.getIswhite() << " Piece: " << pieceOne->getIswhite() << std::endl;
            return false;
        }



        // if piece at destination and piece at source have the same color -> error
        if (pieceTwo != nullptr and pieceTwo->getIswhite() == pieceOne->getIswhite()) {
            std::cout << "The spot you want to move to is blocked by a piece of your color. " << pieceTwo->getIswhite() << "" << pieceOne->getIswhite() << std::endl;
            return false;
        }

        bool checkMove = pieceOne->move_valid(move.getLast());

//        if (pieceOne->Piecetype() == PAWN)

        // if the move is not valid -> exit
        if (!checkMove) {
            std::cout << "The move you are trying to make is not a valid move for this piece." << std::endl;
            return false;
        }

//        for (int i = 0; i<8; i++) {
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
//        }
        if (!checkMove) {
            cout << "You are trying to make an unvalid move. There is a piece in the way and your piece cannot jump since it is not a knight." << endl;
            return false;
        }

        // PIECE ONE GETS A NEW POSITION
        pieceOne->setPos(pos2);
//        std::cout << "Just changed the position of your piece to the new position" << std::endl;

        // setPiece takes a pointer to a piece and a position
        // THE BOARD NOW ALSO GETS THE INFORMATION OF THE NEW POSITION OF PIECE ONE
        this->Board.setPiece(nullptr, pos1, this->Whoseturn);
//        std::cout << "We set the now empty spot to null." << std::endl;
        //
        this->Board.setPiece(pieceOne, pos2, this->Whoseturn);
//        cout << "TESTESTESTEST, here is where we set the position." << endl;
//        std::cout << "and told the board where your piece is now." << std::endl;

//        cout << Board.getPiece(pos2)->Piecetype() << Board.getPiece(pos2)->getPieceNo() << endl;


        // collect all captured pieces at position -1, -1, IDK...
        if (pieceTwo != nullptr) {
            pieceTwo->setPos(Position(-1, -1));
            pieceTwo->setIsalive(false);
        }
        // maybe there could be a piece of the given type appearing in the corner or so... let's see

        // now, this move that we just made is only valid if our king (so the king of the current player) is still safe
        // so not in check
        bool kingStillSafe = !isCheck(other, current);

//        cout << "Kingstilsafe" << kingStillSafe << endl;

        // if king is not safe -> abort
        if (!kingStillSafe) {
            pieceOne->setPos(pos1);
            if (pieceTwo != nullptr) {
                pieceTwo->setPos(pos2);
                pieceTwo->setIsalive(true);

                // we have to provide the reference to a certain piece, not the piece itself
                this->Board.setPiece(pieceTwo, pos2, this->Whoseturn);
            }
            else {this->Board.setPiece(nullptr, pos2, this->Whoseturn);}
            std::cout << "The move you were trying to make is not valid because it would leave your king attacked." << std::endl;
            return false;
        }

//        std::cout << "Thank you. This is a valid move." << std::endl;

        // important: if the piece was a pawn, we set its first move to false, now it can no longer do two squares at once.
        if (pieceOne->Piecetype() == PAWN) {pieceOne->setFirstmove(false);}
        this->Board = Board;
        Board.printBoard();
        cout << "testsetsetldkfjsdkhk" <<  Board.getPiece(pos2)->Piecetype() << Board.getPiece(pos2)->getPieceNo() << endl;
        return true;

    }           // make turn function is over


    // Is Player current attacking spot dest??
    bool isAttackingSpot(Player current, Player other, Position dest) {
        bool attack = false;

        // can the king of the Player player attack the position dest?
        // I dont know why this was there before, move_valid does not take Board as an argument
//        attack = attack | player.getKing()->move_valid(Board, dest);
//        if(player.getKing()->move_valid(dest)) {attack = true;};
//        // can the queen attack the position dest?
//        if(player.getQueen()->getIsalive() == true and player.getQueen()->move_valid(dest)) {attack = true;}
//        // can either rook attack the position dest?
//        if (player.getRook(0)->getIsalive() == true and player.getRook(0)->move_valid(dest)) {attack = true;}
//        if (player.getRook(1)->getIsalive() == true and player.getRook(1)->move_valid(dest)) {attack = true;}
//        // can either bishop attack the position dest?
//        if (player.getBishop(0)->getIsalive() == true and player.getBishop(0)->move_valid(dest)) {attack = true;}
//        if (player.getBishop(1)->getIsalive() == true and player.getBishop(1)->move_valid(dest)) {attack = true;}
//        // can either knight attack the position dest?
//        if (player.getKnight(0)->getIsalive() == true and player.getKnight(0)->move_valid(dest)) {attack = true;}
//        if (player.getKnight(1)->getIsalive() == true and player.getKnight(1)->move_valid(dest)) {attack = true;}
//        // can either pawn attack the position dest? Remember: the pawn is the only piece that has a special capturing direction
//        if (player.getPawn(0)->getIsalive() == true and player.getPawn(0)->capture_valid(dest)) {attack = true;}
//        if (player.getPawn(1)->getIsalive() == true and player.getPawn(1)->capture_valid(dest)) {attack = true;}
//        if (player.getPawn(2)->getIsalive() == true and player.getPawn(2)->capture_valid(dest)) {attack = true;}
//        if (player.getPawn(3)->getIsalive() == true and player.getPawn(3)->capture_valid(dest)) {attack = true;}
//        if (player.getPawn(4)->getIsalive() == true and player.getPawn(4)->capture_valid(dest)) {attack = true;}
//        if (player.getPawn(5)->getIsalive() == true and player.getPawn(5)->capture_valid(dest)) {attack = true;}
//        if (player.getPawn(6)->getIsalive() == true and player.getPawn(6)->capture_valid(dest)) {attack = true;}
//        if (player.getPawn(7)->getIsalive() == true and player.getPawn(7)->capture_valid(dest)) {attack = true;}


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

    // Is other current player checking other player?
    // abaendern!!
    bool isCheck(Player current, Player other) {
        Position kingPos = other.getKing()->getPos();
        if (isAttackingSpot(current, other, kingPos)) {return true;}
        else {
//            cout << "There is no check on the board" << endl;
            return false;
        }
    }

    bool isCheckMate(Player current, Player other) {
        // only check for the case that current is checking other, because other can not be in check at this point
        if (!isCheck(current, other)) {return false;}
        Position kingPos = other.getKing()->getPos();

        // here maybe a lambda function to iterate over all possible positions the king can be in
        for (int i = -1; i<2; i++) {
            for (int j = -1; j<2; j++) {
                // if every spot around the king is either attacked or blocked by a piece of the same color
                // the getPiece method takes a pos
                // if one spot is NOT attacked and the spot is either free or a piece of the other color is on it, then it is not checkmate
//                if (!isAttackingSpot(current, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == other.getIswhite() ) {return false;}
                if (!isAttackingSpot(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j)) == nullptr ) {return false;}
                else if (!isAttackingSpot(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == current.getIswhite()) {return false;}
            }
        }
        return true;

    }
        // if king is attacked
        // and make_move does not work for any spot for the king
        // and there is no piece that can move in front of the king

    // this function is quite similar to the isCheckMate function
    // but actually, we have to make sure that no piece can move. Not a single one.
    bool isStaleMate(Player current, Player other) {
        if (isCheck(current, other)) {return false;}
        Position kingPos = other.getKing()->getPos();
        // here maybe a lambda function to iterate over all possible positions the king can be in
        for (int i = -1; i<2; i++) {
            for (int j = -1; j<2; j++) {
                // if every spot around the king is either attacked or blocked by a piece of the same color
                // the getPiece method takes a pos
//                if (!isAttackingSpot(current, kingPos.shiftPos(i, j)) or this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == other.getIswhite() ) {return false;}
                if (!isAttackingSpot(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j)) == nullptr ) {return false;}
                else if (!isAttackingSpot(current, other, kingPos.shiftPos(i, j)) and this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == current.getIswhite()) {return false;}
                // here, we have to iterate over the pieces on the board and see if any of them can move.
                else if (true) {return false;}
            }
        }
        return true;

    }
        // king is not attacked
        // but make_move does not work, because all of the fields are attacked
        // and the player can not move any other piece, so make_move does not work for any other piece either


    // this method is responsible for keeping the game going
    void Game() {
        bool ok;

        GameState state = ACTIVE;
        while (state == ACTIVE or state == CHECK) {

            if (state == CHECK) {std::cout << "You are in check. React." << std::endl;}

            // create two players, current and other
            Player current;
            Player other;
            if (this->Whoseturn == true) {current = Board.getPlayerWhite(); other = Board.getPlayerBlack(); cout << "WHITES MOVE, move number " << move_count << endl;}
            else {other = Board.getPlayerWhite(); current = Board.getPlayerBlack(); cout << "BLACKS MOVE, move number " << move_count  << endl;}

            Move move = current.getMove();

            // Remember: Maketurn takes the input from the current player and judges if the move is valid
            // judging by how the board is set up in this moment

            ok = this->Maketurn(current, other, move);

            cout << "test right before printborad" << endl;

            cout << typeid(Board.getPiece(move.getLast())).name() << endl;

//            this->Board.printBoard();


            if (ok) {cout << "Thank you. This is a valid move given the constellation of pieces on the board." << endl;}
            if (!ok) {cout << "Try again!" << endl;}

//            break;

            // I want the player to reenter the move, until the move is valid.
            while (!ok) {
                std::cout << "The Maketurn function says: The move you provided is not valid. Please reenter your move." << std::endl;
                state = ERROR;
                Move move = current.getMove();
                ok = this->Maketurn(current, other, move);
                if (ok) {cout << "Thank you. This is a valid move given the constellation of pieces on the board." << endl;}
                if (!ok) {cout << "Try again!" << endl;}
            }



            bool gameOver = this->isCheckMate(current, other);

            // if the game is over, determine the winner and break the while loop
            if (gameOver) {
                if (this->Whoseturn) {state = WHITEWINS; std::cout << "Checkmate. White won." << std::endl;}
                else {state = BLACKWINS; std::cout << "Checkmate. Black won." << std::endl;}
                Board.printBoard();
                break;
            }
            if (!gameOver) {cout << "No Checkmate, game continues." << endl;}



            bool draw = this->isStaleMate(current, other);

            if (draw) {std::cout << "The game is drawn." << std::endl; state = DRAW; break;}

            if (!draw) {cout << "No Stalemate, game continues." << endl;}



            // after white, it's black and after black, it's white.
            bool ischeck = this->isCheck(current, other);
            if (ischeck) {
                std::cout << "Your move is valid. The other player is in check and has to respond to that." << std::endl;
                current.showOutput(state);
                continue;
            }
            std::cout << "Your move is valid. There is no checking happening whatsoever. The game continues." << std::endl;
            this->Whoseturn = !Whoseturn;
            current.showOutput(state);

//            break;

            cout << "Last Move" << move.getLast().getX() << move.getLast().getY() << endl;
            bool asdf = this->Board.getPiece(Position(1,2)) == nullptr;
            cout << asdf << endl;
            cout << Board.getPiece(Position(1,2))->getPos().getX() << " " << Board.getPiece(move.getLast())->getPos().getY() << endl;

            for (int i = 0; i<8; i++) {
                for (int j = 0; j<8; j++) {
                    if (Board.getPiece(Position(j, i)) == nullptr) {
                        std::cout << 0 << " ";
                    }
                    else if (Board.getPiece(Position(j, i))->Piecetype() == PAWN) {std::cout << "P" << " ";}
                    else if (Board.getPiece(Position(j, i))->Piecetype() == KNIGHT) {std::cout << "N" << " ";}
                    else if (Board.getPiece(Position(j, i))->Piecetype() == BISHOP) {std::cout << "B" << " ";}
                    else if (Board.getPiece(Position(j, i))->Piecetype() == ROOK) {std::cout << "R" << " ";}
                    else if (Board.getPiece(Position(j, i))->Piecetype() == KING) {std::cout << "K" << " ";}
                    else if (Board.getPiece(Position(j, i))->Piecetype() == QUEEN) {std::cout << "Q" << " ";}
                    else {std::cout << "2" << " ";}
                }
                std::cout << std::endl;
            }
//            Board.printBoard();


            this->move_list.push_back(move.getFirst().getX());
            this->move_list.push_back(move.getFirst().getY());
            this->move_list.push_back(move.getLast().getX());
            this->move_list.push_back(move.getLast().getY());
            this->move_count += 1;
        }
    }


};



#endif // TEST_H
