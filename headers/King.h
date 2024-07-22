#ifndef KING_H
#define KING_H
#include "Piece.h"

class King: public Piece{
    char name;
    bool moved = false;
    public:
        King(char c);
        bool canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) override;
        SetMoved();
        bool isMoved();
};

#endif
