#include "polygon.h"

Polygon::Polygon()
{
}

Polygon::Polygon(PolygonRank r)
{
    this->rank=r;
}

void Polygon::addPoint(QPointF p)
{
    if(!this->curCircuit||this->curCircuit->nowStatus==CLOSED){
        Circuit* newCirCuit=new Circuit();
        if(this->circuits.size()==0)
        {
            newCirCuit->isClockwise=true;
        }else{
            newCirCuit->isClockwise=false;
        }
        this->curCircuit=newCirCuit;
        this->curCircuit->points.push_back(new Point(p.x(),p.y()));
        this->circuits.push_back(newCirCuit);
    }else
    {
        this->curCircuit->points.push_back(new Point(p.x(),p.y()));
        // add line
        Line* line=new Line();
        line->start=*this->curCircuit->points[this->curCircuit->points.size()-2];
        line->end=*this->curCircuit->points[this->curCircuit->points.size()-1];
        this->lines.push_back(line);
    }
}

void Polygon::closeLoop()
{
    qDebug()<<"close now";
    if(this->curCircuit)
    {
        this->curCircuit->nowStatus=CLOSED;
        // add line
        Line* line=new Line();
        line->start=*this->curCircuit->points[this->curCircuit->points.size()-1];
        line->end=*this->curCircuit->points[0];
        this->lines.push_back(line);
        qDebug()<<"addNow";
    }
}

void Polygon::changeRank()
{
    if(this->rank==MAIN)
    {
        this->rank=CUT;
    }else{
        this->rank=MAIN;
    }
}

void Polygon::clearPoints()
{
    for(auto circuit:this->circuits)
    {
        for(std::vector<Point*>::iterator it= circuit->points.begin();it!=circuit->points.end();)
        {
            if((*it)->isIntersectionPoint)
            {
                // delete *it;
                it=circuit->points.erase(it);
            }else{
                it++;
            }
        }
    }
}


void Polygon::drawPolygon(QPainter &painter)
{
    auto oldPen = painter.pen();
    QPen mypen;
    mypen.setWidth(3);
    if(this->rank==MAIN)
    {
        mypen.setColor(Qt::red);
    }else{
        mypen.setColor(Qt::black);
    }
    painter.setPen(mypen);
    for(auto i:this->circuits)
    {
        if(i->nowStatus==POINTS)
        {
            for(auto j:i->points)
            {
                painter.drawPoint(QPointF(j->x,j->y));
            }
        }else{
            for (auto j = 0; j < int(i->points.size()); j++) {
                Point *next;
                if (j + 1 < int(i->points.size())) {
                    next = i->points[j + 1];
                } else {
                    next = i->points[0];
                }
                painter.drawLine(QPointF(i->points[j]->x,i->points[j]->y), QPointF(next->x,next->y));
            }
        }
    }
    painter.setPen(oldPen);
}

void Polygon::drawClippedPath(QPainter &painter)
{
    auto oldPen = painter.pen();
    QPen mypen;
    mypen.setWidth(3);
    for(auto line:this->lines)
    {
        if(line->isMain)
        {
             mypen.setColor(Qt::red);
        }else{
             mypen.setColor(Qt::black);
        }
        painter.setPen(mypen);
        painter.drawLine(QPointF(line->start.x,line->start.y),QPointF(line->end.x,line->end.y));
    }
    painter.setPen(oldPen);
}

