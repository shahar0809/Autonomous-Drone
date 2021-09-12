//
// flytoExit -- commands to the tello
//

#include "find_path.hpp"
#include <cmath>
#define BLOCK_SIZE 0.1
static int count = 1;

//divide the rectangle (the way between the position of the drone and the exit point)
//into blocks and find the number of points in the block
int* cutBlocks  (std::vector<Point> &points,int& col,int& row,Point pos, Point exit){
    int i,j;
    double x,y;
    x = abs(pos.getX()-exit.getX());
    y = abs(pos.getY()-exit.getY());
    x = x/(BLOCK_SIZE/count);
    y = y/(BLOCK_SIZE/count);
    row= (int) y;
    col= (int) x;

    int* blocks= new int [row*col];

    for(int i=0;i < row;i++){
        for(int j=0;j < col;j++){
            blocks[i*col+j]=0;
        }
    }


    for (int k=0; k<points.size(); k++){
        i=abs((points[k].getX()-pos.getX())/(BLOCK_SIZE/count));
        j=abs((points[k].getY()-pos.getY())/(BLOCK_SIZE/count));
        blocks[i*col+j]++;
    }
    //the next time we enter this function we should divide into smaller blocks
    //since the next time we enter this function it will be the situation that we couldn't find exit path
    count++;

    return blocks;
}

// to find if there is a path from
// top left (the position of the drone) to bottom right (the exit point) in the given matrix.
int isPath(int* arr,int row, int col){
    //-1 - can’t go through this cell
    //0 - can go
    arr[0] = 1;//visited


    // Mark reachable (from top left) nodes
    // in first row and first column.
    for (int i = 1; i < row; i++)
        if (arr[i*col] != -1)
            arr[i*col] = arr[(i-1)*col];

    for (int j = 1; j < col; j++)
        if (arr[j] != -1)
            arr[j] = arr[j - 1];



    // Mark reachable nodes in remaining
    // matrix.
    for (int i = 1; i < row; i++)
        for (int j = 1; j < col; j++)
            if (arr[i*col+j] != -1)
                arr[i*col+j] = fmax(arr[i*col+j-1], arr[(i-1)*col+j]);


    if (arr[row*col-1] == 1){
        return 0;
    }else{
        return 1;//there is no path
    }
}

//find the point x',y' that the block i,j represent - according to the positions of the drone and the exit.
Point setxy(double x, double y, int j, int i,Point exit, Point pos){
    double B = BLOCK_SIZE/(count-1);//B is the block size
    if (pos.getX()<=exit.getX()&&
        pos.getY()>=exit.getY()){
        return Point(x+B*(i),y-B*(j));
    }else if (pos.getX()<=exit.getX()&&
              pos.getY()<=exit.getY()){
        return Point(x+B*(i),y+B*(j));
    }else if (pos.getX()>=exit.getX()&&
              pos.getY()>=exit.getY()){
        return Point(x-B*(i),y-B*(j));
    }else{
        return Point(x-B*(i),y+B*(j));
    }
}

//add the path points to the vector exitP
//start from the right bottom to top left
void findpath(std::vector<Point> &exitP,int* arr,int row, int col,Point exit,Point pos){
    int i=row;
    int j=col-1;
    Point temp;
    exitP.push_back(Point(exit.getX(),exit.getY()));

    while (i > 0 && j > 0){
        if(arr[(i-1)*col+j-1]==1){
            exitP.push_back(temp=setxy(pos.getX(), pos.getY(), i-1,  j-1,exit, pos));
            i--;j--;
        }else if(arr[(i-1)*col+j]==1){
            exitP.push_back(temp=setxy(pos.getX(), pos.getY(), i-1,  j,exit, pos));
            i--;
        }else if(arr[i*col+j-1]==1){
            exitP.push_back(temp=setxy(pos.getX(), pos.getY(), i,  j-1,exit, pos));
            j--;
        }

    }

    return;
}

//fly to exit point
/*void flyToExit(std::vector<Point> &exitP,double z){
    double x,y;

    for(int i=exitP.size()-1;i>0;i--){
        x =  exitP[i].getX();
        y = exitP[i].getY();
        tello.SendCommand("go x y z 10");
    }
}*/


//find the exit path
void gotoExit(Point exit, Point pos, double z){
    std::vector<Point> points;
    getxy(points);

    int *matrix;
    int col, row;
    do {
        delete[] matrix;//free the dynamic memory that was allocated in cutBlocks (to start over)
        matrix = cutBlocks(points, col, row, pos, exit);

        //if the block is empty -> we can go through this block (0)
        //otherwise we can't go through this block (-1)
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i * col + j] != 0)
                    matrix[i * col + j] = -1;
            }

        }
    }while (isPath(matrix, row, col));


    std::vector<Point> exitP;//exitP will hold the path from the current position to the exit point

    findpath(exitP,matrix,row, col,exit,pos); //reverse from exit to start (add points to path vector)


    //&&&&&&&&&&&&&&&&&&&&&&&&
    //          check
    /*std::ofstream myFile("foo.csv");

    for(int i=0;i < exitP.size();i++){
        myFile << exitP[i].getX()<<","<<
               exitP[i].getY()<<"\n";
    }
    myFile.close();*/
    //&&&&&&&&&&&&&&&&&&&&&&&&

    //flyToExit( exitP, z);

}






