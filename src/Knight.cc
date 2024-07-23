#include "headers/Knight.h"

Knight::Knight(char c, int row, int col):Piece{c, row, col}{}

/*bool Knight::canMove(pair<int, int> destCd, map<pair<int,int>, Piece>& loc){
    pair<int, int > srcCd{row, col};
    if( srcCd == destCd) return false;
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
}*/
//TODO test for const pair &
bool Knight::canMove(pair<int, int> dest){
    for(auto pair : range){
        if(pair == dest) return true;
    }
    return false;
}

void Knight::updateRange(map<pair<int,int>, Piece>& loc){
    range.clear();
    for(auto pair : moveOption){
        auto it = loc.find({row+pair.first, col+pair.second});
        if(it == loc.end() || it->second.isBlack() != isBlack()) range.push_back({row+pair.first, col+pair.second});
    }
}