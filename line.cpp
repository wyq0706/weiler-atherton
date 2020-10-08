#include "line.h"

Line::Line()
{
    this->isMain=false;
}

Line::Line(Point& a,Point& b)
{
    this->start=a;
    this->end=b;
    this->isMain=false;
}

Line::Line(Point& a,Point& b,bool isMain)
{
    this->start=a;
    this->end=b;
    this->isMain=isMain;
}
