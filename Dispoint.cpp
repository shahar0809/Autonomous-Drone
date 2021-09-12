
#include "Dispoint.h"

Dispoint::Dispoint(){
    point.setx(0);
    point.sety(0);
}
void Dispoint::add(){
    num++;
}

Dispoint::Dispoint (Point _point){
point.setx(_point.getx());
point.sety(_point.gety());
}

void Dispoint::setdis(std::vector<Point> &vertex){
    if(point.getx()>=vertex[0].getx()&&point.getx()<=vertex[1].getx()){
        dis=std::min(abs(point.gety()-vertex[0].gety()),abs(point.gety()-vertex[3].gety()));
    }else if(point.gety()>=vertex[3].gety()&&point.gety()<=vertex[0].gety()){
        dis=std::min(abs(point.getx()-vertex[0].getx()),abs(point.getx()-vertex[2].getx()));
    }else{
        dis=std::min(std::min(sqrt(pow(point.getx()-vertex[0].getx(), 2) + pow(point.gety()-vertex[0].gety(), 2)),
                              sqrt(pow(point.getx()-vertex[1].getx(), 2) + pow(point.gety()-vertex[1].gety(), 2))),
                     std:: min(sqrt(pow(point.getx()-vertex[2].getx(), 2) + pow(point.gety()-vertex[2].gety(), 2)),
                               sqrt(pow(point.getx()-vertex[3].getx(), 2) + pow(point.gety()-vertex[3].gety(), 2))));
    }
}
bool operator<(const Dispoint& l, const Dispoint& r)
{
    return l.dis<r.dis;
}
