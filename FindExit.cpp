#include "FindExit.h"
#define MIN 7
#include <fstream>
#include <algorithm>


Point FindExit(){
    std::vector<Point> points, vertex, outp,suspicious;
    int Size;
    //0     1
    //
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
        std::cout << "points "<<points.size()<<"Size  "<<Size<<std::endl;
    }while (points.size()>150&&Size!=points.size());


    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    std::cout<<vertex[0].getx()<<","<< vertex[0].gety();
    std::cout<< "             " <<vertex[1].getx()<<","<< vertex[1].gety()<<std::endl;
    std::cout<<vertex[3].getx()<<","<< vertex[3].gety();
    std::cout<< "             " <<vertex[2].getx()<<","<< vertex[2].gety()<<std::endl;


    //((((((((((((((((((((((((((()))))))))))))))))))))))))))
    std::vector<Point> ver;
    ver.push_back(Point(1,1));
    ver.push_back(Point(2,1));
    ver.push_back(Point(2,0));
    ver.push_back(Point(1,0));
    Dispoint point(Point(3,0.5));
    point.setdis(ver);
    std::cout<< "point distance  " << point.dis << std::endl;

    //keepsuspicious (outp, suspicious);

/*
	cout <<"CCCCCCCCC"<< endl << endl;
	for (int i=0; i < points.size()-1; i++) {
		cout << points[i].getx() << "   ***   " << points[i].gety() << endl;
	}
*/


    Point exit;
    Exit(points, vertex, exit);
    return exit;
}


void Exit(std::vector<Point> &points, std::vector<Point> &vertex,Point& exit){
    std:: vector<Dispoint> blocks;//we will use the dis to save the number of elements in the block, and point to save one point
    Dispoint temp;
    /*for (int i=0; i<points.size();i++){
        dist.push_back(Dispoint(Point(points[i].getx(),points[i].gety())));
        dist[i].setdis(vertex);
    }*/

    for (int i=0; i<points.size();i++){
        blocks.push_back(Dispoint(Point(points[i].getx(),points[i].gety())));
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

double dis(Point p1, Point p2){
    return sqrt(pow(p1.getx()-p2.getx(), 2) + pow(p1.gety()-p2.gety(), 2));
}

void clearinside (std::vector<Point> &points, std::vector<Point> &outp, std::vector<Point> &vertex){
    for (int i=0; i < points.size(); i++) {
        if (!(points[i].getx()>=vertex[0].getx() && points[i].getx()<=vertex[1].getx()
              && points[i].gety()>=vertex[3].gety() && points[i].gety()<=vertex[0].gety())){
            outp.push_back(Point(points[i].getx(),points[i].gety()));
        }
    }
    return;
}

void findrectangle (std::vector<Point> &points, std::vector<Point> &vertex){// avg points and distances
    int i;
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


    //((((((((((((((((()))))))))))))))))
    std::cout<<vertex[0].getx()<<","<< vertex[0].gety();
    std::cout<< "             " <<vertex[1].getx()<<","<< vertex[1].gety()<<std::endl;
    std:: cout<<vertex[3].getx()<<","<< vertex[3].gety();
    std::cout<< "             " <<vertex[2].getx()<<","<< vertex[2].gety()<<std::endl;

    //cout << x << "   ###   " << y << endl;
    //cout << disx << "   ###   " << disy << endl;


    return;
}

void getxy(std::vector<Point> &xzy) {//from file to vector
    std::ifstream file;
    int i=0;
    file.open("C:\\Users\\saker\\CLionProjects\\untitled2\\pointData1.csv");

    std::string line, num;

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