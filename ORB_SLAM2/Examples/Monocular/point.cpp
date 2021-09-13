#include "point.hpp"

Point::Point(float x, float y) : x(x),y(y) {}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

void Point::setX(float x) {
    Point::x = x;
}

void Point::setY(float y) {
    Point::y = y;
}

void Point::setX(std::string str) {
    Point::x = convert (str);;
}

void Point::setY(std::string str) {
    Point::y = convert (str);
}

double convert (std::string str){
    int i,j;
    float num = 0, q = 0;
    bool Int = true, sign = false;

    for (i = 0; i < str.length(); i++) {
        if(str.at(i)== '-')
        {
            sign = true;
        }else if (str.at(i) == '.') {
            j=str.length()-i;
            Int = false;

        }else if (Int) {
            num *= 10;
            num += (str.at(i) - '0');
        }
        else {
            q *= 10;
            q += (str.at(i) - '0');
        }
    }
    for(i=0;i<j-1;i++){
        q = q / 10;
    }
    num += q;
    if (sign){
        num = -num;
    }
    return num;
}