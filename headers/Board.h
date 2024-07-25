#ifndef BOARD_H
#define BOARD_H
#include "../headers/Piece.h"
#include "../headers/King.h"
#include "../headers/Pawn.h"
#include <utility>
#include <map>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

class Board{
    map<pair<int, int>, unique_ptr<Piece>> loc;
    pair<char, pair<pair<int, int>, pair<int, int>>> record;
    bool wCheck;
    bool bCheck;
    pair<pair<pair<int, int>, pair<int, int>>,pair<pair<int, int>, pair<int, int>>> enpssnt{{{0,0}, {0,0}},{{0,0}, {0,0}}};
    int enpssntTurn = -1; 
    int winner;
    int currTurn = 0;

    bool isCheckmate(King& k);
    bool isEnPssnt(const pair<int, int>& src, const pair<int, int>& dest);
    bool isCastling(const pair<int, int>& src, const pair<int, int>& dest);
    bool isStealmate();
    void updateBoard();
    public:
        unique_ptr<King> bKing;
        unique_ptr<King> wKing;
    public: 
        bool inCheck(King& k);
        int move(const pair<int, int>& src, const pair<int, int>& dest);
        void remove(const pair<int, int>& src);
        int add(const pair<int, int>& src, char p); // fail bit and success bit returned
        bool destInBoard(const pair<int, int>& src);
        vector<pair<pair<int, int>, pair<int, int>>> getLegalMoves(char color);
        map<pair<int, int>, unique_ptr<Piece>>::iterator end();
        map<pair<int, int>, unique_ptr<Piece>>::iterator pieceAt(int i, int j);
};

ostream &operator<<(ostream& out, Board& board);

#endif
