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
        virtual pair<pair<int, int>, pair<int, int>> L1_GetMove(Board &CH_Board) const = 0;
        virtual pair<pair<int, int>, pair<int, int>> L2_GetMove(Board &CH_Board) const = 0;
        virtual pair<pair<int, int>, pair<int, int>> L3_GetMove(Board &CH_Board) const = 0;
        virtual pair<pair<int, int>, pair<int, int>> L4_GetMove(Board &CH_Board) const = 0;
};

#endif
