#ifndef PIECE_H
#define PIECE_H
#include <utility>
#include <map>
using namespace std;

class Piece{
    char name;
    public:
        virtual bool canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) = 0;
        char getName();
        virtual ~Piece();
};

#endif