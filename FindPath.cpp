#define MIN 7

#include "FindPath.h"


//divide the rectangle (the way between the position of the drone and the exit point)
//into blocks and find the number of points in the block
int* cutBlocks  (std::vector<Point> &points,int& col,int& row,Point pos, Point exit){
    int i,j;
    double x,y;
    x = abs(pos.getx()-exit.getx());
    y = abs(pos.gety()-exit.gety());
    x = x/(BLOCK_SIZE/count);
    y = y/(BLOCK_SIZE/count);
    row= (int) y;
    col= (int) x;
    std::cout << "1";
    int* blocks= new int [row*col];
    std::cout << "2";
    for( i=0;i < row;i++){
        for( j=0;j < col;j++){
            blocks[i*col+j]=0;
        }
    }
    std::cout << "3";

    for (int k=0; k<points.size(); k++){
        i=abs((points[k].getx()-pos.getx())/(BLOCK_SIZE/count));
        j=abs((points[k].gety()-pos.gety())/(BLOCK_SIZE/count));
        if(i < col &&j < row)//if the point is in the rectangle
            blocks[i*col+j]++;
    }
    //the next time we enter this function we should divide into smaller blocks
    //since the next time we enter this function it will be the situation that we couldn't find exit path
    count++;
    std::cout << "4";

    //if the block is empty -> we can go through this block (0)
    //otherwise we can't go through this block (-1)
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (blocks[i * col + j] > MIN)
                blocks[i * col + j] = -1;
        }

    }
    std::cout << "5";
    if(isPath(blocks, row, col))
    {
        std::cout << "**";
        delete [] blocks;
        std::cout << "**";
        return cutBlocks(points, col, row, pos, exit);
    }else{
        std::cout << "??\n";
        return blocks;
    }
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
                arr[i*col+j] = std::max(arr[i*col+j-1], arr[(i-1)*col+j]);


    if (arr[row*col-1] == 1){
        return 0;
    }else{
        return 1;//there is no path
    }
}

//find the point x',y' that the block i,j represent - according to the positions of the drone and the exit.
Point setxy(double x, double y, int j, int i,Point exit, Point pos){
    double B = BLOCK_SIZE/(count-1);//B is the block size
    if (pos.getx()<=exit.getx()&&
        pos.gety()>=exit.gety()){
        return Point(x+B*(i),y-B*(j));
    }else if (pos.getx()<=exit.getx()&&
              pos.gety()<=exit.gety()){
        return Point(x+B*(i),y+B*(j));
    }else if (pos.getx()>=exit.getx()&&
              pos.gety()>=exit.gety()){
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
    exitP.push_back(Point(exit.getx(),exit.gety()));

    while (i > 0 && j > 0){
        if(arr[(i-1)*col+j-1]==1){
            exitP.push_back(temp=setxy(pos.getx(), pos.gety(), i-1,  j-1,exit, pos));
            i--;j--;
        }else if(arr[(i-1)*col+j]==1){
            exitP.push_back(temp=setxy(pos.getx(), pos.gety(), i-1,  j,exit, pos));
            i--;
        }else if(arr[i*col+j-1]==1){
            exitP.push_back(temp=setxy(pos.getx(), pos.gety(), i,  j-1,exit, pos));
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

    matrix = cutBlocks(points, col, row, pos, exit);//cut into good blocks (Good blocks ~ until we get a path)

    std::vector<Point> exitP;//exitP will hold the path from the current position to the exit point

    findpath(exitP,matrix,row, col,exit,pos); //reverse from exit to start (add points to path vector)


    //&&&&&&&&&&&&&&&&&&&&&&&&
    //          check
   /* std::cout <<"*****";
    std::ofstream myFile("out.csv");

    for(int i=0;i < exitP.size();i++){
        myFile << exitP[i].getX()<<","<<
               exitP[i].getY()<<"\n";
    }
    myFile.close();*/
    //&&&&&&&&&&&&&&&&&&&&&&&&
    for(int i=0;i < exitP.size();i++){
        std::cout << exitP[i].getx()<<","<<
               exitP[i].gety()<<"\n";
    }
    //flyToExit( exitP, z);


}






