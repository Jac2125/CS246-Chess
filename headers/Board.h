#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
#include "headers/King.h"
#include "headers/Pawn.h"
#include <utility>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

class Board{
    map<pair<int, int>, char> loc;
    pair<char, pair<pair<int, int>, pair<int, int>>> record;
    bool bKing;
    bool wKing;
    bool wCheck;
    bool bCheck;
    int winner;
    int currTurn = 0;

    bool inCheck(King& k);
    bool isCheckmate(King& k);
    bool isEnPssnt(Pawn& p, Pawn& opp, const pair<int, int>& dest);
    public: 
        int move(const pair<int, int>& src, const pair<int, int>& dest);
        void remove(const pair<int, int>& src);
        int add(const pair<int, int>& src, char p); // fail bit and success bit returned
        bool destInBoard(const pair<int, int>& src);
        auto end();
        auto pieceAt(int i, int j);
};

ostream &operator<<(ostream& out, Board board);

#endif