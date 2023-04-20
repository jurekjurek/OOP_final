#ifndef GAME_H
#define GAME_H

#include "board.h"

/*  The most important class
 *  Here, the game is being controlled.
 *
 *
 *
*/

class ChessGame {
private:
    Player White;
    Player Black;
    ChessBoard Board;
    bool Whoseturn;         // true for white, false for black
    GameState state;
public:
    // when the class is called, a new game is generated
    // Black is not white, White is white
    ChessGame() : Black(false), White(true) {
        this->Black = new Player(false);
        this->White = new Player(true);
        this->Board = ChessBoard(White, Black);
        this->Whoseturn = true;
        this->state = ACTIVE;
    }

    bool Maketurn() {
        // which one is the current, which one is the next player?

        Player current;
        Player other;
        if (this->Whoseturn == true) {this->White = current; this->Black = other;}
        else {this->White = other; this->Black = current;}

        Move move = current.getMove();

        Piece* pieceOne = this->Board.getPiece(move.getFirst());
        // if not a piece -> return ERROR!

        if (current.getIswhite() != pieceOne->getIswhite()) {return false;}

        // Now, let's check for other pieces in the destination spot, for example
        Piece* pieceTwo = this->Board.getPiece(move.getLast());

        // if piece at destination and piece at source have the same color -> error
        if (pieceTwo->getIswhite() == pieceOne->getIswhite()) {return false;}

        bool checkMove = pieceOne->move_valid(move.getLast());
        if (!checkMove) {return false;}
        // PIECE ONE GETS A NEW POSITION
        pieceOne->setPos(move.getLast());
        // setPiece takes a pointer to a piece and a position
        // THE BOARD NOW ALSO GETS THE INFORMATION OF THE NEW POSITION OF PIECE ONE
        this->Board.setPiece(nullptr, move.getFirst());
        //
        this->Board.setPiece(pieceOne, move.getLast());

        // collect all captured pieces at position -1, -1, IDK...

        pieceTwo->setPos(Position(-1, -1));
        pieceTwo->setIsalive(false);
        // maybe there could be a piece of the given type appearing in the corner or so... let's see

        // now, this move that we just made is only valid if our king (so the king of the current player) is still safe
        // so not in check
        bool kingStillSafe = isCheck(other, current);

        if (!kingStillSafe) {
            pieceOne->setPos(move.getFirst());
            if (pieceTwo != nullptr) {
                pieceTwo->setPos(move.getLast());
                pieceTwo->setIsalive(true);

                // we have to provide the reference to a certain piece, not the piece itself
                this->Board.setPiece(pieceTwo, move.getLast());
            }
            else {this->Board.setPiece(nullptr, move.getLast());}
            return false;
        }

    }           // make turn function is over


    // Is Player player attacking spot dest??
    bool isAttackingSpot(Player player, Position dest) {
        bool attack = false;

        // can the king of the Player player attack the position dest?
        // I dont know why this was there before, move_valid does not take Board as an argument
//        attack = attack | player.getKing()->move_valid(Board, dest);
        if(player.getKing()->move_valid(dest)) {attack = true;};
        // can the queen attack the position dest?
        if(player.getQueen()->getIsalive() == true and player.getQueen()->move_valid(dest)) {attack = true;}
        // can either rook attack the position dest?
        if (player.getRook(0)->getIsalive() == true and player.getRook(0)->move_valid(dest)) {attack = true;}
        if (player.getRook(1)->getIsalive() == true and player.getRook(1)->move_valid(dest)) {attack = true;}
        // can either bishop attack the position dest?
        if (player.getBishop(0)->getIsalive() == true and player.getBishop(0)->move_valid(dest)) {attack = true;}
        if (player.getBishop(1)->getIsalive() == true and player.getBishop(1)->move_valid(dest)) {attack = true;}
        // can either knight attack the position dest?
        if (player.getKnight(0)->getIsalive() == true and player.getKnight(0)->move_valid(dest)) {attack = true;}
        if (player.getKnight(1)->getIsalive() == true and player.getKnight(1)->move_valid(dest)) {attack = true;}
        // can either pawn attack the position dest? Remember: the pawn is the only piece that has a special capturing direction
        if (player.getPawn(0)->getIsalive() == true and player.getPawn(0)->capture_valid(dest)) {attack = true;}
        if (player.getPawn(1)->getIsalive() == true and player.getPawn(1)->capture_valid(dest)) {attack = true;}
        if (player.getPawn(2)->getIsalive() == true and player.getPawn(2)->capture_valid(dest)) {attack = true;}
        if (player.getPawn(3)->getIsalive() == true and player.getPawn(3)->capture_valid(dest)) {attack = true;}
        if (player.getPawn(4)->getIsalive() == true and player.getPawn(4)->capture_valid(dest)) {attack = true;}
        if (player.getPawn(5)->getIsalive() == true and player.getPawn(5)->capture_valid(dest)) {attack = true;}
        if (player.getPawn(6)->getIsalive() == true and player.getPawn(6)->capture_valid(dest)) {attack = true;}
        if (player.getPawn(7)->getIsalive() == true and player.getPawn(7)->capture_valid(dest)) {attack = true;}

        return attack;
    }

    // Is other current player checking other player?
    // abaendern!!
    bool isCheck(Player current, Player other) {
        Position kingPos = other.getKing()->getPos();
        if (isAttackingSpot(current, kingPos)) {return true;}
        else {return false;}
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
                if (!isAttackingSpot(current, kingPos.shiftPos(i, j)) or this->Board.getPiece(kingPos.shiftPos(i, j))->getIswhite() == other.getIswhite() ) {return false;}
            }
        }

    }
        // if king is attacked
        // and make_move does not work for any spot for the king
        // and there is no piece that can move in front of the king

    bool isStaleMate() {}
        // king is not attacked
        // but make_move does not work, because all of the fields are attacked
        // and the player can not move any other piece, so make_move does not work for any other piece either


    // this method is responsible for keeping the game going
    void Game() {
        GameState state = ACTIVE;
        while (state == ACTIVE or state == CHECK) {

            // create two players, current and other
            Player current;
            Player other;
            if (this->Whoseturn == true) {this->White = current; this->Black = other;}
            else {this->White = other; this->Black = current;}

            // Remember: Maketurn takes the input from the current player and judges if the move is valid
            // judging by how the board is set up in this moment
            bool ok = this->Maketurn();
            if (!ok) {state = ERROR; break;}


            bool gameOver = this->isCheckMate(current, other);

            // if the game is over, determine the winner and break the while loop
            if (gameOver) {
                if (this->Whoseturn) {state = WHITEWINS;}
                else {state = BLACKWINS;}
                break;
            }

            bool draw = this->isStaleMate();

            if (draw) {state = DRAW; break;}


            // after white, it's black and after black, it's white.
            this->Whoseturn = !Whoseturn;

        }
    }


};


#endif // GAME_H
