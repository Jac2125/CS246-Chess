#ifndef BOARD_H
#define BOARD_H
#include "../headers/Piece.h"
#include "../headers/King.h"
#include "../headers/Pawn.h"
#include "../headers/window.h"
#include <utility>
#include <map>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

class Board{
    Xwindow window{400, 400};
    map<pair<int, int>, unique_ptr<Piece>> loc;
    bool wCheck;
    bool bCheck;
    pair<pair<pair<int, int>, pair<int, int>>,pair<pair<int, int>, pair<int, int>>> enpssnt{{{0,0}, {0,0}},{{0,0}, {0,0}}};
    int enpssntTurn = -1; 
    int winner = -1;
    int currTurn = 0;
    pair<int, int> promotePawn;
    bool isEnPssnt(const pair<int, int>& src, const pair<int, int>& dest);
    bool isCastling(const pair<int, int>& src, const pair<int, int>& dest);
    bool isStealmate();
    bool canSave(King& s);
    bool canBlockDot(pair<int, int>src, vector<pair<int, int>> range);
    bool canBlockLine(pair<int, int>src, vector<pair<int, int>> range);
    void undoNoUpdate(const pair<int, int>& src, const pair<int, int>& dest, bool destMoved, char destName, bool srcMoved);
    bool safelyAssume(pair<int, int> p, King& k);
    void updateBoard();
    public: 
        void render();
        void lineToDots(vector<pair<int, int>>& line, pair<int, int>p, int row, int col);
        bool isCheckmate(King& k);
        void addNoUpdate(const pair<int, int>& src, char p);
        bool verifySetup();
        bool promotionAvailable();
        bool pawnOnLastRows();
        char whoseTurn();
        void promote(char c);
        void RevertCurrTurn();
        unique_ptr<King> bKing;
        unique_ptr<King> wKing;
        pair<char, pair<pair<int, int>, pair<int, int>>> record;
        pair<bool , bool> recordMoved;
        void init();
        void undo(const pair<int, int>& src, const pair<int, int>& dest, bool destMoved, char destName, bool srcMoved);
        bool inCheck(King& k);
        int move(const pair<int, int>& src, const pair<int, int>& dest);
        void remove(const pair<int, int>& src);
        int add(const pair<int, int>& src, char p); // fail bit and success bit returned
        bool destInBoard(const pair<int, int>& src);
        int getWinner();
        vector<pair<pair<int, int>, pair<int, int>>> getLegalMoves(char color);
        map<pair<int, int>, unique_ptr<Piece>>::iterator end();
        map<pair<int, int>, unique_ptr<Piece>>::iterator pieceAt(int i, int j);
};

ostream &operator<<(ostream& out, Board& board);

#endif
