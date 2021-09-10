//
// Created by saker
//
//a class which is used in-order to divide the points into groups
// divide -- according to there distance from a rectangle edges
// each group has a representative (point)
// the distance between the representative and the rectangle (dis)
// the number of point in the group (num)

#include "Point.h"
#include <vector>

#ifndef DISPOINT_H
#define DISPOINT_H


class Dispoint {
public:
    Dispoint();
    Dispoint(const Point &point);

    //Getters
    const Point &GetRepresentative() const;
    double GetDistance() const;
    int GetNymberP() const;

    void setPoint(const Point &point);//set representative- first point in the group

    void setDis(std::vector<Point> &vertex);//calculate distance from the rectangle and save it

    void add();// add another point to the group


private:
    Point point = Point (0,0);
    double dis = 0;
    int num = 0;
};

bool operator<(const Dispoint& l, const Dispoint& r);
#endif //DISPOINT_H
