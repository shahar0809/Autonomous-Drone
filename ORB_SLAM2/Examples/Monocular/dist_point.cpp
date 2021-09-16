#include "dist_point.hpp"

Dispoint::Dispoint()
{
    point.set_x(0);
    point.set_y(0);
}

void Dispoint::add()
{
    num++;
}

Dispoint::Dispoint (Point _point)
{
    point.set_x(_point.get_x());
    point.set_y(_point.get_y());
}

void Dispoint::set_dist(std::vector<Point> &vertex)
{
    if (point.get_x() >= vertex[0].get_x() && 
    point.get_x() <= vertex[1].get_x())
    {
        dis = std::min(abs(point.get_y() - vertex[0].get_y()),
        abs(point.get_y() - vertex[3].get_y()));
    }
    else if (point.get_y() >= vertex[3].get_y() &&
    point.get_y() <= vertex[0].get_y())
    {
        dis = std::min(abs(point.get_x() - vertex[0].get_x()), 
        abs(point.get_x() - vertex[2].get_x()));
    }
    else
    {
        dis = std::min(std::min(sqrt(pow(point.get_x() - vertex[0].get_x(), 2) 
        + pow(point.get_y()-vertex[0].get_y(), 2)),
                              sqrt(pow(point.get_x()-vertex[1].get_x(), 2) + pow(point.get_y()-vertex[1].get_y(), 2))),
                     std:: min(sqrt(pow(point.get_x()-vertex[2].get_x(), 2) + pow(point.get_y()-vertex[2].get_y(), 2)),
                               sqrt(pow(point.get_x()-vertex[3].get_x(), 2) + pow(point.get_y()-vertex[3].get_y(), 2))));
    }
}
bool operator<(const Dispoint& l, const Dispoint& r)
{
    return l.dis<r.dis;
}