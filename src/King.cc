#include "headers/King.h"

King::King(char c):name{c} {}

bool King::canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) {
    if(srcCd == destCd) return false;
    if (!(destCd.first >= 1 && destCd.first <= 8 && destCd.second >= 1 && destCd.second <= 8)) return false;
    int rowDiff = destCd.first - srcCd.first;
    int colDiff = destCd.second - srcCd.second;
    
    int absRowDiff = (rowDiff<0) ? -1*rowDiff : rowDiff;
    int absColDiff = (colDiff<0) ? -1*colDiff : colDiff;

    if (absRowDiff <= 1 && absColDiff <= 1) {
        if(loc.find(destCd) == loc.end()) {
            this->moved = true;
            return true;
        }
        bool destIsBlack = loc.find(destCd)->second.isBlack();
        bool srcIsBlack = loc.find(srcCd)->second.isBlack();
        if(destIsBlack != srcIsBlack) {
            this->moved = true;
            return true;
        }
    }
    return false;
}

King::SetMoved() {
    this->moved = true;
}

bool King::isMoved() {
    return this->moved;
}
