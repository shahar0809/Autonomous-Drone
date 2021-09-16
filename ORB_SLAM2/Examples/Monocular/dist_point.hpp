#ifndef UNTITLED2_DISPOINT_H
#define UNTITLED2_DISPOINT_H

#include "point.hpp"
#include <vector>

/*
* A class which is used in-order to divide the points into groups
* divide -- according to there distance from a rectangle edges
* each group has a representative (point)
* the distance between the representative and the rectangle (dis)
* the number of point in the group (num)
*/

class Dispoint
{
public:
    Point point; //Representative- the point with max distance
    double dis = 0;
    int num = 0;
    Dispoint();

    // add another point to the group
    void add();

    Dispoint (Point _point);

    // calculate distance from the rectangle and save it
    void set_dist(std::vector<Point> &vertex);

};

bool operator<(const Dispoint& l, const Dispoint& r);


#endif //UNTITLED2_DISPOINT_H
