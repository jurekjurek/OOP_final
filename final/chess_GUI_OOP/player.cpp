#include "player.h"


Player::Player(bool iswhite) {
    this->Iswhite       = iswhite;
    KinG          = new King(iswhite);
    Queens[0]     = new Queen(iswhite);
    Queens[1]     = new Queen(iswhite);
    Queens[2]     = new Queen(iswhite);
    Rooks[0]      = new Rook(iswhite);
    Rooks[1]      = new Rook(iswhite);
    Rooks[2]      = new Rook(iswhite);
    Rooks[3]      = new Rook(iswhite);
    Bishops[0]    = new Bishop(iswhite);
    Bishops[1]    = new Bishop(iswhite);
    Bishops[2]    = new Bishop(iswhite);
    Bishops[3]    = new Bishop(iswhite);
    Knights[0]    = new Knight(iswhite);
    Knights[1]    = new Knight(iswhite);
    Knights[2]    = new Knight(iswhite);
    Knights[3]    = new Knight(iswhite);
    Pawns[0]      = new Pawn(iswhite);
    Pawns[1]      = new Pawn(iswhite);
    Pawns[2]      = new Pawn(iswhite);
    Pawns[3]      = new Pawn(iswhite);
    Pawns[4]      = new Pawn(iswhite);
    Pawns[5]      = new Pawn(iswhite);
    Pawns[6]      = new Pawn(iswhite);
    Pawns[7]      = new Pawn(iswhite);

    Queens[1]->setIsalive(false);
    Queens[2]->setIsalive(false);
    Queens[3]->setIsalive(false);
    Rooks[2]->setIsalive(false);
    Rooks[3]->setIsalive(false);
    Knights[2]->setIsalive(false);
    Knights[3]->setIsalive(false);
    Bishops[2]->setIsalive(false);
    Bishops[3]->setIsalive(false);



    if (iswhite) {
        this->KinG->setPos(Position(4,0));

        this->Queens[0]->setPos(Position(3,0));

        this->Rooks[0]->setPos(Position(0,0));
        this->Rooks[1]->setPos(Position(7,0));

        this->Bishops[0]->setPos(Position(2,0));
        this->Bishops[1]->setPos(Position(5,0));

        this->Knights[0]->setPos(Position(1,0));
        this->Knights[1]->setPos(Position(6,0));

        this->Pawns[0]->setPos(Position(0,1));
        this->Pawns[1]->setPos(Position(1,1));
        this->Pawns[2]->setPos(Position(2,1));
        this->Pawns[3]->setPos(Position(3,1));
        this->Pawns[4]->setPos(Position(4,1));
        this->Pawns[5]->setPos(Position(5,1));
        this->Pawns[6]->setPos(Position(6,1));
        this->Pawns[7]->setPos(Position(7,1));
    }

    else if (!iswhite) {
        this->KinG->setPos(Position(4,7));

        this->Queens[0]->setPos(Position(3,7));

        this->Rooks[0]->setPos(Position(0,7));
        this->Rooks[1]->setPos(Position(7,7));

        this->Bishops[0]->setPos(Position(2,7));
        this->Bishops[1]->setPos(Position(5,7));

        this->Knights[0]->setPos(Position(1,7));
        this->Knights[1]->setPos(Position(6,7));

        this->Pawns[0]->setPos(Position(0,6));
        this->Pawns[1]->setPos(Position(1,6));
        this->Pawns[2]->setPos(Position(2,6));
        this->Pawns[3]->setPos(Position(3,6));
        this->Pawns[4]->setPos(Position(4,6));
        this->Pawns[5]->setPos(Position(5,6));
        this->Pawns[6]->setPos(Position(6,6));
        this->Pawns[7]->setPos(Position(7,6));
    }


}

Player::Player() {}

Player::~Player() {
//    delete this->Rooks[0];
//    delete this->Rooks[1];
//    delete this->Bishops[0];
//    delete this->Bishops[1];
//    delete this->Knights[0];
//    delete this->Knights[1];
//    delete this->Pawns[0];
//    delete this->Pawns[1];
//    delete this->Pawns[2];
//    delete this->Pawns[3];
//    delete this->Pawns[4];
//    delete this->Pawns[5];
//    delete this->Pawns[6];
//    delete this->Pawns[7];
}

bool Player::getIswhite() {
    return this->Iswhite;
}


void Player::setIswhite(bool iswhite) {
    this->Iswhite = iswhite;
}


King* Player::getKing() {return KinG;}

Queen* Player::getQueen(int i) {
    Queens[i]->setPieceNo(i);
    return Queens[i];
}

// For these Pieces, we have two, so we have to pick a piece, each piece has a number assigned to it
Rook* Player::getRook(int i) {
//    if(i>1) {std::cout << "There are only two rooks." << std::endl; return nullptr;}
    Rooks[i]->setPieceNo(i);
    return Rooks[i];
}
Bishop* Player::getBishop(int i) {
//    if(i>1) {std::cout << "There are only two bishops." << std::endl; return nullptr;}
    Bishops[i]->setPieceNo(i);
    return Bishops[i];
}
Knight* Player::getKnight(int i) {
//    if(i>1) {std::cout << "There are only two knights." << std::endl; return nullptr;}
    Knights[i]->setPieceNo(i);
    return Knights[i];
}


Pawn* Player::getPawn(int i) {
//    if(i>7) {std::cout << "There are only eight pawns." << std::endl; return nullptr;}
    Pawns[i]->setPieceNo(i);
    return Pawns[i];
}


vector<Piece*> Player::getAlivePieces() {
    // keep a vector of all alive pieces of a certain player
    // keep in mind that we have four pieces of every kind, two for the case of promotion
    vector<Piece*> AlivePieces;
    if (this->Queens[0]->getIsalive()) {
        AlivePieces.push_back(this->Queens[0]);
    }
    if (this->Queens[1]->getIsalive()) {
        AlivePieces.push_back(this->Queens[1]);
    }
    if (this->Queens[2]->getIsalive()) {
        AlivePieces.push_back(this->Queens[2]);
    }
    if (this->KinG->getIsalive()) {
        AlivePieces.push_back(this->KinG);
    }
    if (this->Rooks[0]->getIsalive()) {
        AlivePieces.push_back(this->Rooks[0]);
    }
    if (this->Rooks[1]->getIsalive()) {
        AlivePieces.push_back(this->Rooks[1]);
    }
    if (this->Rooks[2]->getIsalive()) {
        AlivePieces.push_back(this->Rooks[2]);
    }
    if (this->Rooks[3]->getIsalive()) {
        AlivePieces.push_back(this->Rooks[3]);
    }
    if (this->Bishops[0]->getIsalive()) {
        AlivePieces.push_back(this->Bishops[0]);
    }
    if (this->Bishops[1]->getIsalive()) {
        AlivePieces.push_back(this->Bishops[1]);
    }
    if (this->Bishops[2]->getIsalive()) {
        AlivePieces.push_back(this->Bishops[2]);
    }
    if (this->Bishops[3]->getIsalive()) {
        AlivePieces.push_back(this->Bishops[3]);
    }
    if (this->Knights[0]->getIsalive()) {
        AlivePieces.push_back(this->Knights[0]);
    }
    if (this->Knights[1]->getIsalive()) {
        AlivePieces.push_back(this->Knights[1]);
    }
    if (this->Knights[2]->getIsalive()) {
        AlivePieces.push_back(this->Knights[2]);
    }
    if (this->Knights[3]->getIsalive()) {
        AlivePieces.push_back(this->Knights[3]);
    }
    if (this->Pawns[0]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[0]);
    }
    if (this->Pawns[1]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[1]);
    }
    if (this->Pawns[2]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[2]);
    }
    if (this->Pawns[3]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[3]);
    }
    if (this->Pawns[4]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[4]);
    }
    if (this->Pawns[5]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[5]);
    }
    if (this->Pawns[6]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[6]);
    }
    if (this->Pawns[7]->getIsalive()) {
        AlivePieces.push_back(this->Pawns[7]);
    }
    return AlivePieces;
}















































