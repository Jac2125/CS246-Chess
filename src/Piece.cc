#include "headers/Piece.h"
#include <cctype>

Piece::~Piece(){};

char Piece::getName(){ return name;}

bool Piece::isBlack(){
    return std::islower(name);
}