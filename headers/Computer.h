#ifndef COMPUTER_H
#define COMPUTER_H
#include <random>
#include <cstdlib> 
#include <vector>
#include <utility>
#include "Players.h"

using namespace std;

class Computer : public Players {
    public:
        Computer(char Colour);
        pair<pair<int, int>, pair<int, int>> L1_GetMove(Board &CH_Board) const;
        pair<pair<int, int>, pair<int, int>> L2_GetMove(Board &CH_Board) const;
        pair<pair<int, int>, pair<int, int>> L3_GetMove(Board &CH_Board) const;
};


#endif