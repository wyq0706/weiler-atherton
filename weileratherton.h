#ifndef WEILERATHERTON_H
#define WEILERATHERTON_H

#include <QDebug>

#include <point.h>
#include <polygon.h>

#include <algorithm>
#include <math.h>

class WeilerAtherton
{
public:
    WeilerAtherton();

    // 判断两线段是否相交，相交则返回交点
    Point getIntersection(Point& a_start,Point& a_end,Point& b_start,Point& b_end,bool &mark);

    // 求交点、归类，并按顺序插入到顶点表中，后裁剪
    Polygon& perform(Polygon & subject, Polygon & clipping);

private:
    // 求叉积
    double crossProduct(Point& a,Point& b);

    // 判断点是否在直线上
    bool inLine(Point& spot,Point& a,Point& b);

    // 将交点加入顶点表
    void addPointToVertexList(std::vector<Circuit*>& circuits, Point& pStart,Point& pEnd,Point& ip);

    // 裁剪
    Point doClip(std::vector<Circuit*>& walking_points, Polygon& pol, Point& start,bool which);

    // 求两点距离
    double distance(Point& p, Point& q);

    int vecContains(std::vector<Point*> list, Point& p);
};

#endif // WEILERATHERTON_H
