#include "headers/Pawn.h"

Pawn::Pawn(char c, int row, int col):Piece{c, row, col}{}

bool Pawn::canMove(pair<int, int> dest) {
    for(auto pair : range){
        if(dest == pair) return true;
    }
    return false;
}

void Pawn::updateRange(map<pair<int,int>, Piece>& loc){
    range.clear();
    int dir = isBlack() ? -1 : 1;
    int nextRow = row + dir;
    for(int i = -1; i <= 1; i++){
        auto it = loc.find({nextRow, col+i});
        if(i != 0 && (it == loc.end() || it->second.isBlack() != isBlack())) range.push_back({nextRow, col+i});
        if(i == 0 && it != loc.end()) range.push_back({nextRow, col});
    }
    if((loc.find({nextRow, col}) != loc.end())&& (loc.find({nextRow+1, col}) != loc.end()) && twoForward){
        range.push_back({nextRow + 1, col});
    }
}

int Pawn::getEnPssntTurn(){ return turn;}

bool Pawn::getTwoFwd(){
    return twoForward;
}

void Pawn::setTwoFwd(){
    twoForward = false;
}

void Pawn::movedTwo(int currTurn){ 
    twoForward = false;
    turn = currTurn;
}
