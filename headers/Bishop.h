#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop: public Piece{
    char name;
    public:
        Bishop(char c);
        bool canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) override;
};

#endif
