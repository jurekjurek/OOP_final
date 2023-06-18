#include "piece.h"



// constructor
Piece::Piece(bool iswhite) {
    this->Iswhite = iswhite;
    this->Isalive = true;
    this->enPassant = false;
}

Piece::Piece() {
    this->Iswhite = true;
    this->Isalive = true;
    this->enPassant = false;
}

// Firstmove
void Piece::setFirstmove(bool firstmove) {
    this->Firstmove = firstmove;
}

bool Piece::getFirstmove() {
    return this->Firstmove;
}

// Position
void Piece::setPos(Position pos) {
    this->Pos = pos;
}

Position Piece::getPos() {
    return this->Pos;
}

// Color
void Piece::setIswhite(bool iswhite) {
    this->Iswhite = iswhite;
}

bool Piece::getIswhite() {
    return this->Iswhite;
}

// Is alive
void Piece::setIsalive(bool isalive) {
    this->Isalive = isalive;
}

bool Piece::getIsalive() {
    return this->Isalive;
}








// will be overwritten for the other pieces
bool Piece::move_valid(Position final) {
    return true;
}


PieceType Piece::Piecetype() {
    return NONE;
}

void Piece::setPieceNo(int) {
}

int Piece::getPieceNo() {
    return 0;
}

bool Piece::getPromotion() {
    return false;
}

bool Piece::getEnPassant() {
    return this->enPassant;
}

void Piece::setEnPassant(bool ep) {
    this->enPassant = ep;
}



// now, for the children

// King:


King::King(bool iswhite) : Piece(iswhite) {}

King::King() {Piece();}

bool King::move_valid(Position final){
    if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

    // consider here all the moves that a king can make in a chess game
    // for example, a king can also move 2 to the left or right in case of castles
    int tx[] = {1, 1, -1, -1, 1, -1, 0, 0, -2, 2};
    int ty[] = {-1, 1, -1, 1, 0, 0, 1, -1, 0, 0};
    bool valid_move = false;

    for (int i =0; i<10; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        if (x+tx[i] == final.getX() and y+ty[i] == final.getY()) {valid_move = true;}

    }
    return valid_move;
}

PieceType King::Piecetype()  {
    return KING;
}


// Queen

Queen::Queen(bool iswhite) : Piece(iswhite) {}

Queen::Queen() {Piece();}

bool Queen::move_valid(Position final)  {
    if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

    int tx[] = {1, 1, -1, -1, 1, -1, 0, 0};
    int ty[] = {-1, 1, -1, 1, 0, 0, 1, -1};
    bool valid_move = false;

    for (int i =0; i<8; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        for (int j = 0; j<8; j++) {
            if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {valid_move = true;}
        }

    }
    return valid_move;
}


PieceType Queen::Piecetype()  {
    return QUEEN;
}

void Queen::setPieceNo(int i)  {
    this->PieceNo = i;
}


int Queen::getPieceNo()  {
    return this->PieceNo;
}


// Rook

Rook::Rook(bool iswhite) : Piece(iswhite) {}

Rook::Rook() {Piece();}

bool Rook::move_valid(Position final)  {
    if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

    int tx[] = {1, -1, 0, 0};
    int ty[] = {0, 0, 1, -1};
    bool valid_move = false;

    for (int i =0; i<4; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        for (int j = 0; j<8; j++) {
            if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {valid_move = true;}
        }
    }
    return valid_move;
}


PieceType Rook::Piecetype()  {
    return ROOK;
}


void Rook::setPieceNo(int i)  {
    this->PieceNo = i;
}


int Rook::getPieceNo()  {
    return this->PieceNo;
}



// Knight

Knight::Knight(bool iswhite) : Piece(iswhite) {}

Knight::Knight() {Piece();}


bool Knight::move_valid(Position final)  {
    if (!final.check_pos()) {return false;}

    int tx[] = { 2, 2,-2,-2, 1, 1,-1,-1};
    int ty[] = {-1, 1,-1, 1,-2, 2,-2, 2};
    bool valid_move = false;

    for (int i =0; i<8; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        if (x+tx[i] == final.getX() and y+ty[i] == final.getY()) {valid_move = true;}

    }
    return valid_move;
}

PieceType Knight::Piecetype()  {
    return KNIGHT;
}

void Knight::setPieceNo(int i)  {
    this->PieceNo = i;
}

int Knight::getPieceNo()  {
    return this->PieceNo;
}




// Bishop

Bishop::Bishop(bool iswhite) : Piece(iswhite) {}

Bishop::Bishop() {Piece();}


bool Bishop::move_valid(Position final)  {
    if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

    int tx[] = {1, 1, -1, -1};
    int ty[] = {-1, 1, -1, 1};
    bool valid_move = false;

    for (int i =0; i<8; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        for (int j = 0; j<8; j++) {
            if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {valid_move = true;}
        }

    }
    return valid_move;
}

PieceType Bishop::Piecetype()  {
    return BISHOP;
}

// pieceno can actually be bigger than 1, because of promotion
void Bishop::setPieceNo(int i)  {
    this->PieceNo = i;
}

int Bishop::getPieceNo()  {
    return this->PieceNo;
}



// Pawn


Pawn::Pawn(bool iswhite) : Piece(iswhite) {
    this->Iswhite = iswhite;
}

Pawn::Pawn() {Piece();}



bool Pawn::move_valid(Position final)  {
    if (!final.check_pos()) {return false;}
    bool valid_move = false;

    // determine position that pawn moves from. The pawn moves from its current position which is an attribute of the class
    int x = this->getPos().getX();
    int y = this->getPos().getY();

    // differentiate between two cases:
    // Pawn is white, can only move up the board.
    if (this->getIswhite()) {

        // for its first move, it can take two steps
        if (this->getFirstmove() and x == final.getX() and y+2 == final.getY()) {valid_move = true;}

        // it can always move one up the board
        else if (x == final.getX() and y+1 == final.getY()) {valid_move = true;}

        // and it can hit diagonally, either to the right
        else if (x+1 == final.getX() and y+1 == final.getY()) {valid_move = true;}

        // or to the left
        else if (x-1 == final.getX() and y+1 == final.getY()) {valid_move = true;}

        // if the pawn is white and we hit the uppermost row of the chessboard, the pawn can be promoted
        if (valid_move == true and final.getY() == 7) {this->promotion = true;}
    }

    // Pawn is black, can only move down the board
    if (!this->getIswhite()) {
        // the cases are all the same as for white
        if (this->getFirstmove() and x == final.getX() and y-2 == final.getY()) {valid_move = true;}
        else if (x == final.getX() and y-1 == final.getY()) {valid_move = true;}
        else if (x+1 == final.getX() and y-1 == final.getY()) {valid_move = true;}
        else if (x-1 == final.getX() and y-1 == final.getY()) {valid_move = true;}
        if (valid_move == true and y == 0) {cout << "Your pawn can be promoted!" << endl; this->promotion = true;}
    }

    return valid_move;
}


PieceType Pawn::Piecetype()  {
    return PAWN;
}

void Pawn::setPieceNo(int i)  {
    if (i>7) {
        cout << "You are trying to set a non-valid piecenumber. Not doing that" << endl;
        return;
    }
    this->PieceNo = i;
}

int Pawn::getPieceNo()  {
    return this->PieceNo;
}

bool Pawn::getPromotion() {
    return this->promotion;
}




