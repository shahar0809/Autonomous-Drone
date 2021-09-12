#ifndef POINT_H
#define POINT_H

#include <string>

class Point {
public:

    Point(double x = 0, double y = 0);

    double getY() const;
    double getX() const;

    void setX(double x);
    void setY(double y);

    //we get the numbers from the csv file as a string
    void setX(std::string x);
    void setY(std::string y);

private:
    double x,y;
};

//convert string to a double number
double convert (std::string str);

#endif //POINT_H
