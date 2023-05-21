#include "player.h"


Player::Player(bool iswhite) {
    this->Iswhite       = iswhite;
    this->Rooks[0]      = new Rook(iswhite);
    this->Rooks[1]      = new Rook(iswhite);
    this->Bishops[0]    = new Bishop(iswhite);
    this->Bishops[1]    = new Bishop(iswhite);
    this->Knights[0]    = new Knight(iswhite);
    this->Knights[1]    = new Knight(iswhite);
    this->Pawns[0]      = new Pawn(iswhite);
    this->Pawns[1]      = new Pawn(iswhite);
    this->Pawns[2]      = new Pawn(iswhite);
    this->Pawns[3]      = new Pawn(iswhite);
    this->Pawns[4]      = new Pawn(iswhite);
    this->Pawns[5]      = new Pawn(iswhite);
    this->Pawns[6]      = new Pawn(iswhite);
    this->Pawns[7]      = new Pawn(iswhite);
}

Player::Player() {}

Player::~Player() {
    delete this->Rooks[0];
    delete this->Rooks[1];
    delete this->Bishops[0];
    delete this->Bishops[1];
    delete this->Knights[0];
    delete this->Knights[1];
    delete this->Pawns[0];
    delete this->Pawns[1];
    delete this->Pawns[2];
    delete this->Pawns[3];
    delete this->Pawns[4];
    delete this->Pawns[5];
    delete this->Pawns[6];
    delete this->Pawns[7];
}

bool Player::getIswhite() {
    return this->Iswhite;
}


void Player::setIswhite(bool iswhite) {
    this->Iswhite = iswhite;
}


King* Player::getKing() {return KinG;}

Queen* Player::getQueen() {return QueeN;}

// For these Pieces, we have two, so we have to pick a piece, each piece has a number assigned to it
Rook* Player::getRook(int i) {
     if(i>1) {std::cout << "There are only two rooks." << std::endl; return nullptr;}
    Rooks[i]->setPieceNo(i);
    return Rooks[i];
}
Bishop* Player::getBishop(int i) {
    if(i>1) {std::cout << "There are only two bishops." << std::endl; return nullptr;}
    Bishops[i]->setPieceNo(i);
    return Bishops[i];
}
Knight* Player::getKnight(int i) {
    if(i>1) {std::cout << "There are only two knights." << std::endl; return nullptr;}
    Knights[i]->setPieceNo(i);
    return Knights[i];
}


Pawn* Player::getPawn(int i) {
    if(i>7) {std::cout << "There are only eight pawns." << std::endl; return nullptr;}
    Pawns[i]->setPieceNo(i);
    return Pawns[i];
}


















































