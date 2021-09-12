#ifndef EXIT_SCAN_DETECT_EXIT_HPP
#define EXIT_SCAN_DETECT_EXIT_HPP

#include "dist_point.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#define SAME_BLOCK 0.03
#define MIN 7

//get the data from "pointData.csv" and save it in a vector (xzy)
void getxy(std::vector<Point>& xzy);

void findrectangle (std::vector<Point> &points, std::vector<Point> &vertex);

//save in the vector outp all the points that are outside the rectangle.
void clearinside (std::vector<Point> &points, std::vector<Point> &outp, std::vector<Point> &vertex);

//return the distance between two points
double dis(Point p1, Point p2);

//divide into blocks
//delete blocks with few points
//return the representative point of the block with maximum distance as the exit point
void getExit(std::vector<Point> &points, std::vector<Point> &vertex,Point& exit);

//this function uses the other functions and return the exit point
Point FindExit();


#endif //EXIT_SCAN_DETECT_EXIT_HPP
