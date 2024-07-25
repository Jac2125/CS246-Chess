#include "../headers/Queen.h"

Queen::Queen(char c, int row, int col):Piece{c, row, col}{}

bool Queen::canMove(pair<int, int> dest){
    int x_diff = dest.first - row;
    int y_diff = dest.second - col;

    int absRow = (x_diff < 0) ? -1*x_diff : x_diff;
    int absCol = (y_diff < 0) ? -1*y_diff : y_diff;

    if(!((absRow == absCol)||(dest.first == row || dest.second == col))) return false;

    for(auto coord : range){
        int x = coord.first;
        int y = coord.second;
        if(row < dest.first && dest.first <= x && col < dest.second && dest.second <= y) return true;
        if(x <= dest.first && dest.first < row && y <= dest.second && dest.second < col) return true;
        if(row < dest.first && dest.first <= x && col < dest.second && dest.second <= y) return true;
        if(x <= dest.first && dest.first < row && y <= dest.second && dest.second < col) return true;
    }

    for(auto coord : range){
        int x = coord.first;
        int y = coord.second;
        if(row < dest.first && dest.first <= x) return true;
        if(x < dest.first && dest.first < row) return true;
        if(col < dest.first && dest.first <= y) return true;
        if(y < dest.first && dest.first < col) return true;
    }
    
    return false;
}

void Queen::updateRange(map<pair<int, int>, unique_ptr<Piece>>& loc){
    range.clear();
    vector<int> dir{1, -1};
    for(int i : dir){
        for(int j : dir){
            updateDirec(i, j, loc);
        }
    }

    for(int i : dir){
        updateDirec(i, 0, loc);
    }

    for(int j : dir){
        updateDirec(0, j, loc);
    }
}

void Queen::updateDirec(int x_dir, int y_dir, map<pair<int, int>, unique_ptr<Piece>>& loc){
    for(int i = 1; i<8; i++){
        int x = row+i*x_dir;
        int y = col+i*y_dir;

        if (!(x >= 1 &&  x <= 8 && y >= 1 && y <= 8)){
            for(auto i : range){
                if (i == pair<int, int>{x-x_dir, y-y_dir}) break;
            } 
            range.push_back(pair<int, int>{x-x_dir, y-y_dir});
            return;
        };

        auto it = loc.find(pair<int, int>{x, y});
        /*if(it == loc.end()) {
            range.push_back(pair<int, int>{x-x_dir, y-y_dir});
            break;
        }*/
        if(it == loc.end()) continue;
        if(it->second->isBlack() != isBlack()){
            for(auto i : range){
                if (i == pair<int, int>{x, y}) break;
            }
            range.push_back(pair<int, int>{x, y});
            
        }else{
            for(auto i : range){
                if (i == pair<int, int>{x-x_dir, y-y_dir}) break;
            }
            range.push_back(pair<int, int>{x-x_dir, y-y_dir});
        }
    }
}
