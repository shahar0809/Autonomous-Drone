#include "FindExit.h"
#include <cmath>
#define BLOCK_SIZE 0.1
static int count = 1;
#include <iostream>
#include <fstream>
#include "Point.h"
#include <vector>

#ifndef FINDPATH_H
#define FINDPATH_H

//divide the rectangle (the way between the position of the drone and the exit point)
//into blocks and find the number of points in the block
int* cutBlocks  (std::vector<Point> &points,int& col,int& row,Point pos, Point exit);

// to find if there is a path from
// top left (the position of the drone) to bottom right (the exit point) in the given matrix.
int isPath(int* arr,int row, int col);

//find the point x',y' that the block i,j represent - according to the positions of the drone and the exit.
Point setxy(double x, double y, int j, int i,Point exit, Point pos);

//add the path points to the vector exitP
//start from the right bottom to top left
void findpath(std::vector<Point> &exitP,int* arr,int row, int col,Point exit,Point pos);

//find the exit path
void gotoExit(Point exit, Point pos, double z);


#endif //FINDPATH_H
