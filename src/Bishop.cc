#include "headers/Bishop.h"

Bishop::Bishop(char name, int r, int c):Piece{name, r, c}{}

/*bool Bishop::canMove(pair<int, int> dest, map<pair<int,int>, Piece>& loc) {
    if(srcCd == dest) return false;
    if (!(dest.first >= 1 && dest.first <= 8 && dest.second >= 1 && dest.second <= 8)) return false;
    bool pieceExist = loc.find(dest) != loc.end();
    bool diffColour = pieceExist ? loc.find(dest)->second.isBlack() != loc.find(srcCd)->second.isBlack() : false;

    int rowDiff = dest.first - srcCd.first;
    int colDiff = dest.second - srcCd.second;

    int absRow = (rowDiff < 0) ? -1*rowDiff : rowDiff;
    int absCol = (colDiff < 0) ? -1*colDiff : colDiff;

    if(absRow != absCol) return false;

    int incX = (rowDiff < 0) ? -1 : 1;
    int incY = (colDiff < 0) ? -1 : 1;

    for(int i = srcCd.first, j = srcCd.second; !(i == dest.first && j == dest.second); i+=incX, j+=incY){
        if(loc.find(pair<int, int>{i,j}) != loc.end()) return false;
    }
    if(!pieceExist || diffColour) return true;
    return false;
}*/

bool Bishop::canMove(pair<int, int> dest){
    
    int x_diff = dest.first - row;
    int y_diff = dest.second - col;

    int absRow = (x_diff < 0) ? -1*x_diff : x_diff;
    int absCol = (y_diff < 0) ? -1*y_diff : y_diff;

    if(absRow != absCol) return false;

    for(auto coord : range){
        int x = coord.first;
        int y = coord.second;
        if(row < dest.first && dest.first <= x && col < dest.second && dest.second <= y) return true;
        if(x <= dest.first && dest.first < row && y <= dest.second && dest.second < col) return true;
        if(row < dest.first && dest.first <= x && col < dest.second && dest.second <= y) return true;
        if(x <= dest.first && dest.first < row && y <= dest.second && dest.second < col) return true;
    }
    return false;
}

void Bishop::updateRange(map<pair<int,int>, Piece>& loc){
    range.clear();
    vector<int> dir{1, -1};
    for(int i : dir){
        for(int j : dir){
            updateDirec(i, j, loc);
        }
    }
}

void Bishop::updateDirec(int x_dir, int y_dir, map<pair<int,int>, Piece>& loc){
    for(int i = 1; i<8; i++){
        int x = row+i*x_dir;
        int y = col+i*y_dir;

        if (!(x >= 1 &&  x <= 8 && y >= 1 && y <= 8)){
            range.push_back(pair<int, int>{x-x_dir, y-y_dir});
            break;
        };

        auto it = loc.find(pair<int, int>{x, y});
        if(it == loc.end()) {
            range.push_back(pair<int, int>{x-x_dir, y-y_dir});
            break;
        }

        if(it->second.isBlack() != isBlack()){
            range.push_back(pair<int, int>{x, y});
            break;
        }
        break;
    }
}