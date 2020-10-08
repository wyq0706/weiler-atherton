#ifndef LINES_H
#define LINES_H

#include <QPointF>
#include <vector>
#include <point.h>
#include <common.h>

class Circuit
{
public:
    Circuit();
    Circuit(bool);

    std::vector<Point*> points;

    drawStatus nowStatus;

    bool isClockwise;
};

#endif // LINES_H
