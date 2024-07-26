#ifndef PLAYERS_H
#define PLAYERS_H
#include <utility>
#include <map>
#include <string>
#include "Board.h"
using namespace std;

class Players {
    protected:
        char colour;
        int score = 0;
    public:
        Players(char Colour);
        char getColour();
        int getScore();
        void win();
};

#endif
