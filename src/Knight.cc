#include "headers/Knight.h"

Knight::Knight(char c):name{c}{}

bool Knight::canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc){
    if(srcCd == destCd) return false;
    if (!(destCd.first >= 1 && destCd.first <= 8 && destCd.second >= 1 && destCd.second <= 8)) return false;
    int rowDiff = destCd.first - srcCd.first;
    int colDiff = destCd.second - srcCd.second;
    
    int absRowDiff = (rowDiff<0) ? -1*rowDiff : rowDiff;
    int absColDiff = (colDiff<0) ? -1*colDiff : colDiff;

    if((absRowDiff == 2 && absColDiff ==1) || (absRowDiff == 1 && absColDiff == 2)){
        if(loc.find(destCd) == loc.end()) return true;
        bool destIsBlack = loc.find(destCd)->second.isBlack();
        bool srcIsBlack = loc.find(srcCd)->second.isBlack();
        if(destIsBlack != srcIsBlack) return true;
    }
    
    return false;
}
