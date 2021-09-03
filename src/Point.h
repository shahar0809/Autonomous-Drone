//
// Created by shahar on 9/2/21.
//

#ifndef EXIT_SCAN_POINT_H
#define EXIT_SCAN_POINT_H

class Point
{
public:
    Point(double _x = 0, double _y = 0)
    {
        x = _x;
        y = _y;
    }
    double getx() const { return x; };
    double gety() const { return y; };

    void setx(double num) {
        x=num;
        return;
    }

    void sety(double num) {
        y=num;
        return;
    }

    void setx(string str) {
        x=convert (str);
        return;
    }

    void sety(string str) {
        y=convert (str);
        return;
    }

    double convert (string str)
    {
        int i,j;
        double num = 0, q = 0;
        bool Int = true, sign = false;

        for (i = 0; i < str.length(); i++)
        {
            if(str.at(i) == '-')
            {
                sign = true;
            }
            else if (str.at(i) == '.')
            {
                j=str.length()-i;
                Int = false;

            }
            else if (Int)
            {
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

private:
    double x, y;
};

#endif //EXIT_SCAN_POINT_H
