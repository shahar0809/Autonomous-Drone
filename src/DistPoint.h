#include "Point.h"

#ifndef EXIT_SCAN_DISTPOINT_H
#define EXIT_SCAN_DISTPOINT_H

class DistPoint
{
public:
    Point point;
    double dis = 0;
    int num = 0;

    DistPoint()
    {
        point.setx(0);
        point.sety(0);
    }

    void add()
    {
        num++;
    }

    DistPoint (Point _point)
    {
        point.setx(_point.getx());
        point.sety(_point.gety());
    }

    void set_dist(vector<Point> &vertex)
    {
        if(point.getx()>=vertex[0].getx()&&point.getx()<=vertex[1].getx())
        {
            dis = min(abs(point.gety() - vertex[0].gety()), abs(point.gety()-vertex[3].gety()));
        }
        else if(point.gety() >= vertex[3].gety() && point.gety() <= vertex[0].gety())
        {
            dis = min(abs(point.getx() - vertex[0].getx()), abs(point.getx()-vertex[2].getx()));
        }
        else
        {
            dis=min(min(sqrt(pow(point.getx()-vertex[0].getx(), 2) + pow(point.gety()-vertex[0].gety(), 2)),
                        sqrt(pow(point.getx()-vertex[1].getx(), 2) + pow(point.gety()-vertex[1].gety(), 2))),
                    min(sqrt(pow(point.getx()-vertex[2].getx(), 2) + pow(point.gety()-vertex[2].gety(), 2)),
                        sqrt(pow(point.getx()-vertex[3].getx(), 2) + pow(point.gety()-vertex[3].gety(), 2))));
        }
    }
};

#endif //EXIT_SCAN_DISTPOINT_H
