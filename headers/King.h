#ifndef KING_H
#define KING_H
#include "Piece.h"

class King: public Piece{
    bool moved = false;
    vector<pair<int, int>> range;
    public:
        King(char c, int row, int col);
        bool kingCanMove();
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int,int>, Piece>& loc) override;
        void setMoved();
        bool getMoved();
};

#endif
