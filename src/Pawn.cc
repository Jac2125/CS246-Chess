#include "headers/Pawn.h"

Pawn::Pawn(char c, bool black):name{c}{}

bool Pawn::canMove(pair<int, int> srcCd, pair<int, int> destCd, map<pair<int,int>, Piece> loc) {

    if(srcCd.first + 1 != destCd.first) return false;
    bool pieceExist = loc.find(destCd) == loc.end();
    if(srcCd.second == destCd.second) return pieceExist? false : true;

    if(srcCd.second - 1 == destCd.second || srcCd.first + 1 == destCd.second){
        if(!pieceExist) return true;
    }

    bool destIsBlack = loc.find(destCd)->second.isBlack();
    bool srcIsBlack = loc.find(srcCd)->second.isBlack();
    if(srcIsBlack != destIsBlack) return true;
    return false;

}

void Pawn::setEnPssnt(int currTurn){
    turn = currTurn;
}

int Pawn::getEnPssntTurn(){ return turn;}