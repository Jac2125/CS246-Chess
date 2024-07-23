#ifndef PIECE_H
#define PIECE_H
#include <utility>
#include <map>
#include <vector>
using namespace std;

class Piece{
    protected:
        char name;
        int row;
        int col;
    public:
        Piece(char name, int r, int c);
        virtual bool canMove(pair<int, int> destCd) = 0;
        virtual void updateRange(map<pair<int,int>, Piece>& loc);
        bool isBlack();
        char getName();
        pair<int, int> getCoord();
        void setCoord(int r, int c);
        virtual ~Piece();
};

#endif
