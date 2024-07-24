#ifndef KING_H
#define KING_H
#include "Piece.h"

class King: public Piece{
    
    public:
        King(char c, int row, int col);
        //bool kingCanMove();
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc) override;
};

#endif
