#ifndef COMPUTER_H
#define COMPUTER_H
#include <random>
#include <vector>
#include "Players.h"

using namespace std;

class Computer : public Players {
    public:
        Computer(char Colour);
        pair<pair<int, int>, pair<int, int>> L1_GetMove(Board &CH_Board) const override;
        pair<pair<int, int>, pair<int, int>> L2_GetMove(Board &CH_Board) const override;
        pair<pair<int, int>, pair<int, int>> L3_GetMove(Board &CH_Board) const override;
        pair<pair<int, int>, pair<int, int>> L4_GetMove(Board &CH_Board) const override;
};


#endif
