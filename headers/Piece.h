#ifndef PIECE_H
#define PIECE_H
#include <utility>
#include <map>
#include <vector>
#include <memory>
using namespace std;

class Piece{
    protected:
        vector<pair<int, int>> range;
        char name;
        int row;
        int col;
        bool moved = false;
    public:
        Piece(char name, int row, int col);
        virtual bool canMove(pair<int, int> dest){return false;}
        virtual void updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc){return;}
        int movableNum();
        bool isBlack();
        char getName();
        pair<int, int> getCoord();
        void setCoord(int r, int c);
        void setMoved();
        bool getMoved();
        virtual ~Piece();
};

#endif
