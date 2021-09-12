#include "Point.h"
#include <vector>

#ifndef UNTITLED2_DISPOINT_H
#define UNTITLED2_DISPOINT_H


class Dispoint
{
public:
    Point point;
    double dis=0;
    int num=0;
    Dispoint();
    void add();

    Dispoint (Point _point);

    void setdis(std::vector<Point> &vertex);

};

bool operator<(const Dispoint& l, const Dispoint& r);


#endif //UNTITLED2_DISPOINT_H
