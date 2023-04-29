#include "player.h"


Player::Player(bool iswhite) {
    this->Iswhite       = iswhite;
    this->KinG          = new King(iswhite);
    this->QueeN         = new Queen(iswhite);
    this->Rooks[0]      = new Rook(iswhite);
    this->Rooks[1]      = new Rook(iswhite);
    this->Rooks[2]      = new Rook(iswhite);
    this->Bishops[0]    = new Bishop(iswhite);
    this->Bishops[1]    = new Bishop(iswhite);
    this->Bishops[2]    = new Bishop(iswhite);
    this->Knights[0]    = new Knight(iswhite);
    this->Knights[1]    = new Knight(iswhite);
    this->Knights[2]    = new Knight(iswhite);
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
    Rooks[i].setPieceNo(i);
    return &Rooks[i];
}
Bishop* Player::getBishop(int i) {
    Bishops[i].setPieceNo(i);
    return &Bishops[i];
}
Knight* Player::getKnight(int i) {
    Knights[i].setPieceNo(i);
    return &Knights[i];
}


Pawn* Player::getPawn(int i) {
    if(i>7) {std::cout << "There are only eight pawns." << std::endl; return nullptr;}
    Pawns[i].setPieceNo(i);
    return &Pawns[i];
}


Move Player::getMove() {
    int x1, y1, x2, y2;
    std::cout << "Enter four numbers, the first two corresponding to x1, y1, the second two to x2, y2" << std::endl << std::flush;
    std::cin >> x1 >> y1 >> x2 >> y2;
    Position pos1(x1, y1);
    Position pos2(x2, y2);
    Move move(pos1, pos2);
    return move;
}


void Player::showOutput(GameState status) {
    switch (status) {
        case ACTIVE:
            std::cout << "State: Game active" << std::endl;
            break;
        case ERROR:
            std::cout << "State: ERROR" << std::endl;
            break;
        case CHECK:
            std::cout << "State: You're in check!" << std::endl;
            break;
        case DRAW:
            std::cout << "State: Game is drawn" << std::endl;
            break;
        case WHITEWINS:
            std::cout << "State: White wins" << std::endl;
            break;
        case BLACKWINS:
            std::cout << "State: Black wins" << std::endl;
            break;
    }
}

















































