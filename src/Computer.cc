#include "headers/Computer.h"

Computer::Computer(char Colour) : Players(Colour) {}

pair<pair<int, int>, pair<int, int>> Computer::L1_GetMove(Board &CH_Board) const {
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> legalMoves = CH_Board.getLegalMoves(getColour());

}
