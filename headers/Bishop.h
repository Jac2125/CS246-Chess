#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop: public Piece{
    //vector<pair<int, int>> range;
    void updateDirec(int x_dir, int y_dir, map<pair<int, int>, unique_ptr<Piece>>& loc);
    public:
        Bishop(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc) override;
};

#endif
