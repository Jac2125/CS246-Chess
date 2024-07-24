#include "headers/Knight.h"

Knight::Knight(char c, int row, int col):Piece{c, row, col}{}

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