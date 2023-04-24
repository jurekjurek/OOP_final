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
    Player black;
    Player white;
public:
    // constructor sets all the pointers to zero
    ChessBoard(Player White, Player Black) {
        // fill
        for (int i = 0; i < 8; i++) {
            for (int j = 2; j < 6; j++) {
                Board[i][j] = nullptr;
            }
        }

        // double check that the colors are correct
        this->white = White;
        this->black = Black;
        white.setIswhite(true);
        black.setIswhite(false);
        // white
        // pieces
        Board[0][0] = white.getRook(0);
        Board[1][0] = white.getKnight(0);
        Board[2][0] = white.getBishop(0);
        Board[3][0] = white.getQueen();
        Board[4][0] = white.getKing();
        Board[5][0] = white.getBishop(1);
        Board[6][0] = white.getKnight(1);
        Board[7][0] = white.getRook(1);

        // pawns
        Board[0][1] = white.getPawn(0);
        Board[1][1] = white.getPawn(1);
        Board[2][1] = white.getPawn(2);
        Board[3][1] = white.getPawn(3);
        Board[4][1] = white.getPawn(4);
        Board[5][1] = white.getPawn(5);
        Board[6][1] = white.getPawn(6);
        Board[7][1] = white.getPawn(7);

        // black
        // pieces
        Board[0][7] = black.getRook(0);
        Board[1][7] = black.getKnight(0);
        Board[2][7] = black.getBishop(0);
        Board[3][7] = black.getQueen();
        Board[4][7] = black.getKing();
        Board[5][7] = black.getBishop(1);
        Board[6][7] = black.getKnight(1);
        Board[7][7] = black.getRook(1);

        // pawns
        Board[0][6] = black.getPawn(0);
        Board[1][6] = black.getPawn(1);
        Board[2][6] = black.getPawn(2);
        Board[3][6] = black.getPawn(3);
        Board[4][6] = black.getPawn(4);
        Board[5][6] = black.getPawn(5);
        Board[6][6] = black.getPawn(6);
        Board[7][6] = black.getPawn(7);

        // now that the board knows where the different pieces are, we can assign the positions also to the pieces
        // white
        white.getRook(0)->setPos(Position(0,0));
        white.getKnight(0)->setPos(Position(1,0));
        white.getBishop(0)->setPos(Position(2,0));
        white.getQueen()->setPos(Position(3,0));
        white.getKing()->setPos(Position(4,0));
        white.getBishop(1)->setPos(Position(5,0));
        white.getKnight(1)->setPos(Position(6,0));
        white.getRook(1)->setPos(Position(7,0));

        white.getPawn(0)->setPos(Position(0,1));
        white.getPawn(1)->setPos(Position(1,1));
        white.getPawn(2)->setPos(Position(2,1));
        white.getPawn(3)->setPos(Position(3,1));
        white.getPawn(4)->setPos(Position(4,1));
        white.getPawn(5)->setPos(Position(5,1));
        white.getPawn(6)->setPos(Position(6,1));
        white.getPawn(7)->setPos(Position(7,1));

        white.getRook(0)->setIswhite(true);
        white.getKnight(0)->setIswhite(true);
        white.getBishop(0)->setIswhite(true);
        white.getQueen()->setIswhite(true);
        white.getKing()->setIswhite(true);
        white.getBishop(1)->setIswhite(true);
        white.getKnight(1)->setIswhite(true);
        white.getRook(1)->setIswhite(true);

        white.getPawn(0)->setIswhite(true);
        white.getPawn(1)->setIswhite(true);
        white.getPawn(2)->setIswhite(true);
        white.getPawn(3)->setIswhite(true);
        white.getPawn(4)->setIswhite(true);
        white.getPawn(5)->setIswhite(true);
        white.getPawn(6)->setIswhite(true);
        white.getPawn(7)->setIswhite(true);

        // black
        black.getRook(0)->setPos(Position(0,7));
        black.getKnight(0)->setPos(Position(1,7));
        black.getBishop(0)->setPos(Position(2,7));
        black.getQueen()->setPos(Position(3,7));
        black.getKing()->setPos(Position(4,7));
        black.getBishop(1)->setPos(Position(5,7));
        black.getKnight(1)->setPos(Position(6,7));
        black.getRook(1)->setPos(Position(7,7));

        black.getPawn(0)->setPos(Position(0,6));
        black.getPawn(1)->setPos(Position(1,6));
        black.getPawn(2)->setPos(Position(2,6));
        black.getPawn(3)->setPos(Position(3,6));
        black.getPawn(4)->setPos(Position(4,6));
        black.getPawn(5)->setPos(Position(5,6));
        black.getPawn(6)->setPos(Position(6,6));
        black.getPawn(7)->setPos(Position(7,6));

        black.getRook(0)->setIswhite(false);
        black.getKnight(0)->setIswhite(false);
        black.getBishop(0)->setIswhite(false);
        black.getQueen()->setIswhite(false);
        black.getKing()->setIswhite(false);
        black.getBishop(1)->setIswhite(false);
        black.getKnight(1)->setIswhite(false);
        black.getRook(1)->setIswhite(false);

        black.getPawn(0)->setIswhite(false);
        black.getPawn(1)->setIswhite(false);
        black.getPawn(2)->setIswhite(false);
        black.getPawn(3)->setIswhite(false);
        black.getPawn(4)->setIswhite(false);
        black.getPawn(5)->setIswhite(false);
        black.getPawn(6)->setIswhite(false);
        black.getPawn(7)->setIswhite(false);

        std::cout << "Okay, functionet das? " << Board[6][6]->getPos().getX() << " and " << Board[6][6]->getPos().getY() << std::endl;
        Board[6][6]->Piecetype();

    }

    // default constructor

    ChessBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Board[i][j] = nullptr;
            }
        }
    }

    void printBoard() {
        for (int i = 0; i<8; i++) {
            for (int j = 0; j<8; j++) {
                if (Board[j][i] == nullptr) {
                    std::cout << 0 << " ";
                }
                else if (Board[j][i]->Piecetype() == PAWN) {std::cout << "P" << " ";}
                else if (Board[j][i]->Piecetype() == KNIGHT) {std::cout << "N" << " ";}
                else if (Board[j][i]->Piecetype() == BISHOP) {std::cout << "B" << " ";}
                else if (Board[j][i]->Piecetype() == ROOK) {std::cout << "R" << " ";}
                else if (Board[j][i]->Piecetype() == KING) {std::cout << "K" << " ";}
                else if (Board[j][i]->Piecetype() == QUEEN) {std::cout << "Q" << " ";}
            }
            std::cout << std::endl;
        }
    }

    // getter and setter for pieces
    // getPiece returns A POINTER TO A PIECE!!!
    Piece getPiece(Position pos) {
//        switch (Board[pos.getX()][pos.getY()]->Piecetype()) {
//            case KING:
//                break;
//            case QUEEN:
//                break;
//            case KNIGHT:
//                break;
//            case BISHOP:
//                break;
//            case ROOK:
//                break;
//            case PAWN:
//                break;
//        }
        return this->black.getBishop(0); //*Board[pos.getX()][pos.getY()];
    }

    Piece* getPiecePointer(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }

    Knight* getKnight(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }

    Bishop* getBishop(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }

    Rook* getRook(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }

    Queen* getQueen(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }

    King* getKing(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }

    Pawn* getPawn(Position pos) {
        return Board[pos.getX()][pos.getY()];
    }




    // set piece with given color to some position
    void setPiece(Piece* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }

    void set(Pawn* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }

    void setPawn(Pawn* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }

    void setPawn(Pawn* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }

    void setPawn(Pawn* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }

    void setPawn(Pawn* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }

    void setPawn(Pawn* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }

    void setPawn(Pawn* piece, Position pos) {
        this->Board[pos.getX()][pos.getY()] = piece;
    }


};




#endif // BOARD_H
