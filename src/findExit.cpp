#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "DistPoint.h"
#include "findExit.h"

 bool operator<(const DistPoint& l, const DistPoint& r)
 {
    return l.dis<r.dis;
 }


void get_xy(vector<Point> &xzy);
void findRectangle (vector<Point> &points, vector<Point> &vertex);
void clearInside (vector<Point> &points, vector<Point> &outp, vector<Point> &vertex);


void exit(vector<Point> &points, vector<Point> &vertex, Point& exit);
double distance(Point p1, Point p2);
const Point findExit();
const Point getPosition ();
void cutBlocks (int* blocks, vector<Point> &points, int col,Point pos, Point exit);
int isPath(int* arr,int row, int col);
void findPath(vector<Point> &exitP, int* arr, int row, int col, Point exit, Point pos);

int detect_and_nav()
{
    Point exit,pos;

    //get pos
    /*
    cv::mat Tcw = SLAM.TrackMonocular(frame, 0.2);
    cv::Mat Rwc = Tcw.rowRange(0,3).colRange(0,3).t(); // Rotation information
    cv::Mat twc = -Rwc*Tcw.rowRange(0,3).col(3); // translation information
    pos = Point(twc.at(0,0),twc.at(2,0));
    double z=twc.at(1,0)*/

    exit = findExit();
    cout <<"exit =   " << exit.getx() << " , " << exit.gety();

    vector<Point> points;
    pos = getPosition();
    get_xy(points);

    double x, y;
    int row, col;

    x = abs(pos.getx() - exit.getx());
    y = abs(pos.gety() - exit.gety());
    x = x / B;
    y = y / B;
    row = (int) y;
    col = (int) x;

    int* matrix = new int [row * col];

    for(int i=0;i < row;i++)
    {
        for(int j = 0; j < col; j++)
        {
             matrix[i * col + j]=0;
        }
    }

    cutBlocks(matrix ,points ,col, pos, exit);

    for(int i=0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(matrix[i * col + j]!=0)
                matrix[i * col + j]=-1;
        }
    }

    if(isPath(matrix, row, col))
    {
        throw std::exception();
	}

	vector<Point> exitP;
    findpath(exitP,matrix,row, col,exit,pos); //reverse from exit to start (add points to path vector)


    //&&&&&&&&&&&&&&&&&&&&&&&&
    std::ofstream myFile("foo.csv");

    // Send data to the stream
    for(int i=0;i < exitP.size();i++){
            myFile << exitP[i].getx()<<","<<
            exitP[i].gety()<<"\n";
        }

    // Close the file
    myFile.close();
    //&&&&&&&&&&&&&&&&&&&&&&&&


    gotoExit(exitP,z);


    return 0;
}

void gotoExit(vector<Point> &exitP,double z){
    double x,y,z;
    z=
    for(int i=exitP.size()-1;i>0;i--){
        x =  exitP[i].getx();
        y = exitP[i].gety();
        tello.SendCommand("go x y z 10");
    }
}

Point setxy(double x, double y, int j, int i,Point exit, Point pos){
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

void findPath(vector<Point> &exitP, int* arr, int row, int col, Point exit, Point pos){//reverse from exit to start (add points to path vector)
    int i=row;
    int j=col-1;
Point temp;
    exitP.push_back(Point(exit.getx(),exit.gety()));

    while (i >0&&j >0){
        if(arr[(i-1)*col+j-1]==1){
            exitP.push_back(temp=setxy(pos.getx(), pos.gety(), i-1,  j-1,exit, pos));
            //cout<< i<<","<<j<<"  "<< temp.getx()<<","<<temp.gety()<<endl;
            i--;j--;
            //cout <<"***"<<endl;
        }else if(arr[(i-1)*col+j]==1){
            exitP.push_back(temp=setxy(pos.getx(), pos.gety(), i-1,  j,exit, pos));
            //cout<< i<<","<<j<<"  "<< temp.getx()<<","<<temp.gety()<<endl;
            i--;
            //cout <<"*"<<endl;
        }else if(arr[i*col+j-1]==1){
            exitP.push_back(temp=setxy(pos.getx(), pos.gety(), i,  j-1,exit, pos));
            //cout<< i<<","<<j<<"  "<< temp.getx()<<","<<temp.gety()<<endl;
            j--;
            //cout <<"**"<<endl;
        }else{
            //cout<<i<<" , "<<j;
            cout<<"Error!"<<endl;
            return;
        }

    }

    return;
}


// to find the path from
// top left to bottom right
int isPath(int* arr,int row, int col){//-1 - can�t go through this cell

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
              arr[i*col+j] = max(arr[i*col+j-1], arr[(i-1)*col+j]);


    if (arr[row*col-1] == 1){
        return 0;
    }else{
        return 1;//there is no path
    }
}

void cutBlocks  (int* blocks, vector<Point> &points,int col,Point pos, Point exit){//blocks 0.01 X 0.01
    int i,j;

    for (int k=0; k<points.size(); k++){
        i=abs((points[k].getx()-pos.getx())/B);
        j=abs((points[k].gety()-pos.gety())/B);
        blocks[i*col+j]++;
    }

}


Point findExit(){
    vector<Point> points, vertex, outp;
	int Size;
    //0     1
	//3     2
	 for (int i=0; i<4; i++){
        vertex.push_back(Point());
    }


	getxy(points);

	do{
	    outp.clear();
        findrectangle(points, vertex);
        Size=points.size();
        clearinside(points, outp, vertex);
        points.clear();

        for (int i=0; i<outp.size(); i++){
            points.push_back(Point(outp[i].getx(),outp[i].gety()));
        }
	}while (points.size()>150&&Size!=points.size());



    Point exit;
    Exit(points, vertex, exit);
    return exit;
}

void exit(vector<Point> &points, vector<Point> &vertex, Point& exit){
    vector<Dispoint> blocks;//we will use the dis to save the number of elements in the block, and point to save one point
    Dispoint temp;

    for (int i=0; i<points.size();i++){
        blocks.push_back(DistPoint(Point(points[i].getx(),points[i].gety())));
        blocks[i].add();
        for (int j=i; j<points.size(); j++){

            if(dis(points[i],points[j])<0.03){
                (temp.point).setx(points[j].getx());
                (temp.point).sety(points[j].gety());
                temp.setdis(vertex);
                if(blocks[i].dis<temp.dis){//representative is the one with max distance
                   (blocks[i].point).setx(points[j].getx());
                   (blocks[i].point).sety(points[j].gety());
                   blocks[i].setdis(vertex);
                }
                points.erase(points.begin()+i);
                blocks[i].add();
            }

        }
    }
    for(int i=0;i<blocks.size();i++){
            if (blocks[i].num<MIN){
                blocks.erase(blocks.begin()+i);
                i--;
            }
    }


    std::sort(blocks.begin(), blocks.end());//sort by distance

    temp=blocks[blocks.size()-1];
    exit.setx((temp.point).getx());
    exit.sety((temp.point).gety());
    return;
}

double distance(Point p1, Point p2){
    return sqrt(pow(p1.getx()-p2.getx(), 2) + pow(p1.gety()-p2.gety(), 2));
}

void clearInside (vector<Point> &points, vector<Point> &outp, vector<Point> &vertex){
    for (int i=0; i < points.size(); i++) {
            if (!(points[i].getx()>=vertex[0].getx() && points[i].getx()<=vertex[1].getx()
                && points[i].gety()>=vertex[3].gety() && points[i].gety()<=vertex[0].gety())){
                      outp.push_back(Point(points[i].getx(),points[i].gety()));
                }
	}
    return;
}

void findRectangle (vector<Point> &points, vector<Point> &vertex){// avg points and distances
    double x=0,y=0,disx=0,disy=0;
    for (int i=0; i < points.size(); i++) {
            y += (points[i].gety()/(points.size()));
            x += (points[i].getx()/(points.size()));
	}

	//avg distance
	for (int i=0; i < points.size(); i++) {
            disy += (abs (points[i].gety()-y)/(points.size()));
            disx += (abs (points[i].getx()-x)/(points.size()));
	}


	//0     1
	//
	//3     2



	vertex[0].setx(x-disx);
	vertex[0].sety(y+disy);

	vertex[1].setx(x+disx);
	vertex[1].sety(y+disy);

	vertex[2].setx(x+disx);
	vertex[2].sety(y-disy);

	vertex[3].setx(x-disx);
	vertex[3].sety(y-disy);


    return;
}

void get_xy(vector<Point> &xzy) {//from file to vector
	ifstream file;
	int i=0;
	file.open("pointData.csv");

	string line, num;

        while(file.good()){
           getline(file, num, ',');
           if (num == "\0"){
            break;
           }
           xzy.push_back(Point());
           xzy[i].setx(num);
           getline(file, num, ',');
           getline(file, num, '\n');
           xzy[i].sety(num);
           i++;
        }
	file.close();
}
