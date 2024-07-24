#include "headers/King.h"

King::King(char c, int row, int col):Piece{c, row, col} {}

bool King::canMove(pair<int, int> dest){
    for(auto coord : range){
        if(coord == dest) return true;
    }
    return false;
}

void King::updateRange(map<pair<int,int>, Piece>& loc){
    range.clear();
    int x_left = col == 2 ? col : col - 1;
    int x_right = col == 7 ? col : col + 1;
    int y_down = row == 2 ? row : row - 1;
    int y_up = row == 7 ? row : row + 1;
    for(int i = y_down; i <= y_up; i++){
        for(int j = x_left; j <=  x_right; j++){
            if(row == i && col == j) continue;
            auto it = loc.find({i,j});
            if(it == loc.end() || it->second.isBlack() != isBlack()){
                range.push_back({i,j});
            }
        }
    }
}

bool King::kingCanMove(){
    return !(range.size() == 0);
}

void King::setMoved() {
    this->moved = true;
}

bool King::getMoved() {
    return this->moved;
}
