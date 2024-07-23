#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight: public Piece{
    vector<pair<int, int>> range;
    vector<pair<int, int>> moveOption{{1,2}, {-1, 2}, {1, -2}, {-1, -2},
                                        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    public:
        Knight(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int,int>, Piece>& loc) override;
};

#endif
