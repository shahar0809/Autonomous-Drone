#ifndef UNTITLED2_POINT_H
#define UNTITLED2_POINT_H
#include <string>
#include <iostream>

class Point
{
public:
    Point(double _x = 0 , double _y = 0 );
    double getx();
    double gety();
    void setx(double num);
    void sety(double num);
    void setx(std::string str);
    void sety(std::string str);
    double convert (std::string str);

private:
    double x, y;
};


#endif //UNTITLED2_POINT_H
