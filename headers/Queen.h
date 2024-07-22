#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen: public Piece{
    char name;
    public:
        Queen(char c);
        bool canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) override;
};

#endif
