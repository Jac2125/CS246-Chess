#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece{
    //bool twoForward = true;
    //int turn = -1;
    //vector<pair<int, int>> range;
    public:
        Pawn(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc) override;
        /*int getEnPssntTurn();
        bool getTwoFwd();
        void setTwoFwd();
        void movedTwo(int currTurn);*/
};

#endif
