#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();
    Point(double x,double y);
    Point(double x,double y, bool isInterSectionPoint,bool isEntering);
    Point(Point&a);
    bool operator==(const Point& p) const;
    Point operator*(double a);
    Point operator+(const Point& p);
    Point operator-(const Point& p);
    // Point& operator=(const Point& p);

public:
    double x;
    double y;
    bool isEntering;
    bool isIntersectionPoint;
    bool isChecked=false;
};

#endif // POINT_H
