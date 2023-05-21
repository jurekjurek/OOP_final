#include "player.h"


Player::Player(bool iswhite) {
    this->Iswhite       = iswhite;
//    this->QueeN         = new Queen(iswhite);
//    this->KinG          = new King(iswhite);
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

    if (iswhite) {
//        this->KinG.setPos(Position(4,0));

//        this->QueeN.setPos(Position(3,0));

        this->Rooks[0].setPos(Position(0,0));
        this->Rooks[1].setPos(Position(7,0));

        this->Bishops[0].setPos(Position(2,0));
        this->Bishops[1].setPos(Position(5,0));

        this->Knights[0].setPos(Position(1,0));
        this->Knights[1].setPos(Position(6,0));

        this->Pawns[0].setPos(Position(0,1));
        this->Pawns[1].setPos(Position(1,1));
        this->Pawns[2].setPos(Position(2,1));
        this->Pawns[3].setPos(Position(3,1));
        this->Pawns[4].setPos(Position(4,1));
        this->Pawns[5].setPos(Position(5,1));
        this->Pawns[6].setPos(Position(6,1));
        this->Pawns[7].setPos(Position(7,1));
    }

    else if (!iswhite) {
//        this->KinG.setPos(Position(4,7));

//        this->QueeN.setPos(Position(3,7));

        this->Rooks[0].setPos(Position(0,7));
        this->Rooks[1].setPos(Position(7,7));

        this->Bishops[0].setPos(Position(2,7));
        this->Bishops[1].setPos(Position(5,7));

        this->Knights[0].setPos(Position(1,7));
        this->Knights[1].setPos(Position(6,7));

        this->Pawns[0].setPos(Position(0,6));
        this->Pawns[1].setPos(Position(1,6));
        this->Pawns[2].setPos(Position(2,6));
        this->Pawns[3].setPos(Position(3,6));
        this->Pawns[4].setPos(Position(4,6));
        this->Pawns[5].setPos(Position(5,6));
        this->Pawns[6].setPos(Position(6,6));
        this->Pawns[7].setPos(Position(7,6));
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


King* Player::getKing() {return &KinG;}

Queen* Player::getQueen() {return &QueeN;}

// For these Pieces, we have two, so we have to pick a piece, each piece has a number assigned to it
Rook* Player::getRook(int i) {
    if(i>1) {std::cout << "There are only two rooks." << std::endl; return nullptr;}
    Rooks[i].setPieceNo(i);
    return &Rooks[i];
}
Bishop* Player::getBishop(int i) {
    if(i>1) {std::cout << "There are only two bishops." << std::endl; return nullptr;}
    Bishops[i].setPieceNo(i);
    return &Bishops[i];
}
Knight* Player::getKnight(int i) {
    if(i>1) {std::cout << "There are only two knights." << std::endl; return nullptr;}
    Knights[i].setPieceNo(i);
    return &Knights[i];
}


Pawn* Player::getPawn(int i) {
    if(i>7) {std::cout << "There are only eight pawns." << std::endl; return nullptr;}
    Pawns[i].setPieceNo(i);
    return &Pawns[i];
}


















































