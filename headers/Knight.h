#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight: public Piece{
    char name;
    public:
        Knight(char c);
        bool canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) override;
};

#endif
