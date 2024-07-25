#include "../headers/Players.h"

Players::Players(char Colour) : colour{Colour} {}

char Players::getColour() {
    return this->colour;
}

int Players::getScore() {
    return this->score;
}

void Players::win() {
    this->score++;
}
