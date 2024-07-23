#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen: public Piece{
    vector<pair<int, int>> range;
    void updateDirec(int x_dir, int y_dir, map<pair<int,int>, Piece>& loc);
    public:
        Queen(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int,int>, Piece>& loc) override;
};

#endif
