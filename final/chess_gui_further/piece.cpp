#include "piece.h"



// first, the piece class


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

void Piece::setFirstmove(bool firstmove) {
    this->Firstmove = firstmove;
}

bool Piece::getFirstmove() {
    return this->Firstmove;
}

void Piece::setPos(Position pos) {
    this->Pos = pos;
}

void Piece::setIswhite(bool iswhite) {
    this->Iswhite = iswhite;
}


void Piece::setIsalive(bool isalive) {
    this->Isalive = isalive;
}


Position Piece::getPos() {return this->Pos;}

bool Piece::getIswhite() {return this->Iswhite;}


bool Piece::getIsalive() {return this->Isalive;}


bool Piece::move_valid(Position final) {
    return true;
}


PieceType Piece::Piecetype() {
    return NONE;
}

void Piece::setPieceNo(int) {}

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

    // -2 and +2 in case of castles
    int tx[] = {1, 1, -1, -1, 1, -1, 0, 0, -2, 2};
    int ty[] = {-1, 1, -1, 1, 0, 0, 1, -1, 0, 0};
    bool result = false;

    for (int i =0; i<10; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        if (x+tx[i] == final.getX() and y+ty[i] == final.getY()) {result = true;}

    }
    return result;
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
    bool result = false;

    for (int i =0; i<8; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        for (int j = 0; j<8; j++) {
            if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {result = true;}
        }

    }
    return result;
}


PieceType Queen::Piecetype()  {
    return QUEEN;
}


// Rook

Rook::Rook(bool iswhite) : Piece(iswhite) {}

Rook::Rook() {Piece();}

bool Rook::move_valid(Position final)  {
    if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}

    int tx[] = {1, -1, 0, 0};
    int ty[] = {0, 0, 1, -1};
    bool result = false;

    for (int i =0; i<4; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        for (int j = 0; j<8; j++) {
            if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {result = true;}
        }
    }
    return result;
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
    bool result = false;

    for (int i =0; i<8; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        if (x+tx[i] == final.getX() and y+ty[i] == final.getY()) {result = true;}

    }
    return result;
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
    bool result = false;

    for (int i =0; i<8; i++) {
        int x = this->getPos().getX();
        int y = this->getPos().getY();
        for (int j = 0; j<8; j++) {
            if (x+j*tx[i] == final.getX() and y+j*ty[i] == final.getY()) {result = true;}
        }

    }
    return result;
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


Pawn::Pawn(bool iswhite) : Piece(iswhite) {}

Pawn::Pawn() {Piece();}



bool Pawn::move_valid(Position final)  {
//    cout << "MOVE VALID FUNCTION EXECUTED" << endl;
//    cout << final.getX() << " " << final.getY() << endl;
    if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}
    bool result = false;


    int x = this->getPos().getX();
    int y = this->getPos().getY();
//    cout << "this position: " << x << " " << y << endl;

    if (this->getIswhite()) {
//        cout << "Apparently, your piece is white. " << endl;
        if (this->getFirstmove() and x == final.getX() and y+2 == final.getY()) {result = true;}
        else if (x == final.getX() and y+1 == final.getY()) {result = true;}
        else if (x+1 == final.getX() and y+1 == final.getY()) {result = true;}
        else if (x-1 == final.getX() and y+1 == final.getY()) {result = true;}
        if (result == true and y == 7) {cout << "Your pawn can be promoted!" << endl; this->promotion = true;}
    }
    if (!this->getIswhite()) {
//        cout << "Apparently, your piece is black. " << endl;
        if (this->getFirstmove() and x == final.getX() and y-2 == final.getY()) {result = true;}
        else if (x == final.getX() and y-1 == final.getY()) {result = true;}
        else if (x+1 == final.getX() and y-1 == final.getY()) {result = true;}
        else if (x-1 == final.getX() and y-1 == final.getY()) {result = true;}
        if (result == true and y == 0) {cout << "Your pawn can be promoted!" << endl; this->promotion = true;}
    }

    return result;
}



bool Pawn::capture_valid(Position final) {
    if (!final.check_pos()) {std::cout << "final position invalid" << std::endl; return false;}
    if (!this->Capturepossible) {std::cout << "invalid move, pawn not in position to capture" << std::endl; return false;}
    bool result = false;

    int x = this->getPos().getX();
    int y = this->getPos().getY();

    if (x+1 == final.getX() and y+1 == final.getY()) {result = true;}
    else if (x-1 == final.getX() and y+1 == final.getY()) {result = true;}

    return result;
}

PieceType Pawn::Piecetype()  {
    return PAWN;
}

void Pawn::setPieceNo(int i)  {
    if (i>7) {
        cout << "You are trying to set a non-valid piecenumber. Not doing that" << endl;
    }
    this->PieceNo = i;
}

int Pawn::getPieceNo()  {
    return this->PieceNo;
}

bool Pawn::getPromotion() {
    return this->promotion;
}




