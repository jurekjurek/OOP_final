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
    Player White;
    Player Black;
    ChessBoard Board;
    bool Whoseturn;         // true for white, false for black
    GameState state;
public:
    // when the class is called, a new game is generated
    // Black is not white, White is white
    ChessGame() : Black(false), White(true) {
//        this->Black = Player(false);
//        this->White = Player(true);
        this->Board = ChessBoard(White, Black);
        this->Whoseturn = true;
        this->state = ACTIVE;
    }

    bool Maketurn(Player current, Player other) {
        // which one is the current, which one is the next player?

//        Player current;
//        Player other;
//        if (this->Whoseturn == true) {this->White = current; this->Black = other;}
//        else {this->White = other; this->Black = current;}
        this->White = Player(true);
        this->Black = Player(false);
        ChessBoard Board(White, Black);
        std::cout << "Maketurn function executed" << std::endl;

        Move move = current.getMove();

        std::cout << "Got the move, now to check if there's a piece at that spot." << std::endl;

        std::cout << "x and y of first: " << move.getFirst().getX() << " and " << move.getFirst().getY() << std::endl;
        std::cout << "x and y of last: " << move.getLast().getX() << " and " << move.getLast().getY() << std::endl;

        Piece pieceOne = this->Board.getPiece(move.getFirst());
        Piece* pieceOne_ptr = this->Board.getPiecePointer(move.getFirst());

        // Now, piece in spot two?
        Piece pieceTwo = this->Board.getPiece(move.getLast());
        Piece* pieceTwo_ptr = this->Board.getPiecePointer(move.getLast());
        if (pieceTwo_ptr == nullptr) {std::cout << "No Piece at destination spot" << std::endl;}

        if (pieceOne_ptr == nullptr) {std::cout << "There is no piece at the starting position! Pointer is nullptr." << std::endl; return false;}

        std::cout << "Typeinfo " << typeid(pieceOne).name() << " Pos " << pieceOne.getPos().getY()  << std::endl;

//        pieceOne->Piecetype();
        pieceOne.Piecetype();


        // okay, lets test all kinds of things here

        std::cout << "Player colors, 1 " << current.getIswhite() <<  " 2 " << other.getIswhite() << " Piece colors, 1 " << pieceOne.getIswhite() << " 2 " << pieceTwo.getIswhite() << " Piece positions 1 x y " << pieceOne.getPos().getX() << pieceOne.getPos().getY() << " 2 x y " << pieceTwo.getPos().getX() << pieceTwo.getPos().getY() << std::endl;

        if (current.getIswhite() != pieceOne.getIswhite()) {
            std::cout << "color of current player is not equal to the color of the piece you're trying to move. Player: " << current.getIswhite() << " Piece: " << pieceOne.getIswhite() << std::endl;
            return false;
        }



        // if piece at destination and piece at source have the same color -> error
        if (pieceTwo.getIswhite() == pieceOne.getIswhite()) {std::cout << "The spot you want to move to is blocked by a piece of your color. " << pieceTwo.getIswhite() << "" << pieceOne.getIswhite() << std::endl; return false;}

        bool checkMove = pieceOne.move_valid(move.getLast());

        // if the move is not valid -> exit
        if (!checkMove) {std::cout << "The move you are trying to make is not a valid move for this piece." << std::endl; return false;}

        // PIECE ONE GETS A NEW POSITION
        pieceOne.setPos(move.getLast());
        std::cout << "Just changed the position of your piece to the new position" << std::endl;

        // setPiece takes a pointer to a piece and a position
        // THE BOARD NOW ALSO GETS THE INFORMATION OF THE NEW POSITION OF PIECE ONE
        this->Board.setPiece(nullptr, move.getFirst());
        std::cout << "We set the now empty spot to null." << std::endl;
        //
        this->Board.setPiece(&pieceOne, move.getLast());
        std::cout << "and told the board where your piece is now." << std::endl;

        // collect all captured pieces at position -1, -1, IDK...

        pieceTwo.setPos(Position(-1, -1));
        pieceTwo.setIsalive(false);
        // maybe there could be a piece of the given type appearing in the corner or so... let's see

        // now, this move that we just made is only valid if our king (so the king of the current player) is still safe
        // so not in check
        bool kingStillSafe = isCheck(other, current);

        if (!kingStillSafe) {
            pieceOne.setPos(move.getFirst());
            if (pieceTwo_ptr != nullptr) {
                pieceTwo.setPos(move.getLast());
                pieceTwo.setIsalive(true);

                // we have to provide the reference to a certain piece, not the piece itself
                this->Board.setPiece(&pieceTwo, move.getLast());
            }
            else {this->Board.setPiece(nullptr, move.getLast());}
            std::cout << "The move you were trying to make is not valid because it would leave your king attacked." << std::endl;
            return false;
        }

        std::cout << "Thank you. This is a valid move." << std::endl;
        return true;

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
                if (!isAttackingSpot(current, kingPos.shiftPos(i, j)) or this->Board.getPiece(kingPos.shiftPos(i, j)).getIswhite() == other.getIswhite() ) {return false;}
            }
        }

    }
        // if king is attacked
        // and make_move does not work for any spot for the king
        // and there is no piece that can move in front of the king

    // this function is quite similar to the isCheckMate function
    bool isStaleMate(Player current, Player other) {
        if (isCheck(current, other)) {return false;}
        Position kingPos = other.getKing()->getPos();
        // here maybe a lambda function to iterate over all possible positions the king can be in
        for (int i = -1; i<2; i++) {
            for (int j = -1; j<2; j++) {
                // if every spot around the king is either attacked or blocked by a piece of the same color
                // the getPiece method takes a pos
                if (!isAttackingSpot(current, kingPos.shiftPos(i, j)) or this->Board.getPiece(kingPos.shiftPos(i, j)).getIswhite() == other.getIswhite() ) {return false;}
            }
        }

    }
        // king is not attacked
        // but make_move does not work, because all of the fields are attacked
        // and the player can not move any other piece, so make_move does not work for any other piece either


    // this method is responsible for keeping the game going
    void Game() {
        GameState state = ACTIVE;
        while (state == ACTIVE or state == CHECK) {
            if (state == CHECK) {std::cout << "You are in check. React." << std::endl;}

            // create two players, current and other
            Player current;
            Player other;
            if (this->Whoseturn == true) {this->White = current; this->Black = other;}
            else {this->White = other; this->Black = current;}

            // Remember: Maketurn takes the input from the current player and judges if the move is valid
            // judging by how the board is set up in this moment
            bool ok = this->Maketurn(current, other);

            // I want the player to reenter the move, until the move is valid.
            while (!ok) {
                std::cout << "The Maketurn function says: The move you provided is not valid. Please reenter your move." << std::endl;
                state = ERROR;
                ok = this->Maketurn(current, other);
            }


            bool gameOver = this->isCheckMate(current, other);

            // if the game is over, determine the winner and break the while loop
            if (gameOver) {
                if (this->Whoseturn) {state = WHITEWINS; std::cout << "Checkmate. White won." << std::endl;}
                else {state = BLACKWINS; std::cout << "Checkmate. Black won." << std::endl;}
                break;
            }

            bool draw = this->isStaleMate(current, other);

            if (draw) {std::cout << "The game is drawn." << std::endl; state = DRAW; break;}


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
        }
    }


};



#endif // TEST_H
