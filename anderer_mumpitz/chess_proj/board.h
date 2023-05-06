#ifndef BOARD_H
#define BOARD_H
#include "player.h"

/*  The Borad class is an 8x8 array of pointers to pieces.
 *
 *  This class is responsible for nothing more than being a board, so being able to hold pieces and set pieces to given positions
 *
 *
*/

class ChessBoard {
private:
    Piece* Board[8][8];
    Player White;
    Player Black;
public:
    // constructor sets all the pointers to zero
    ChessBoard(Player white, Player black) {
        this->White = white;
        this->Black = black;
        // fill
        for (int i = 0; i < 8; i++) {
            for (int j = 2; j < 6; j++) {
                this->Board[i][j] = nullptr;
            }
        }
        // white
        // pieces

        std::cout << "Look at the type of certain pieces." << std::endl;

        std::cout << "Typeinfo " << typeid(white.getKnight(0)).name() << " Queen " <<  typeid(white.getKnight(1)).name() << std::endl;

        this->Board[0][0] = white.getRook(0);
        this->Board[1][0] = white.getKnight(0);
        this->Board[2][0] = white.getBishop(0);
        this->Board[3][0] = white.getQueen();
        this->Board[4][0] = white.getKing();
        this->Board[5][0] = white.getBishop(1);
        this->Board[6][0] = white.getKnight(1);
        this->Board[7][0] = white.getRook(1);

        // pawns
        this->Board[0][1] = white.getPawn(0);
        this->Board[1][1] = white.getPawn(1);
        this->Board[2][1] = white.getPawn(2);
        this->Board[3][1] = white.getPawn(3);
        this->Board[4][1] = white.getPawn(4);
        this->Board[5][1] = white.getPawn(5);
        this->Board[6][1] = white.getPawn(6);
        this->Board[7][1] = white.getPawn(7);

        // black
        // pieces
        this->Board[0][7] = black.getRook(0);
        this->Board[1][7] = black.getKnight(0);
        this->Board[2][7] = black.getBishop(0);
        this->Board[3][7] = black.getQueen();
        this->Board[4][7] = black.getKing();
        this->Board[5][7] = black.getBishop(1);
        this->Board[6][7] = black.getKnight(1);
        this->Board[7][7] = black.getRook(1);

        // pawns
        this->Board[0][6] = black.getPawn(0);
        this->Board[1][6] = black.getPawn(1);
        this->Board[2][6] = black.getPawn(2);
        this->Board[3][6] = black.getPawn(3);
        this->Board[4][6] = black.getPawn(4);
        this->Board[5][6] = black.getPawn(5);
        this->Board[6][6] = black.getPawn(6);
        this->Board[7][6] = black.getPawn(7);

        // now that the board knows where the different pieces are, we can assign the positions also to the pieces
        // white

        this->Board[0][0]->setPos(Position(0,0));         // rook
        this->Board[0][0]->setIswhite(true);
        this->Board[1][0]->setPos(Position(1,0));         // knight
        this->Board[1][0]->setIswhite(true);
        this->Board[2][0]->setPos(Position(2,0));
        this->Board[2][0]->setIswhite(true);
        this->Board[3][0]->setPos(Position(3,0));
        this->Board[3][0]->setIswhite(true);
        this->Board[4][0]->setPos(Position(4,0));
        this->Board[4][0]->setIswhite(true);
        this->Board[5][0]->setPos(Position(5,0));
        this->Board[5][0]->setIswhite(true);
        this->Board[6][0]->setPos(Position(6,0));
        this->Board[6][0]->setIswhite(true);
        this->Board[7][0]->setPos(Position(7,0));
        this->Board[7][0]->setIswhite(true);
        this->Board[0][1]->setPos(Position(0,1));
        this->Board[0][1]->setIswhite(true);
        this->Board[1][1]->setPos(Position(1,1));
        this->Board[1][1]->setIswhite(true);
        this->Board[2][1]->setPos(Position(2,1));
        this->Board[2][1]->setIswhite(true);
        this->Board[3][1]->setPos(Position(3,1));
        this->Board[3][1]->setIswhite(true);
        this->Board[4][1]->setPos(Position(4,1));
        this->Board[4][1]->setIswhite(true);
        this->Board[5][1]->setPos(Position(5,1));
        this->Board[5][1]->setIswhite(true);
        this->Board[6][1]->setPos(Position(6,1));
        this->Board[6][1]->setIswhite(true);
        this->Board[7][1]->setPos(Position(7,1));
        this->Board[7][1]->setIswhite(true);

        // black

        this->Board[0][7]->setPos(Position(0,7));         // rook
        this->Board[0][7]->setIswhite(true);
        this->Board[1][7]->setPos(Position(1,7));         // knight
        this->Board[1][7]->setIswhite(true);
        this->Board[2][7]->setPos(Position(2,7));
        this->Board[2][7]->setIswhite(true);
        this->Board[3][7]->setPos(Position(3,7));
        this->Board[3][7]->setIswhite(true);
        this->Board[4][7]->setPos(Position(4,7));
        this->Board[4][7]->setIswhite(true);
        this->Board[5][7]->setPos(Position(5,7));
        this->Board[5][7]->setIswhite(true);
        this->Board[6][7]->setPos(Position(6,7));
        this->Board[6][7]->setIswhite(true);
        this->Board[7][7]->setPos(Position(7,7));
        this->Board[7][7]->setIswhite(true);
        this->Board[0][6]->setPos(Position(0,6));
        this->Board[0][6]->setIswhite(true);
        this->Board[1][6]->setPos(Position(1,6));
        this->Board[1][6]->setIswhite(true);
        this->Board[2][6]->setPos(Position(2,6));
        this->Board[2][6]->setIswhite(true);
        this->Board[3][6]->setPos(Position(3,6));
        this->Board[3][6]->setIswhite(true);
        this->Board[4][6]->setPos(Position(4,6));
        this->Board[4][6]->setIswhite(true);
        this->Board[5][6]->setPos(Position(5,6));
        this->Board[5][6]->setIswhite(true);
        this->Board[6][6]->setPos(Position(6,6));
        this->Board[6][6]->setIswhite(true);
        this->Board[7][6]->setPos(Position(7,6));
        this->Board[7][6]->setIswhite(true);

//        white.getRook(0)->setPos(Position(0,0));
//        white.getKnight(0)->setPos(Position(1,0));
//        white.getBishop(0)->setPos(Position(2,0));
//        white.getQueen()->setPos(Position(3,0));
//        white.getKing()->setPos(Position(4,0));
//        white.getBishop(1)->setPos(Position(5,0));
//        white.getKnight(1)->setPos(Position(6,0));
//        white.getRook(1)->setPos(Position(7,0));

//        white.getPawn(0)->setPos(Position(0,1));
//        white.getPawn(1)->setPos(Position(1,1));
//        white.getPawn(2)->setPos(Position(2,1));
//        white.getPawn(3)->setPos(Position(3,1));
//        white.getPawn(4)->setPos(Position(4,1));
//        white.getPawn(5)->setPos(Position(5,1));
//        white.getPawn(6)->setPos(Position(6,1));
//        white.getPawn(7)->setPos(Position(7,1));
//        // black
//        black.getRook(0)->setPos(Position(0,7));
//        black.getKnight(0)->setPos(Position(1,7));
//        black.getBishop(0)->setPos(Position(2,7));
//        black.getQueen()->setPos(Position(3,7));
//        black.getKing()->setPos(Position(4,7));
//        black.getBishop(1)->setPos(Position(5,7));
//        black.getKnight(1)->setPos(Position(6,7));
//        black.getRook(1)->setPos(Position(7,7));

//        black.getPawn(0)->setPos(Position(0,6));
//        black.getPawn(1)->setPos(Position(1,6));
//        black.getPawn(2)->setPos(Position(2,6));
//        black.getPawn(3)->setPos(Position(3,6));
//        black.getPawn(4)->setPos(Position(4,6));
//        black.getPawn(5)->setPos(Position(5,6));
//        black.getPawn(6)->setPos(Position(6,6));
//        black.getPawn(7)->setPos(Position(7,6));


        std::cout << "Look at the positions of certain pieces." << std::endl;
        std::cout << Board[6][1]->getPos().getX() << " " << Board[6][1]->getPos().getY() << std::endl;

    }

    // default constructor

    ChessBoard() {
//        for (int i = 0; i < 8; i++) {
//            for (int j = 0; j < 8; j++) {
//                Board[i][j] = nullptr;
//            }
//        }
    }

    // getter and setter for pieces
    // getPiece returns A POINTER TO A PIECE!!!
    Piece getPiece(Position pos) {
        std::cout << "getPiece returns Piece at point " << pos.getX() << ", " << pos.getY() << std::endl;
        std::cout << "TESTTESETTEST" << std::endl;
        std::cout << this->Board[6][1]->getPos().getX() << " " << Board[6][1]->getPos().getY() << std::endl;
        std::cout << "Which is at position: " << this->Board[pos.getX()][pos.getY()]->getPos().getX() << ", " << this->Board[pos.getX()][pos.getY()]->getPos().getY() << std::endl;
        std::cout << "And has the color " << Board[pos.getX()][pos.getY()]->getIswhite() << std::endl;
        return *Board[pos.getX()][pos.getY()];
    }

    Piece* getPiecePointer(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }

    // set piece with given color to some position
    void setPiece(Piece* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }


};




#endif // BOARD_H
