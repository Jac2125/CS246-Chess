#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece{
    char name;
    bool twoForward = false;
    int turn = -1;
    
    public:
        Pawn(char name);
        bool canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) override;
        void setEnPssnt(int currTurn);
        int getEnPssntTurn();
        void movedTwo();
};

#endif