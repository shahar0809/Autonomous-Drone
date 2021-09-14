#ifndef POINT_H
#define POINT_H

#include <string>
#include <opencv2/core/core.hpp>

class Point
{
public:

    Point(float x = 0, float y = 0);

    float getY();
    float getX();

    void setX(float x);
    void setY(float y);

    //we get the numbers from the csv file as a string
    void setX(std::string x);
    void setY(std::string y);

    explicit operator cv::Mat()
    {
        return cv::Mat { x, y };
    }

private:
    float x,y;
};

//convert string to a double number
float convert (std::string str);

#endif //POINT_H
