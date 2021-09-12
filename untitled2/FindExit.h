#include "Dispoint.h"

#ifndef UNTITLED2_FINDEXIT_H
#define UNTITLED2_FINDEXIT_H


void getxy(std::vector<Point> &xzy);
void findrectangle (std::vector<Point> &points, std::vector<Point> &vertex);
void clearinside (std::vector<Point> &points, std::vector<Point> &outp, std::vector<Point> &vertex);
void Exit(std::vector<Point> &points, std::vector<Point> &vertex,Point& exit);
double dis(Point p1, Point p2);
Point FindExit();


#endif //UNTITLED2_FINDEXIT_H
