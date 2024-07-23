#include "headers/Piece.h"
#include <cctype>

Piece::~Piece(){};

Piece::Piece(char name, int r, int c):name{name}, row{r}, col{c}{}

char Piece::getName(){ return name;}

bool Piece::isBlack(){
    return std::islower(name);
}

void Piece::updateRange(map<pair<int,int>, Piece>& loc){return;}

pair<int, int> Piece::getCoord(){
    return pair<int, int>{row, col};
}

void Piece::setCoord(int r, int c){
    row = r;
    col = c;
}