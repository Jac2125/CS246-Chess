#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook: public Piece{
    void updateDirec(int x_dir, int y_dir, map<pair<int, int>, unique_ptr<Piece>>& loc);
    public:
        Rook(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc) override;
};

#endif
