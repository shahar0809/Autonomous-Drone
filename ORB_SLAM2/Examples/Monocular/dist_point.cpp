#include "dist_point.hpp"

Dispoint::Dispoint(){
    point.setX(0);
    point.setY(0);
}
void Dispoint::add(){
    num++;
}

Dispoint::Dispoint (Point _point){
    point.setX(_point.getX());
    point.setY(_point.getY());
}

void Dispoint::setdis(std::vector<Point> &vertex){
    if(point.getX()>=vertex[0].getX()&&point.getX()<=vertex[1].getX()){
        dis=std::min(abs(point.getY()-vertex[0].getY()),abs(point.getY()-vertex[3].getY()));
    }else if(point.getY()>=vertex[3].getY()&&point.getY()<=vertex[0].getY()){
        dis=std::min(abs(point.getX()-vertex[0].getX()),abs(point.getX()-vertex[2].getX()));
    }else{
        dis=std::min(std::min(sqrt(pow(point.getX()-vertex[0].getX(), 2) + pow(point.getY()-vertex[0].getY(), 2)),
                              sqrt(pow(point.getX()-vertex[1].getX(), 2) + pow(point.getY()-vertex[1].getY(), 2))),
                     std:: min(sqrt(pow(point.getX()-vertex[2].getX(), 2) + pow(point.getY()-vertex[2].getY(), 2)),
                               sqrt(pow(point.getX()-vertex[3].getX(), 2) + pow(point.getY()-vertex[3].getY(), 2))));
    }
}
bool operator<(const Dispoint& l, const Dispoint& r)
{
    return l.dis<r.dis;
}
