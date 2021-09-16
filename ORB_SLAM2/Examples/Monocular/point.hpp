#ifndef UNTITLED2_POINT_H
#define UNTITLED2_POINT_H
#include <string>
#include <iostream>

class Point
{
public:
    Point(double _x = 0 , double _y = 0 );

    double get_x();
    double get_y();

    void set_x(double num);
    void set_y(double num);

    //we get the numbers from the csv file as a string
    void set_x(std::string str);
    void set_y(std::string str);

    //convert string to a double number
    double convert (std::string str);

private:
    double x, y;
};


#endif //UNTITLED2_POINT_H
