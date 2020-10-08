#include "circuit.h"

Circuit::Circuit()
{
    this->nowStatus=POINTS;
}

Circuit::Circuit(bool isClockwise)
{
    this->nowStatus=POINTS;
    this->isClockwise=isClockwise;
}
