#include "weileratherton.h"

WeilerAtherton::WeilerAtherton()
{

}

int WeilerAtherton::vecContains(std::vector<Point*> list, Point& p) {
//    for(std::vector<Point*>::iterator i=list.begin();i!=list.end();i++)
    for(int i=0;i<int(list.size());i++)
    {
        if(list[i]->x==p.x&&list[i]->y==p.y)
        {
            return i;
        }
    }
    return list.size();
}

double WeilerAtherton::crossProduct(Point &a, Point &b)
{
    return a.x*b.y-a.y*b.x;
}

bool WeilerAtherton::inLine(Point& spot,Point& a,Point& b)
{
    bool x=spot.x<=std::max(a.x,b.x)&&spot.x>=std::min(a.x,b.x);
    bool y=spot.y<=std::max(a.y,b.y)&&spot.y>=std::min(a.y,b.y);
    return x&&y;
}

double WeilerAtherton::distance(Point& p, Point& q){
    return std::sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
}

Point WeilerAtherton::doClip(std::vector<Circuit*>& walking_points, Polygon& pol, Point& start,bool which) {
    // find in each circuit
    for(auto circuit:walking_points)
    {
        int iter = vecContains(circuit->points,start);
        int count=0;
        if(iter!=int(circuit->points.size()))
        {
            while (true) {
                pol.curCircuit->points.push_back(circuit->points[iter]);
                if(count>0){
                    Line* line=new Line(*circuit->points[(iter-1+circuit->points.size())%circuit->points.size()],*circuit->points[iter],which);
                    pol.lines.push_back(line);
                }
                qDebug()<<"new add: "<<circuit->points[iter]->x<<"--"<<circuit->points[iter]->y;
                iter++;

                // 循环列表
                if (iter == int(circuit->points.size())) {
                    iter = 0;
                }

                qDebug()<<"to find: "<<circuit->points[iter]->x<<"--"<<circuit->points[iter]->y;
                if(circuit->points[iter]->isIntersectionPoint){
                    break;
                }
                count++;
            }
            Line* line=new Line(*circuit->points[(iter-1+circuit->points.size())%circuit->points.size()],*circuit->points[iter],which);
            pol.lines.push_back(line);
            qDebug()<<"here find: "<<iter;
            return *circuit->points[iter];
        }
    }
    // should not happend
    Point p;
    return p;
}

Point WeilerAtherton::getIntersection(Point& a_start,Point& a_end,Point& b_start,Point& b_end,bool &mark)
{
    double a1 = a_end.y - a_start.y;
    double b1 = a_start.x-a_end.x;
    double c1 = -a_start.x*a1-b1*a_start.y;
    double a2 = b_end.y-b_start.y;
    double b2 = b_start.x - b_end.x;
    double c2 = -a2 * b_start.x - b2 * b_start.y;


    Point u,v;
    u=a_end-a_start;
    v=b_end-b_start;

    double determinant = crossProduct(u,v);

    // qDebug()<<a1<<" "<<b1<<" "<<c1<<" "<<a2<<" "<<b2<<" "<<c2<<" "<<determinant<<endl;

    Point p;
    if (determinant == 0) {
        mark=false;
    }
    else {
        p.x = (b1 * c2 - b2 * c1) / determinant;
        p.y = (a2 * c1 - a1 * c2) / determinant;


        // check if point belongs to segment
        if (inLine(p,a_start,a_end)&&inLine(p,b_start,b_end)){
            p.isIntersectionPoint=true;
            // determine if the point is entering by determinant
            p.isEntering=determinant<0;
            mark=true;
        }else
        {
            mark=false;
        }
    }
    return p;
}


Polygon& WeilerAtherton::perform(Polygon & subject, Polygon & clipping) {
    Polygon* pol=new Polygon;

    std::vector<Point*> entering_points;
    std::vector<Point*> exiting_points;

    bool mark;

    for (auto i:subject.lines) {
        for (auto j:clipping.lines) {
            Point* ip=new Point();
            *ip=getIntersection(i->start,i->end,j->start,j->end,mark);

            if (mark) {
                if (ip->isEntering) {
                    entering_points.push_back(ip);
                }
                else {
                    exiting_points.push_back(ip);
                }
                addPointToVertexList(subject.circuits, i->start,i->end, *ip);
                addPointToVertexList(clipping.circuits, j->start,j->end, *ip);
            }
        }
    }

    qDebug()<<"search over"<<endl;

    // debug -- print vertex list
    for(auto circuit:subject.circuits)
    {
        for(auto j:circuit->points)
        {
            qDebug()<<j->x<<" "<<j->y<<" (isIntersect)"<<j->isIntersectionPoint<<" (isEntering)"<<j->isEntering;
        }
    }
    for(auto circuit:clipping.circuits)
    {
        for(auto j:circuit->points)
        {
            qDebug()<<j->x<<" "<<j->y<<" (isIntersect)"<<j->isIntersectionPoint<<" (isEntering)"<<j->isEntering;
        }
    }
    // debug -- print vertex list

    entering_points.swap(exiting_points);
    auto iter_entering_points = entering_points.begin();
    while (iter_entering_points != entering_points.end()) {
        if((*iter_entering_points)->isChecked)
        {
            *iter_entering_points++;
            continue;
        }
        Circuit* circuit=new Circuit;
        pol->curCircuit=circuit;
        pol->circuits.push_back(circuit);
        Point* start = *iter_entering_points++;
        Point next = *start;
        start->isChecked=true;
        int where;
        do {
            next = doClip(subject.circuits, *pol, next,true);
            next = doClip(clipping.circuits, *pol, next,false);
            where=vecContains(entering_points,next);
            (*(entering_points.begin()+where))->isChecked=true;
        } while (next.x != start->x||next.y!=start->y);
    }

    return *pol;
}


void WeilerAtherton::addPointToVertexList(std::vector<Circuit*>& circuits,Point& pStart,Point& pEnd, Point& ip) {
    for(int i=0;i<int(circuits.size());i++)
    {
        Circuit* circuit=circuits[i];
        for(auto j:circuit->points)
        {
            qDebug()<<" "<<j->x<<" "<<j->y<<" (isIntersect)"<<j->isIntersectionPoint<<" (isEntering)"<<j->isEntering;
        }

        // debug: cannot use stl for wrong use of */&
        int start = vecContains(circuit->points,pStart);
        if(start==int(circuit->points.size()))
        {
            qDebug()<<"end";
            continue;
        }
        int end = vecContains(circuit->points,pEnd);

        int it = start;
        double dist_from_start = distance(ip, *circuit->points[it]);
        qDebug()<<"find"<<circuit->points[it]->x<<" "<< circuit->points[it]->y;

        // 处理多个交点
        while (it != end && it != int(circuit->points.size())) {
            if (distance(*circuit->points[it],*circuit->points[start]) >= dist_from_start) {
                break;
            }
            it++;
        }
        circuit->points.insert(circuit->points.begin()+it,&ip);
        break;
    }
}
