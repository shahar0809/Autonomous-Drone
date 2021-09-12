//
// Created by saker on 9/12/2021.
//

#include "Detector.h"
#include <fstream>
#include <algorithm>
#define SAME_BLOCK 0.03
#define MIN 7


void Detector::getxy() {//from file to vector
    std::ifstream file;
    int i=0;
    file.open("pointData.csv");

    std::string line, num;

    while(file.good()){
        getline(file, num, ','); // get first number (x)
        if (num == "\0"){
            break;
        }
        points.push_back(Point(0,0));
        points[i].setX(num);
        getline(file, num, ',');// get second number (z)
        getline(file, num, '\n');// get third number (y)
        points[i].setY(num);
        i++;
    }
    file.close();
}

void Detector::findrectangle (){// avg points and distances
    double x=0,y=0,disx=0,disy=0;

    //calculate average according to x, and average according to y.
    for (int i=0; i < points.size(); i++) {
        y += (points[i].getY()/(points.size()));
        x += (points[i].getX()/(points.size()));
    }

    //find the average distance according to x and y from the average points x,y.
    for (int i=0; i < points.size(); i++) {
        disy += (abs (points[i].getY()-y)/(points.size()));
        disx += (abs (points[i].getX()-x)/(points.size()));
    }

    //build the rectangle
    //0     1
    //
    //3     2

    vertex[0].setX(x-disx);
    vertex[0].setY(y+disy);

    vertex[1].setX(x+disx);
    vertex[1].setY(y+disy);

    vertex[2].setX(x+disx);
    vertex[2].setY(y-disy);

    vertex[3].setX(x-disx);
    vertex[3].setY(y-disy);


    return;
}

void Detector::clearinside (){
    for (int i=0; i < points.size(); i++) {
        if (!(points[i].getX()>=vertex[0].getX() && points[i].getX()<=vertex[1].getX()
              && points[i].getY()>=vertex[3].getY() && points[i].getY()<=vertex[0].getY())){
            outp.push_back(Point(points[i].getX(),points[i].getY()));
        }
    }
    return;
}

double dis(Point p1, Point p2){
    return sqrt(pow(p1.getX()-p2.getX(), 2) + pow(p1.getY()-p2.getY(), 2));
}

void Detector::getExit(){
    //we will use the dis to save the number of elements in the block, and point to save one point.
    std::vector<Dispoint> blocks;
    Dispoint temp;

    //divide points into blocks by distances
    for (int i=0; i<points.size();i++){
        blocks.push_back(Dispoint(Point(points[i].getX(),points[i].getY())));//Representative
        blocks[i].add();
        for (int j=i; j<points.size(); j++){

            if(dis(points[i],points[j])<SAME_BLOCK){
                temp.setPoint(Point(points[j].getX(),points[j].getY()));
                temp.setDis(vertex);
                //representative is the one with max distance
                if(blocks[i].GetDistance() < temp.GetDistance()){
                    blocks[i].setPoint(temp.GetRepresentative());
                    blocks[i].setDis(vertex);
                }
                //delete each point that belongs to a block
                points.erase(points.begin()+i);
                blocks[i].add();
            }

        }
    }

    //delete blocks with few points
    for(int i=0;i<blocks.size();i++){
        if (blocks[i].GetNymberP() < MIN){
            blocks.erase(blocks.begin()+i);
            i--;
        }
    }


    std::sort(blocks.begin(), blocks.end());//sort by distance

    //the exit point is the representative point of the block with maximum distance
    temp=blocks[blocks.size()-1];
    exit.setX((temp.GetRepresentative()).getX());
    exit.setY((temp.GetRepresentative()).getY());
    return;
}

Point Detector::FindExit(){

    int Size;
    for (int i=0; i<4; i++){
        vertex.push_back(Point(0,0));
    }

    //....(1)......get data
    getxy();

    //....(2)......find rectangle & clear inside -- the maximum rectangle
    do{
        outp.clear();
        findrectangle();
        Size=points.size();
        clearinside();
        points.clear();

        for (int i=0; i<outp.size(); i++){
            points.push_back(Point(outp[i].getX(),outp[i].getY()));
        }
    }while (points.size()>150 && Size!=points.size());


    Point exit(0,0);

    //....(3)...... get exit
    getExit();
    return exit;
}