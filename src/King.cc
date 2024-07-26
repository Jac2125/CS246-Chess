#include "../headers/King.h"

King::King(char c, int row, int col):Piece{c, row, col} {}

bool King::canMove(pair<int, int> dest){
    
    for(auto coord : range){
        if(coord == dest) return true;
    }
    return false;
}



void King::updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc){
    range.clear();
    int x_left = col == 1 ? col : col - 1;
    int x_right = col == 8 ? col : col + 1;
    int y_down = row == 1 ? row : row - 1;
    int y_up = row == 8 ? row : row + 1;
    for(int i = y_down; i <= y_up; ++i){
        for(int j = x_left; j <=  x_right; ++j){
            if(row == i && col == j) continue;

            auto it = loc.find({i,j});

            if(it == loc.end() || it->second->isBlack() != isBlack()){
                bool exist = false;
                for(auto it2 = loc.begin(); it2 != loc.end(); ++it2){
                    if((it2->second->getCoord() == getCoord())) continue;
                    if(it2->second->isBlack() == isBlack()) continue;
                    if(it2->second->canMove({i,j})){
                        exist = true;
                        break;
                    }
                }
                if(!exist) range.push_back({i, j});
            }
        }
    }
}