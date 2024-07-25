#include "../headers/Piece.h"
#include <cctype>

Piece::~Piece(){};

Piece::Piece(char name, int r, int c):name{name}, row{r}, col{c}{}

char Piece::getName(){ return name;}

bool Piece::isBlack(){
    return std::islower(name);
}

int Piece::movableNum(){
    return range.size();
}

bool Piece::getMoved(){
    return moved;
}

void Piece::setMoved(){
    moved = true;
}

pair<int, int> Piece::getCoord(){
    return pair<int, int>{row, col};
}

void Piece::setCoord(int r, int c){
    row = r;
    col = c;
}

