#include "../headers/Board.h"
#include "../headers/Queen.h"
#include "../headers/Knight.h"
#include "../headers/Rook.h"
#include "../headers/Bishop.h"
#include "../headers/Computer.h"

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

void Board::init(){
    add({8,1},'r');
    add({8,8},'r');
    add({8,2},'n');
    add({8,7},'n');
    add({8,3},'b');
    add({8,6},'b');
    add({8,4},'q');
    add({8,5},'k');
    
    add({1,1},'R');
    add({1,8},'R');
    add({1,2},'N');
    add({1,7},'N');
    add({1,3},'B');
    add({1,6},'B');
    add({1,4},'Q');
    add({1,5},'K');
    for(int i = 1; i <= 8; i++){
        add({2,i},'P');
        add({7,i},'p');
    }
    winner = -1;
}

bool Board::inCheck(King& k){
    for(auto it = loc.begin(); it != loc.end(); ++it){
        if(it->first == k.getCoord()) continue;
        it->second->updateRange(loc);
        if(!it->second->canMove(k.getCoord())) continue;
        if(it->second->isBlack() != k.isBlack()){
            if(k.isBlack()) bCheck = true;
            else wCheck = true;
            return true;
        } 
    }
    wCheck = false;
    bCheck = false;
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
    k.updateRange(loc);
    if(kColour && (bCheck && (k.movableNum()==0 && !canSave(k)))) return true;
    else if(!kColour && wCheck && (k.movableNum()==0 && !canSave(k))) return true;
    return false;
}

bool Board::safelyAssume(pair<int, int> p, King& k){
    bool result = true;
    auto nodeHandler = loc.extract(p);
    nodeHandler.key() = {-1, -1};
    loc.insert(std::move(nodeHandler));
    
    int size = loc.size();
    vector<bool> bVec;
    vector<char> cVec;
    vector<pair<int,int>> pVec;

    for(auto it = loc.begin(); it!= loc.end(); ++it){
        bVec.push_back(it->second->isBlack());
        cVec.push_back(it->second->getName());
        pVec.push_back(it->second->getCoord());
    }
    for(int i = 0; i < size; ++i){
        if(pVec.at(i) == pair<int,int>{-1, -1}) continue;
        auto it2 = loc.find(pVec.at(i));
        it2->second->updateRange(loc);
        if(it2->second->canMove(k.getCoord())) {
            result = false;
            break;
        }
    }
    auto nodeHandler2 = loc.extract({-1,-1});
    nodeHandler2.key() = p;
    loc.insert(std::move(nodeHandler2));
    return result;
}

bool Board::canSave(King& k){
    bool kColour = k.isBlack();
    int attack = 0;
    for(auto it = loc.begin(); it != loc.end(); ++it){
        if(it->second->isBlack() != kColour && it->second->canMove(k.getCoord())) attack++;
    }
    if(attack > 1) return false;
    
    int size = loc.size();
    
    vector<bool> bVec;
    vector<char> cVec;
    vector<pair<int,int>> pVec;
    vector<vector<pair<int, int>>> vp;
    
    for(auto it = loc.begin();  it!= loc.end(); ++it){
        bVec.push_back(it->second->isBlack());
        cVec.push_back(it->second->getName());
        pVec.push_back(it->second->getCoord());
        vp.push_back(it->second->getRange());
    }
    for(int j = 0; j < size; ++j){
        if(bVec.at(j) != kColour) continue;
        char name = tolower(cVec.at(j));
        if(name == 'k') continue;
        if((name == 'p' || name == 'n') && canBlockDot(pVec.at(j), vp.at(j))){
            return true;
        }
        else if(canBlockLine(pVec.at(j), vp.at(j))){
            
            return safelyAssume(pVec.at(j), k);
        }
    }
    return false;
}

void Board::addNoUpdate(const pair<int, int>& src, char p){

    if(p == 'Q' || p == 'q'){
        loc[src] = make_unique<Queen>(Queen(p, src.first, src.second));
    }

    if(p == 'P' || p == 'p'){
        loc[src] = make_unique<Pawn>(Pawn(p, src.first, src.second));
    }

    if(p == 'N' || p == 'n'){
        loc[src] = make_unique<Knight>(Knight(p, src.first, src.second));
    }

    if(p == 'B' || p == 'b'){
        loc[src] = make_unique<Bishop>(Bishop(p, src.first, src.second));
    }

    if(p == 'R' || p == 'r'){
        loc[src] = make_unique<Rook>(Rook(p, src.first, src.second));
    }
    
    for(auto it = loc.begin(); it != loc.end(); ++it){
        it->second->updateRange(loc);
    }

}

void Board::undoNoUpdate(const pair<int, int>& src, const pair<int, int>& dest, bool destMoved, char destName, bool srcMoved){
        char srcName = loc.find(dest)->second->getName();
        remove(dest);
        addNoUpdate(src, srcName);
        
        if(srcMoved){
            loc.find(src)->second->setMoved();
            if(srcName == 'k') bKing->setMoved();
            if(srcName == 'K') wKing->setMoved();
        } 
        if(destName != '\0') {
            addNoUpdate(dest, destName);
            if(destMoved) loc.find(dest)->second->setMoved();
        }
        
}

bool Board::canBlockDot(pair<int, int>src, vector<pair<int, int>> range){
    bool moved = loc.find(src)->second->getMoved();
    char name = loc.find(src)->second->getName();
    for(pair<int,int> p : range){
        auto it = loc.find(p);
        bool exist = it != loc.end();
        bool destMoved = exist ? it->second->getMoved() : false;
        bool bTurn = currTurn%2 == 0;
        char destName = exist ? it->second->getName() : '\0';
        remove(src);
        addNoUpdate(p, name);
        if(bTurn && bKing != NULL && inCheck(*bKing)){
            undoNoUpdate(src, p, destMoved, destName, moved);
            continue;
        } else if(!bTurn && wKing != NULL && inCheck(*wKing)){
            undoNoUpdate(src, p, destMoved, destName, moved);
            continue;
        }else{
            undoNoUpdate(src, p, destMoved, destName, moved);
            return true;
        }        
    }
    return false;
}
void Board::lineToDots(vector<pair<int, int>>& line, pair<int, int>p, int row, int col){
    int rowDiff = row - p.first;
    int colDiff = col - p.second;
    int xDir = rowDiff ==  0 ? 0 : (rowDiff < 0?  1 : -1);
    int yDir = colDiff ==  0 ? 0 : (colDiff < 0? 1 : -1);
    for(int i = row+xDir, j = col+yDir; pair<int,int>{i,j}!=p; i+=xDir, j+=yDir){
        line.push_back({i,j});
    }
    line.push_back(p);
}
bool Board::canBlockLine(pair<int, int>src, vector<pair<int, int>> range){
    int originRow = src.first;
    int originCol = src.second;
    for(auto p : range){
        vector<pair<int,int>> dots{};
        lineToDots(dots, p, originRow, originCol);
        if(canBlockDot(src,dots)) return true;
    }
    return false;
}

bool Board::isCastling(const pair<int, int>& src, const pair<int, int>& dest){
    if(loc.find(src) != loc.end() && loc.find(src)->second->getMoved()) return false;
    if(!(src == pair<int, int>{1, 5} || src == pair<int, int>{8, 5})) return false;
    char c  = loc.find(src)->second->getName();
    if(c != 'K' && c != 'k') return false;
    
    bool kingIsBlack = loc.find(src)->second->isBlack();
    int rowNum;
    if(kingIsBlack) rowNum = 8;
    if(!kingIsBlack) rowNum = 1;

    if(!(dest == pair<int, int>{rowNum, 7} || dest == pair<int, int>{rowNum, 3})) return false;
    pair<int, int>rook{};
    if(dest == pair<int, int>{rowNum, 7}) rook = {rowNum,8};
    else if(dest == pair<int, int>{rowNum, 3}) rook = {rowNum,1};

    auto it = loc.find(rook);
    if(it == loc.end()) return false;
    char rookName = it->second->getName();
    if(kingIsBlack && rookName != 'r') return false;
    if(!kingIsBlack && rookName != 'R') return false;
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

    remove(src);
    add(dest, c);
    loc.find(dest)->second->setMoved();
    remove(rook);
    add(rookDest, rookName);
    loc.find(rookDest)->second->setMoved();
    currTurn++;
    updateBoard();
    return true;
}

bool Board::isEnPssnt(const pair<int, int>& src, const pair<int, int>& dest){
    if(enpssnt.first == pair<pair<int, int>, pair<int, int>>{src, dest} && currTurn == enpssntTurn + 1){
        remove(dest);
        auto kingHandler = loc.extract(src);
        kingHandler.key() = dest;
        loc.find(dest)->second->setMoved();
        updateBoard();
    }
    if(enpssnt.second == pair<pair<int, int>, pair<int, int>>{src, dest} && currTurn == enpssntTurn + 1){
        remove(dest);
        auto kingHandler = loc.extract(src);
        kingHandler.key() = dest;
        loc.find(dest)->second->setMoved();
        updateBoard();
    }
    
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

    auto itDest = loc.find(dest);
    bool movedSrc = it->second->getMoved();
    bool movedDest = false;
    char destN = '\0';
    if(itDest != loc.end()){
        destN = itDest->second->getName();
        movedDest = itDest->second->getMoved();
    } 
    
    remove(src);
    add(dest, n);
    loc.find(dest)->second->setMoved();
    if(n =='k') bKing->setMoved();
    if(n =='K') wKing->setMoved();
    if(bTurn && bKing != NULL && inCheck(*bKing)){
        undo(src, dest, movedDest, destN, movedSrc);
        return -1;
    }

    if(!bTurn && wKing != NULL && inCheck(*wKing)){
        wKing->setCoord(src.first, src.second);
        return -1;
    }
    remove(dest);
    remove(src);
    add(dest, n);
    loc.find(dest)->second->setMoved();
    currTurn++;
    updateBoard();
    return 0;
}


void Board::undo(const pair<int, int>& src, const pair<int, int>& dest, bool destMoved, char destName, bool srcMoved){
        char srcName = loc.find(dest)->second->getName();
        remove(dest);
        add(src, srcName);
        
        if(srcMoved){
            loc.find(src)->second->setMoved();
            if(srcName == 'k') bKing->setMoved();
            if(srcName == 'K') wKing->setMoved();
        } 
        if(destName != '\0') {
            add(dest, destName);
            if(destMoved) loc.find(dest)->second->setMoved();
        }
        
}

void Board::remove(const pair<int, int>& src){
    auto it = loc.find(src);
    if(it == loc.end()) return;
    char c = it->second->getName();
    if(c == 'k') bKing = NULL;
    if(c == 'K') wKing = NULL; 
    it->second.release();
    loc.erase(it->first);
}

int Board::add(const pair<int, int>& src, char p){
    if(p == 'K' && wKing == NULL){
        wKing = make_unique<King>(King(p, src.first, src.second));
        loc[src] = make_unique<King>(King(p, src.first, src.second));
        updateBoard();
        return 0;
    }

    if(p == 'k' && bKing == NULL){
        bKing = make_unique<King>(King(p, src.first, src.second));
        loc[src] = make_unique<King>(King(p, src.first, src.second));
        updateBoard();
        return 0;        
    }

    if(p == 'Q' || p == 'q'){
        loc[src] = make_unique<Queen>(Queen(p, src.first, src.second));
        updateBoard();
        return 0;
    }

    if(p == 'P' || p == 'p'){
        loc[src] = make_unique<Pawn>(Pawn(p, src.first, src.second));
        updateBoard();
        return 0;
    }

    if(p == 'N' || p == 'n'){
        loc[src] = make_unique<Knight>(Knight(p, src.first, src.second));
        updateBoard();
        return 0;
    }

    if(p == 'B' || p == 'b'){
        loc[src] = make_unique<Bishop>(Bishop(p, src.first, src.second));
        updateBoard();
        return 0;
    }

    if(p == 'R' || p == 'r'){
        loc[src] = make_unique<Rook>(Rook(p, src.first, src.second));
        updateBoard();
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
bool Board::promotionAvailable(){
    vector<int>rows{1,8};
    for(int rowNum : rows){
        for(int i = 1; i<=8; ++i){
            auto it = loc.find({rowNum, i});
            if(it == loc.end()) continue;
            char name = it->second->getName();
            if((name == 'P' || name =='p')){
                promotePawn = {rowNum, i};
                return true;
            } 
        }
    }
    return false;
}

bool Board::pawnOnLastRows(){
    vector<int>rows{1,8};
    for(int i : rows){
        for(int j = 1; j<=8; ++j){
            auto it = loc.find({i, j});
            if(it == loc.end()) continue;
            char name = it->second->getName();
            if(name =='p' || name == 'P') return true;
        }  
    }
    return false;
}
void Board::updateBoard(){
    for(auto it = loc.begin(); it != loc.end(); ++it){
        it->second->updateRange(loc);
    }
    if(bKing != NULL && inCheck(*bKing) ) winner = 1;
    else if(wKing != NULL && inCheck(*wKing)) winner = 2;
    else if(isStealmate()) winner = 0;
    else winner = -1;
}

vector<pair<pair<int, int>, pair<int, int>>> Board::getLegalMoves(char color) {
    vector<pair<pair<int, int>, pair<int, int>>> legalMoves;
    bool isWhite = (color == 'w');

     for (auto it = loc.begin(); it != loc.end(); ++it) {
        if (isWhite && !it->second->isBlack()) { // For white pieces
            for (auto move : it->second->getRange()) {
                legalMoves.push_back({it->first, move});
            }
        } else if (!isWhite && it->second->isBlack()) { // For black pieces
            for (auto move : it->second->getRange()) {
                legalMoves.push_back({it->first, move});
            }
        }
    }

    return legalMoves;
}

bool Board::verifySetup(){
    bool checkBlack = bKing != NULL ?inCheck(*bKing) : false;
    bool checkWhite = wKing != NULL ?inCheck(*wKing) : false;
    bool pwn = pawnOnLastRows();
    return !checkBlack && !checkWhite && !pwn;
}

void Board::promote(char c){
    remove(promotePawn);
    add(promotePawn, c);
    loc.find(promotePawn)->second->setMoved();
    promotePawn = {-1,-1};
}

char Board::whoseTurn(){
    return currTurn %2 == 0? 'B' : 'W';
}

int Board::getWinner(){ return winner; }