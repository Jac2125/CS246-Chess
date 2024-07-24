#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight: public Piece{
    //vector<pair<int, int>> range;
    public:
        Knight(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc) override;
};

#endif
