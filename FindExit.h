#include "Dispoint.h"

#ifndef UNTITLED2_FINDEXIT_H
#define UNTITLED2_FINDEXIT_H

//get the data from "pointData.csv" and save it in a vector (xzy)
void getxy(std::vector<Point> &xzy);

//given the list of points
//the function build a rectangle using the average value according to x and the distance from this point
// and the same with y
void findrectangle (std::vector<Point> &points, std::vector<Point> &vertex);

//save in the vector outp all the points that are outside the rectangle.
void clearinside (std::vector<Point> &points, std::vector<Point> &outp, std::vector<Point> &vertex);

//divide into blocks
//delete blocks with few points
//return the representative point of the block with maximum distance as the exit point
void Exit(std::vector<Point> &points, std::vector<Point> &vertex,Point& exit);

//return the distance between two points
double dis(Point p1, Point p2);

//this function uses the other functions and return the exit point
Point FindExit();


#endif //UNTITLED2_FINDEXIT_H
