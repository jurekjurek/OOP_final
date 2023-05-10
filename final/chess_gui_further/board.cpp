#include "board.h"



ChessBoard::ChessBoard(Player *white, Player *black)  {
    // fill
    for (int i = 0; i < 8; i++) {
        for (int j = 2; j < 6; j++) {
            Board[i][j] = nullptr;
        }
    }

    // double check that the colors are correct
    this->White = white;
    this->Black = black;
//    black = &Black;
//    white = &White;
//    White->setIswhite(true);
//    Black->setIswhite(false);
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

    // now that the board knows where the different pieces are, we can assign the positions also to the pieces
    // white
    White->getRook(0)->setPos(Position(0,0));
    White->getKnight(0)->setPos(Position(1,0));
    White->getBishop(0)->setPos(Position(2,0));
    White->getQueen()->setPos(Position(3,0));
    White->getKing()->setPos(Position(4,0));
    White->getBishop(1)->setPos(Position(5,0));
    White->getKnight(1)->setPos(Position(6,0));
    White->getRook(1)->setPos(Position(7,0));

    White->getPawn(0)->setPos(Position(0,1));
    White->getPawn(1)->setPos(Position(1,1));
    White->getPawn(2)->setPos(Position(2,1));
    White->getPawn(3)->setPos(Position(3,1));
    White->getPawn(4)->setPos(Position(4,1));
    White->getPawn(5)->setPos(Position(5,1));
    White->getPawn(6)->setPos(Position(6,1));
    White->getPawn(7)->setPos(Position(7,1));

    White->getRook(0)->setIswhite(true);
    White->getKnight(0)->setIswhite(true);
    White->getBishop(0)->setIswhite(true);
    White->getQueen()->setIswhite(true);
    White->getKing()->setIswhite(true);
    White->getBishop(1)->setIswhite(true);
    White->getKnight(1)->setIswhite(true);
    White->getRook(1)->setIswhite(true);

    White->getPawn(0)->setIswhite(true);
    White->getPawn(1)->setIswhite(true);
    White->getPawn(2)->setIswhite(true);
    White->getPawn(3)->setIswhite(true);
    White->getPawn(4)->setIswhite(true);
    White->getPawn(5)->setIswhite(true);
    White->getPawn(6)->setIswhite(true);
    White->getPawn(7)->setIswhite(true);

    // black
    Black->getRook(0)->setPos(Position(0,7));
    Black->getKnight(0)->setPos(Position(1,7));
    Black->getBishop(0)->setPos(Position(2,7));
    Black->getQueen()->setPos(Position(3,7));
    Black->getKing()->setPos(Position(4,7));
    Black->getBishop(1)->setPos(Position(5,7));
    Black->getKnight(1)->setPos(Position(6,7));
    Black->getRook(1)->setPos(Position(7,7));

    Black->getPawn(0)->setPos(Position(0,6));
    Black->getPawn(1)->setPos(Position(1,6));
    Black->getPawn(2)->setPos(Position(2,6));
    Black->getPawn(3)->setPos(Position(3,6));
    Black->getPawn(4)->setPos(Position(4,6));
    Black->getPawn(5)->setPos(Position(5,6));
    Black->getPawn(6)->setPos(Position(6,6));
    Black->getPawn(7)->setPos(Position(7,6));

    Black->getRook(0)->setIswhite(false);
    Black->getKnight(0)->setIswhite(false);
    Black->getBishop(0)->setIswhite(false);
    Black->getQueen()->setIswhite(false);
    Black->getKing()->setIswhite(false);
    Black->getBishop(1)->setIswhite(false);
    Black->getKnight(1)->setIswhite(false);
    Black->getRook(1)->setIswhite(false);

    Black->getPawn(0)->setIswhite(false);
    Black->getPawn(1)->setIswhite(false);
    Black->getPawn(2)->setIswhite(false);
    Black->getPawn(3)->setIswhite(false);
    Black->getPawn(4)->setIswhite(false);
    Black->getPawn(5)->setIswhite(false);
    Black->getPawn(6)->setIswhite(false);
    Black->getPawn(7)->setIswhite(false);
}



//ChessBoard::ChessBoard() {
//    cout << "Default ChessBoard constructor executed. " << endl;
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            Board[i][j] = nullptr;
//        }
//    }
//}


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




//void ChessBoard::printBoard() {
//    for (int i = 7; i>=0; i--) {
//        for (int j = 0; j<8; j++) {
//            if (Board[j][i] == nullptr) {
//                std::cout << 0 << " ";
//            }
//            else if (Board[j][i]->Piecetype() == PAWN) {std::cout << "P" << " ";}
//            else if (Board[j][i]->Piecetype() == KNIGHT) {std::cout << "N" << " ";}
//            else if (Board[j][i]->Piecetype() == BISHOP) {std::cout << "B" << " ";}
//            else if (Board[j][i]->Piecetype() == ROOK) {std::cout << "R" << " ";}
//            else if (Board[j][i]->Piecetype() == KING) {std::cout << "K" << " ";}
//            else if (Board[j][i]->Piecetype() == QUEEN) {std::cout << "Q" << " ";}
//            else {std::cout << "2" << " ";}
//        }
//        std::cout << std::endl;
//    }
//}

Piece* ChessBoard::getPiece(Position pos) {
    return Board[pos.getX()][pos.getY()];
}


void ChessBoard::setPiece(Piece* piece, Position pos, Player* current) {
    if (current->getIswhite()) {
//        cout << "current player is White->" << endl;
        if (piece == nullptr) {this->Board[pos.getX()][pos.getY()] = nullptr;}
        else if (piece->Piecetype() == KING) {
            this->Board[pos.getX()][pos.getY()] = this->White->getKing();
            this->White->getKing()->setPos(pos);
//            current->getKing()->setPos(pos);
        }
        else if (piece->Piecetype() == QUEEN) {
            this->Board[pos.getX()][pos.getY()] = this->White->getQueen();
            this->White->getQueen()->setPos(pos);
//            current->getQueen()->setPos(pos);
        }
        else if (piece->Piecetype() == ROOK) {
            this->Board[pos.getX()][pos.getY()] = this->White->getRook(piece->getPieceNo());
            this->White->getRook(piece->getPieceNo())->setPos(pos);
//            current->getRook(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == KNIGHT) {
            this->Board[pos.getX()][pos.getY()] = this->White->getKnight(piece->getPieceNo());
            this->White->getKnight(piece->getPieceNo())->setPos(pos);
//            current->getKnight(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == BISHOP) {
    //            if (whoseturn == true) {this->Board[pos.getX()][pos.getY()] = White->getBishop(piece->getPieceNo());}
    //            else {this->Board[pos.getX()][pos.getY()] = Black->getBishop(piece->getPieceNo());}
            this->Board[pos.getX()][pos.getY()] = this->White->getBishop(piece->getPieceNo());
            this->White->getBishop(piece->getPieceNo())->setPos(pos);
//            current->getBishop(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == PAWN) {
//            cout << "Set pawn number " << piece->getPieceNo() << "to position " << pos.getX() << " " << pos.getY() << endl;
            this->Board[pos.getX()][pos.getY()] = this->White->getPawn(piece->getPieceNo());
            this->White->getPawn(piece->getPieceNo())->setPos(pos);
//            current->getPawn(piece->getPieceNo())->setPos(pos);
        }
    }

    else if (!current->getIswhite()) {
        if (piece == nullptr) {this->Board[pos.getX()][pos.getY()] = nullptr;}
        else if (piece->Piecetype() == KING) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getKing();
            this->Black->getKing()->setPos(pos);
//            current->getKing()->setPos(pos);
        }
        else if (piece->Piecetype() == QUEEN) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getQueen();
            this->Black->getQueen()->setPos(pos);
//            current->getQueen()->setPos(pos);
        }
        else if (piece->Piecetype() == ROOK) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getRook(piece->getPieceNo());
            this->Black->getRook(piece->getPieceNo())->setPos(pos);
//            current->getRook(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == KNIGHT) {
            this->Board[pos.getX()][pos.getY()] = this->Black->getKnight(piece->getPieceNo());
            this->Black->getKnight(piece->getPieceNo())->setPos(pos);
//            current->getKnight(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == BISHOP) {
    //            if (whoseturn == true) {this->Board[pos.getX()][pos.getY()] = Black->getBishop(piece->getPieceNo());}
    //            else {this->Board[pos.getX()][pos.getY()] = Black->getBishop(piece->getPieceNo());}
            this->Board[pos.getX()][pos.getY()] = this->Black->getBishop(piece->getPieceNo());
            this->Black->getBishop(piece->getPieceNo())->setPos(pos);
//            current->getBishop(piece->getPieceNo())->setPos(pos);
        }
        else if (piece->Piecetype() == PAWN) {
            cout << "Set pawn number " << piece->getPieceNo() << "to position " << pos.getX() << " " << pos.getY() << endl;
            this->Board[pos.getX()][pos.getY()] = this->Black->getPawn(piece->getPieceNo());
            this->Black->getPawn(piece->getPieceNo())->setPos(pos);
//            current->getPawn(piece->getPieceNo())->setPos(pos);
        }
    }
}






























