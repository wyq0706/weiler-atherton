#ifndef LINE_H
#define LINE_H

#include <point.h>

class Line
{
public:
    Line();
    Line(Point& a,Point& b);
    Line(Point& a,Point& b,bool isMain);

    Point start;
    Point end;

    bool isMain; // necessary for showing clipped polygons
};

#endif // LINE_H
