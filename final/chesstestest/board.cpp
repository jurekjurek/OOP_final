#include "board.h"



ChessBoard::ChessBoard(Player *white, Player *black)  {
    // fill
    for (int i = 0; i < 8; i++) {
        for (int j = 2; j < 6; j++) {
            Board[i][j] = nullptr;
        }
    }

    // double check that the colors are correct
    white->setIswhite(true);
    black->setIswhite(false);
    this->White = white;
    this->Black = black;
//    this->White->setIswhite(true);
//    this->Black->setIswhite(false);
    // white
    // pieces
    Board[0][0] = White->getRook(0);
    Board[1][0] = White->getKnight(0);
    Board[2][0] = White->getBishop(0);
    Board[3][0] = White->getQueen();
    Board[4][0] = White->getKing();
    Board[5][0] = White->getBishop(1);
    Board[6][0] = White->getKnight(1);
    Board[7][0] = White->getRook(1);

    // pawns
    Board[0][1] = White->getPawn(0);
    Board[1][1] = White->getPawn(1);
    Board[2][1] = White->getPawn(2);
    Board[3][1] = White->getPawn(3);
    Board[4][1] = White->getPawn(4);
    Board[5][1] = White->getPawn(5);
    Board[6][1] = White->getPawn(6);
    Board[7][1] = White->getPawn(7);

    // black
    // pieces
    Board[0][7] = Black->getRook(0);
    Board[1][7] = Black->getKnight(0);
    Board[2][7] = Black->getBishop(0);
    Board[3][7] = Black->getQueen();
    Board[4][7] = Black->getKing();
    Board[5][7] = Black->getBishop(1);
    Board[6][7] = Black->getKnight(1);
    Board[7][7] = Black->getRook(1);

    // pawns
    Board[0][6] = Black->getPawn(0);
    Board[1][6] = Black->getPawn(1);
    Board[2][6] = Black->getPawn(2);
    Board[3][6] = Black->getPawn(3);
    Board[4][6] = Black->getPawn(4);
    Board[5][6] = Black->getPawn(5);
    Board[6][6] = Black->getPawn(6);
    Board[7][6] = Black->getPawn(7);

}

// Default constructor
ChessBoard::ChessBoard()  {
    // fill
    for (int i = 0; i < 8; i++) {
        for (int j = 2; j < 6; j++) {
            Board[i][j] = nullptr;
        }
    }
    this->White->setIswhite(true);
    this->Black->setIswhite(false);
    // white
    // pieces
    Board[0][0] = White->getRook(0);
    Board[1][0] = White->getKnight(0);
    Board[2][0] = White->getBishop(0);
    Board[3][0] = White->getQueen();
    Board[4][0] = White->getKing();
    Board[5][0] = White->getBishop(1);
    Board[6][0] = White->getKnight(1);
    Board[7][0] = White->getRook(1);

    // pawns
    Board[0][1] = White->getPawn(0);
    Board[1][1] = White->getPawn(1);
    Board[2][1] = White->getPawn(2);
    Board[3][1] = White->getPawn(3);
    Board[4][1] = White->getPawn(4);
    Board[5][1] = White->getPawn(5);
    Board[6][1] = White->getPawn(6);
    Board[7][1] = White->getPawn(7);

    // black
    // pieces
    Board[0][7] = Black->getRook(0);
    Board[1][7] = Black->getKnight(0);
    Board[2][7] = Black->getBishop(0);
    Board[3][7] = Black->getQueen();
    Board[4][7] = Black->getKing();
    Board[5][7] = Black->getBishop(1);
    Board[6][7] = Black->getKnight(1);
    Board[7][7] = Black->getRook(1);

    // pawns
    Board[0][6] = Black->getPawn(0);
    Board[1][6] = Black->getPawn(1);
    Board[2][6] = Black->getPawn(2);
    Board[3][6] = Black->getPawn(3);
    Board[4][6] = Black->getPawn(4);
    Board[5][6] = Black->getPawn(5);
    Board[6][6] = Black->getPawn(6);
    Board[7][6] = Black->getPawn(7);

}




Player* ChessBoard::getPlayerBlack() {
    return this->Black;
}

Player* ChessBoard::getPlayerWhite() {
    return this->White;
}

void ChessBoard::setPlayerWhite(Player* white)
{
    this->White = white;
}

void ChessBoard::setPlayerBlack(Player* black)
{
    this->Black = black;
}



// this function prints the board in the console just to see what the actual board constellation is and if QT messes up
// White pieces are printed uppercase, black pieces lowercase
void ChessBoard::printBoard() {
    for (int i = 7; i>=0; i--) {
        for (int j = 0; j<8; j++) {
            if (Board[j][i] == nullptr) {
                std::cout << 0 << " ";
            }
            else if (Board[j][i]->Piecetype() == PAWN and Board[j][i]->getIswhite() == true) {std::cout << "P" << " ";}
            else if (Board[j][i]->Piecetype() == KNIGHT and Board[j][i]->getIswhite() == true) {std::cout << "N" << " ";}
            else if (Board[j][i]->Piecetype() == BISHOP and Board[j][i]->getIswhite() == true) {std::cout << "B" << " ";}
            else if (Board[j][i]->Piecetype() == ROOK and Board[j][i]->getIswhite() == true) {std::cout << "R" << " ";}
            else if (Board[j][i]->Piecetype() == KING and Board[j][i]->getIswhite() == true) {std::cout << "K" << " ";}
            else if (Board[j][i]->Piecetype() == QUEEN and Board[j][i]->getIswhite() == true) {std::cout << "Q" << " ";}
            else if (Board[j][i]->Piecetype() == PAWN and Board[j][i]->getIswhite() == false) {std::cout << "p" << " ";}
            else if (Board[j][i]->Piecetype() == KNIGHT and Board[j][i]->getIswhite() == false) {std::cout << "n" << " ";}
            else if (Board[j][i]->Piecetype() == BISHOP and Board[j][i]->getIswhite() == false) {std::cout << "b" << " ";}
            else if (Board[j][i]->Piecetype() == ROOK and Board[j][i]->getIswhite() == false) {std::cout << "r" << " ";}
            else if (Board[j][i]->Piecetype() == KING and Board[j][i]->getIswhite() == false) {std::cout << "k" << " ";}
            else if (Board[j][i]->Piecetype() == QUEEN and Board[j][i]->getIswhite() == false) {std::cout << "q" << " ";}
            else {std::cout << "2" << " ";}
        }
        std::cout << std::endl;
    }
}

Piece* ChessBoard::getPiece(Position pos) {
    return Board[pos.getX()][pos.getY()];
}


void ChessBoard::setPiece(Piece* piece, Position pos) {
    // in case we just want to free a spot, a nullptr does not have a color
    if (piece == nullptr) {this->Board[pos.getX()][pos.getY()] = nullptr;}
    else if (piece->getIswhite()) {
        if (piece->Piecetype() == KING) {
            this->Board[pos.getX()][pos.getY()] = this->White->getKing();
            this->White->getKing()->setPos(pos);
        }
        else if (piece->Piecetype() == QUEEN) {
            this->Board[pos.getX()][pos.getY()] = this->White->getQueen();
            this->White->getQueen()->setPos(pos);
        }
        else if (piece->Piecetype() == ROOK) {
            this->Board[pos.getX()][pos.getY()] = this->White->getRook(piece->getPieceNo());
            this->White->getRook(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == KNIGHT) {
            this->Board[pos.getX()][pos.getY()] = this->White->getKnight(piece->getPieceNo());
            this->White->getKnight(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == BISHOP) {
            this->Board[pos.getX()][pos.getY()] = this->White->getBishop(piece->getPieceNo());
            this->White->getBishop(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == PAWN) {
            this->Board[pos.getX()][pos.getY()] = this->White->getPawn(piece->getPieceNo());
            this->White->getPawn(piece->getPieceNo())->setPos(pos);
        }
    }

    else if (!piece->getIswhite()) {
        if (piece->Piecetype() == KING) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getKing();
            this->Black->getKing()->setPos(pos);
        }
        else if (piece->Piecetype() == QUEEN) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getQueen();
            this->Black->getQueen()->setPos(pos);
        }
        else if (piece->Piecetype() == ROOK) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getRook(piece->getPieceNo());
            this->Black->getRook(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == KNIGHT) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getKnight(piece->getPieceNo());
            this->Black->getKnight(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == BISHOP) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getBishop(piece->getPieceNo());
            this->Black->getBishop(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == PAWN) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getPawn(piece->getPieceNo());
            this->Black->getPawn(piece->getPieceNo())->setPos(pos);
        }
    }
}






























