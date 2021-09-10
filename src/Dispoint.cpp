//
// Created by saker on 9/7/2021.
//

#include "Dispoint.h"

Dispoint::Dispoint(){
    Dispoint(Point(0,0));
}
Dispoint::Dispoint(const Point &point) : point(point) {}

const Point &Dispoint::GetRepresentative() const {
    return point;
}

double Dispoint::GetDistance() const {
    return dis;
}

int Dispoint::GetNymberP() const {
    return num;
}

void Dispoint::setPoint(const Point &point) {
    Dispoint::point = point;
}

void Dispoint::add() {
    Dispoint::num += 1;
}

void Dispoint::setDis(std::vector<Point> &vertex){
    Point point = Dispoint::point;
    if(point.getX()>=vertex[0].getX()&&point.getX()<=vertex[1].getX()){
        Dispoint::dis = fmin(abs(point.getY()-vertex[0].getY()),abs(point.getY()-vertex[3].getY()));
    }else if(point.getY()>=vertex[3].getY()&&point.getY()<=vertex[0].getY()){
        Dispoint::dis = fmin(abs(point.getX()-vertex[0].getX()),abs(point.getX()-vertex[2].getX()));
    }else{
        Dispoint::dis = fmin(fmin(sqrt(pow(point.getX()-vertex[0].getX(), 2) + pow(point.getY()-vertex[0].getY(), 2)),
                    sqrt(pow(point.getX()-vertex[1].getX(), 2) + pow(point.getY()-vertex[1].getY(), 2))),
                fmin(sqrt(pow(point.getX()-vertex[2].getX(), 2) + pow(point.getY()-vertex[2].getY(), 2)),
                    sqrt(pow(point.getX()-vertex[3].getX(), 2) + pow(point.getY()-vertex[3].getY(), 2))));
    }
}

bool operator<(const Dispoint& l, const Dispoint& r){
    return l.GetDistance()<r.GetDistance();
}





