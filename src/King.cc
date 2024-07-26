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
                int size = loc.size();
                vector<bool> bVec;
                vector<char> cVec;
                vector<pair<int,int>> pVec;
                for(auto it = loc.begin();  it!= loc.end(); ++it){
                    bVec.push_back(it->second->isBlack());
                    cVec.push_back(it->second->getName());
                    pVec.push_back(it->second->getCoord());
                }
                for(int k  = 0; k <size; ++k){
                    if((pVec.at(k) == getCoord())) continue;
                    if(bVec.at(k) == isBlack()) continue;
                    char name =  cVec.at(k);

                    auto nodeHandler = loc.extract({row,col});
                    nodeHandler.key() = {-1, -1};
                    loc.insert(std::move(nodeHandler));
                    if(name != 'k' && name != 'K') loc.find(pVec.at(k))->second->updateRange(loc);
                    
                    auto nodeHandler2 = loc.extract({-1,-1});
                    nodeHandler2.key() = {row, col};
                    loc.insert(std::move(nodeHandler2));

                    if(loc.find(pVec.at(k))->second->canMove({i,j})){
                        exist = true;
                        break;
                    }
                }
                if(!exist) range.push_back({i, j});
            }
        }
    }
}
