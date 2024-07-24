#include "../headers/Board.h"
#include "../headers/Queen.h"
#include "../headers/Knight.h"
#include "../headers/Rook.h"
#include "../headers/Bishop.h"

ostream &operator<<(ostream& out, Board& board){
    for(int i = 8; i>0; i--){
        out << i << " ";
        for(int j = 1; j<9; j++){
            auto it = board.pieceAt(i, j);
            if(it == board.end()){
                if(j%2 == 1) out << '_';
                else out << ' ';
                continue;
            }
            out << it->second->getName();
        }
        out << endl;
    }
    out << endl << endl;
    out << " abcdefgh";
    return out;
}

bool Board::inCheck(King& k){
    for(auto it = loc.begin(); it != loc.end(); ++it){
        if(it->first == k.getCoord()) continue;
        if(!it->second->canMove(it->first)) continue;
        if(it->second->isBlack() != k.isBlack()){
            if(k.isBlack()) bCheck = true;
            else wCheck = true;
            return true;
        } 
    }
    return false;
}

bool Board::isStealmate(){
    for(auto it = loc.begin(); it != loc.end(); ++it){
        if(it->second->movableNum() > 0) return false;
    }
    return true;
}

bool Board::isCheckmate(King& k){
    bool kColour = k.isBlack();
    if(kColour) return (bCheck && !(k.movableNum()>0));
    else return (wCheck && !(k.movableNum()>0));
}

bool Board::isCastling(const pair<int, int>& src, const pair<int, int>& dest){
    if(!loc.find(src)->second->getMoved()) return false;
    if(!(src == pair<int, int>{1, 5} || src == pair<int, int>{8, 5})) return false;
    char c  = loc.find(src)->second->getName();
    if(c != 'p' || c != 'P') return false;
    
    bool kingIsBlack = loc.find(src)->second->isBlack();
    int rowNum;
    if(kingIsBlack) rowNum = 8;
    if(!kingIsBlack) rowNum = 1;

    if(!(dest == pair<int, int>{rowNum, 7} || dest == pair<int, int>{rowNum, 3})) return false;
    pair<int, int>rook{};
    if(dest == pair<int, int>{rowNum, 7}) rook = {rowNum,8};
    else if(dest == pair<int, int>{rowNum, 3}) rook = {rowNum,1};

    auto it = loc.find(rook);
    if(it != loc.end()) return false;
    if(kingIsBlack && it->second->getName() != 'r') return false;
    if(!kingIsBlack && it->second->getName() != 'R') return false;
    if(it->second->getMoved()) return false;

    pair<int, int> rookDest{};
    if(rook == pair<int,int>{rowNum,8}){
        if(!(loc.find({rowNum,7}) == loc.end() && loc.find({rowNum,6}) == loc.end())) return false;
        rookDest = {rowNum,6};
    }

    if(rook == pair<int,int>{rowNum,1}){
        if(!(loc.find({rowNum,2}) == loc.end() && 
            loc.find({rowNum,3}) == loc.end() && 
            loc.find({rowNum,4}) == loc.end())) return false;
        rookDest = {rowNum,4};
    }

    if(kingIsBlack){
        bKing->setCoord(dest.first, dest.second);
        if(inCheck(*bKing)){
            bKing->setCoord(src.first, src.second);
            return false;
        }
    }else{
        wKing->setCoord(dest.first, dest.second);
        if(inCheck(*wKing)){
            wKing->setCoord(src.first, src.second);
            return false;
        }
    }

    auto kingHandler = loc.extract(src);
    kingHandler.key() = dest;
    loc.find(dest)->second->setMoved();
    auto rookHandler = loc.extract(rook);
    rookHandler.key() = rookDest;
    loc.find(rookDest)->second->setMoved();
    
    updateBoard();
    return true;
}

bool Board::isEnPssnt(const pair<int, int>& src, const pair<int, int>& dest){
    if(enpssnt.first == pair<pair<int, int>, pair<int, int>>{src, dest} && currTurn == enpssntTurn + 1){
        remove(dest);
        auto kingHandler = loc.extract(src);
        kingHandler.key() = dest;
        loc.find(dest)->second->setMoved();
    }
    if(enpssnt.second == pair<pair<int, int>, pair<int, int>>{src, dest} && currTurn == enpssntTurn + 1){
        remove(dest);
        auto kingHandler = loc.extract(src);
        kingHandler.key() = dest;
        loc.find(dest)->second->setMoved();
    }
    updateBoard();
    return false;
}

int Board::move(const pair<int, int>& src, const pair<int, int>& dest){
    
    bool bTurn = currTurn % 2 == 0 ? true : false;
    
    auto it = loc.find(src);
    if(it == loc.end()) return -1;
    if(it->second->isBlack() != bTurn) return false;
    
    char n = it->second->getName();
    if(isEnPssnt(src, dest)) return 0;
    if(isCastling(src, dest)) return 0;
    if(!it->second->canMove(dest)) return -1;

    if(n == 'p' || n == 'P'){
        int rowDiff = src.first - dest.first;
        if(rowDiff == 2 || rowDiff == -2){
            int dir = (int)(rowDiff/2);
            auto next = loc.find({dest.first, dest.second-1});
            if(next != loc.end()){
                char c = next->second->getName();
                if((c == 'p' || c =='P') && it->second->isBlack() != next->second->isBlack()){
                    enpssntTurn = currTurn;
                    enpssnt.first = {{dest.first, dest.second-1}, {dest.first-dir, dest.second}};
                }
            }

            next = loc.find({dest.first, dest.second+1});
            if(next != loc.end()){
                char c = next->second->getName();
                if((c == 'p' || c =='P') && it->second->isBlack() != next->second->isBlack()){
                    enpssntTurn = currTurn;
                    enpssnt.first = {{dest.first, dest.second+1}, {dest.first-dir, dest.second}};
                }
            }
        }
    }

    
    it->second->setMoved();
    it->second->setCoord(dest.first, dest.second);
    if(bTurn && inCheck(*bKing)){
        bKing->setCoord(src.first, src.second);
        return -1;
    }

    if(!bTurn && inCheck(*wKing)){
        wKing->setCoord(src.first, src.second);
        return -1;
    }
    auto keyHandler = loc.extract(src);
    keyHandler.key() = dest;
    updateBoard();
    return 0;
}

void Board::remove(const pair<int, int>& src){
    auto it = loc.find(src);
    if(it == loc.end()) return;
    it->second.release();
    loc.erase(it->first);
}

int Board::add(const pair<int, int>& src, char p){
    if(p == 'K' && wKing == NULL){
        wKing = make_unique<King>(King(p, src.first, src.second));
        if(inCheck(*wKing)){
            wKing.release();
            wKing = NULL;
            return 1;
        }
        loc[src] = make_unique<King>(King(p, src.first, src.second));
        return 0;
    }

    if(p == 'k' && bKing == NULL){
        bKing = make_unique<King>(King(p, src.first, src.second));
        if(inCheck(*bKing)){
            bKing.release();
            bKing = NULL;
            return -1;
        }
        loc[src] = make_unique<King>(King(p, src.first, src.second));
        return 0;
    }

    if(p == 'Q' || p == 'q'){
        loc[src] = make_unique<Queen>(Queen(p, src.first, src.second));
        return 0;
    }

    if(p == 'P' || p == 'p'){
        loc[src] = make_unique<Pawn>(Pawn(p, src.first, src.second));
        return 0;
    }

    if(p == 'N' || p == 'n'){
        loc[src] = make_unique<Knight>(Knight(p, src.first, src.second));
        return 0;
    }

    if(p == 'B' || p == 'b'){
        loc[src] = make_unique<Bishop>(Bishop(p, src.first, src.second));
        return 0;
    }

    if(p == 'R' || p == 'r'){
        loc[src] = make_unique<Rook>(Rook(p, src.first, src.second));
        return 0;
    }
    return 1;
}

bool Board::destInBoard(const pair<int, int>& src){
    return (1<= src.first && src.first <= 8) && (1 < src.second && src.second <= 8);
}

map<pair<int, int>, unique_ptr<Piece>>::iterator Board::pieceAt(int i, int j){
    return loc.find({i, j});
}

map<pair<int, int>, unique_ptr<Piece>>::iterator Board::end(){
    return loc.end();
}

void Board::updateBoard(){
    for(auto it = loc.begin(); it != loc.end(); ++it){
        it->second->updateRange(loc);
    }
    if(inCheck(*bKing) && isCheckmate(*bKing)) winner = 1;
    if(inCheck(*wKing) && isCheckmate(*wKing)) winner = 2;
    if(isStealmate()) winner = 0;
}
