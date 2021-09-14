#include "point.hpp"


Point::Point(float _x , float _y ) {
    x = _x;
    y = _y;
}
float Point::getX() { return x; };
float Point::getY() { return y; };

void Point::setX(float num) {
    x=num;
    return;
}

void Point::setY(float num) {
    y=num;
    return;
}

void Point::setX(std::string str) {
    x=convert (str);
    return;
}

void Point::setY(std::string str) {
    y=convert (str);
    return;
}

float convert (std::string str)
{
    int i,j;
    double num = 0, q = 0;
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
