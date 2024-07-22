#include "headers/Rook.h"

Rook::Rook(char c):name{c} {}

bool Rook::canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) {
    aaa
    if(srcCd == destCd) return false;
    if (!(destCd.first >= 1 && destCd.first <= 8 && destCd.second >= 1 && destCd.second <= 8)) return false;
    bool pieceExist = loc.find(destCd) != loc.end()? true : false;
    bool diffColour = pieceExist ? loc.find(destCd)->second.isBlack() != loc.find(srcCd)->second.isBlack() : false;

    if(srcCd.first == destCd.first){
        int x = srcCd.first;
        int inc = (destCd.second > srcCd.second) ? 1 : -1;
        for(int i = srcCd.second; i != destCd.second; i+=inc){
            if(loc.find(pair<int, int>{x, i}) != loc.end()) return false;
        }
        if(!pieceExist || diffColour) return true;
        return false;
    }

    if(srcCd.second == destCd.second){
        int y = srcCd.second;
        int inc = (destCd.first > srcCd.first) ? 1 : -1;
        for(int i = srcCd.first; i != destCd.first; i+=inc){
            if(loc.find(pair<int, int>{i, y}) != loc.end()) return false;
        }
        if(!pieceExist || diffColour) return true;
        return false;
    }

    return false;
}

Rook::SetMoved() {
    this->moved = true;
}

bool Rook::isMoved() {
    return this->moved;
}
