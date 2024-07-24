#include "headers/Board.h"
#include "headers/Queen.h"
#include "headers/Knight.h"
#include "headers/Rook.h"
#include "headers/Bishop.h"

ostream &operator<<(ostream& out, Board board){
    for(int i = 8; i>0; i--){
        out << i << " ";
        for(int j = 1; j<9; j++){
            auto it = board.pieceAt(i, j);
            if(it == board.end()){
                if(j%2 == 1) out << '_';
                else out << ' ';
                continue;
            }
            out << it->second.getName();
        }
        out << endl;
    }
    out << endl << endl;
    out << " abcdefgh";
    return out;
}

bool Board::inCheck(King& k){
    for(auto it : loc){
        if(it.first == k.getCoord()) continue;
        if(!it.second->canMove(it.first)) continue;
        if(it.second->isBlack() != k.isBlack()) return true;
    }
    return false;
}

bool Board::isCheckmate(King& k){
    bool kColour = k.isBlack();
    if(kColour) return (bCheck && !k.kingCanMove());
    else return (wCheck && !k.kingCanMove());
}

bool Board::isEnPssnt(Pawn& p, Pawn& opp, const pair<int, int>& dest){
    int dir = p.isBlack() ? -1 : 1;
    if(!(pair<int, int>{p.getCoord().first+dir, opp.getCoord().second} == dest)) return false;
    if(p.canMove(dest) && opp.getEnPssntTurn()+1 == currTurn) return false;
    return false;
}

int Board::move(const pair<int, int>& src, const pair<int, int>& dest){
    auto it = loc.find(src);
    if(it == loc.end()) return -1;
    char name = it->second->getName();
    if(name == 'p' || name == 'P')
        Pawn p = (it->second);

    }
    
}

void Board::remove(const pair<int, int>& src){
    auto it = loc.find(src);
    if(it == loc.end()) return;
    delete it->second;
    loc.erase(it->first);
}

int Board::add(const pair<int, int>& src, char p){
    if(p == 'K' || p =='k'){
        loc.at(src) = King(p, src.first, src.second);
        return 0;
    }

    if(p == 'Q' || p == 'q'){
        loc.at(src) = new Queen(p, src.first, src.second);
        return 0;
    }

    if(p == 'P' || p == 'p'){
        loc.at(src) = new Pawn(p, src.first, src.second);
        return 0;
    }

    if(p == 'N' || p == 'n'){
        loc.at(src) = new Knight(p, src.first, src.second);
        return 0;
    }

    if(p == 'B' || p == 'b'){
        loc.at(src) = new Bishop(p, src.first, src.second);
        return 0;
    }

    if(p == 'R' || p == 'r'){
        loc.at(src) = new Rook(p, src.first, src.second);
        return 0;
    }
    return 1
}

bool Board::destInBoard(const pair<int, int>& src){
    return (1<= src.first && src.first <= 8) && (1 < src.second && src.second <= 8);
}

auto Board::pieceAt(int i, int j){
    return loc.find({i, j});
}

auto Board::end(){
    return loc.end();
}