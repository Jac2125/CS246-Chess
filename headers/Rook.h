#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook: public Piece{
    char name;
    bool moved = false;
    public:
        Rook(char c);
        bool canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) override;
        SetMoved();
        bool isMoved();
};

#endif
