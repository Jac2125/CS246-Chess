#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece{
    public:
        Pawn(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc) override;
};

#endif
