#include "point.hpp"

Point::Point(double _x, double _y) : x(_x),y(_y) {}

double Point::get_x() { return x; };
double Point::get_y() { return y; };

void Point::set_x(double num) {
    x=num;
    return;
}

void Point::set_y(double num) {
    y=num;
    return;
}

void Point::set_x(std::string str) {
    x=convert (str);
    return;
}

void Point::set_y(std::string str) {
    y=convert (str);
    return;
}

double Point::convert (std::string str)
{
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

cv::Mat<double> Point::convertToMat (Point point){
    double data[2];
    data[0]=point.get_x();
    data[1]=point.get_y();
    cv::Mat mat = cv::Mat(2, 1, cv::DataType<double>::type, data);
}
