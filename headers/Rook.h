#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook: public Piece{
    char name;
    bool moved = false;
    vector<pair<int, int>> range;
    void updateDirec(int x_dir, int y_dir, map<pair<int,int>, Piece>& loc);
    public:
        Rook(char c, int row, int col);
        bool canMove(pair<int, int> dest) override;
        void updateRange(map<pair<int,int>, Piece>& loc) override;
        void setMoved();
        bool getMoved();
};

#endif
