#ifndef POLYGON_H
#define POLYGON_H


#include <QPointF>
#include <vector>
#include <QPainter>
#include <QDebug>

#include <circuit.h>
#include <common.h>
#include <line.h>

class Polygon
{
public:
    Polygon();
    Polygon(PolygonRank r);

    // 添加顶点
    void addPoint(QPointF p);

    // 闭合多边形
    void closeLoop();

    // 绘制
    void drawPolygon(QPainter &p);

    // 绘制
    void drawClippedPath(QPainter &p);

    void changeRank();

    void clearPoints();

public:
    // 边表
    std::vector<Line* > lines;

    // 顶点表
    // 按环记顶点：第一个环认为是逆时针外环，后面均是顺时针内环
    std::vector<Circuit*> circuits;

    Circuit* curCircuit=NULL;

private:
    PolygonRank rank;

};

#endif // PPOLYGON_H
