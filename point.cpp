#include "point.h"

Point::Point():x(0),y(0)
{
    this->isIntersectionPoint=false;
}

Point::Point(Point& a)
{
    this->x=a.x;
    this->y=a.y;
}

Point::Point(double x,double y)
{
    this->x=x;
    this->y=y;
    this->isIntersectionPoint=false;
    this->isEntering=false;
}

bool Point::operator==(const Point& p)const
{
    return p.x==this->x&&p.y==this->y;
}

Point Point::operator*(double a)
{
    Point p;
    p.x=this->x*a;
    p.y=this->y*a;
    return p;
}

//Point& Point::operator=(const Point& p)
//{
//    this->x=p.x;
//    this->y=p.y;
//    return *this;
//}

Point Point::operator+(const Point &p)
{
    Point temp(0, 0);
    temp.x = this->x + p.x;
    temp.y = this->y + p.y;
    return temp;
}

Point Point::operator-(const Point &p)
{
    Point temp(0, 0);
    temp.x = this->x - p.x;
    temp.y = this->y - p.y;
    return temp;
}

Point::Point(double x,double y, bool isInterSectionPoint,bool isEntering):x(x),y(y), isEntering(isEntering), isIntersectionPoint(isInterSectionPoint)
{
}
