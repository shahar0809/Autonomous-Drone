#include "detect_exit.hpp"
#define MIN 7
#include <fstream>
#include <algorithm>

Point FindExit()
{
    std::vector<Point> points, vertex, outp,suspicious;
    int Size;
    //0     1
    //
    //3     2
    for (int i=0; i<4; i++)
    {
        vertex.push_back(Point());
    }

    getXy(points);

    do{
        outp.clear();
        findrectangle(points, vertex);
        Size=points.size();
        clearinside(points, outp, vertex);
        points.clear();

        for (int i=0; i<outp.size(); i++){
            points.push_back(Point(outp[i].getX(),outp[i].getY()));
        }
        std::cout << "points "<<points.size()<<"Size  "<<Size<<std::endl;
    }while (points.size()>150&&Size!=points.size());


    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    std::cout<<vertex[0].getX()<<","<< vertex[0].getY();
    std::cout<< "             " <<vertex[1].getX()<<","<< vertex[1].getY()<<std::endl;
    std::cout<<vertex[3].getX()<<","<< vertex[3].getY();
    std::cout<< "             " <<vertex[2].getX()<<","<< vertex[2].getY()<<std::endl;


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
		cout << points[i].getX() << "   ***   " << points[i].getY() << endl;
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
        dist.push_back(Dispoint(Point(points[i].getX(),points[i].getY())));
        dist[i].setdis(vertex);
    }*/

    for (int i=0; i<points.size();i++){
        blocks.push_back(Dispoint(Point(points[i].getX(),points[i].getY())));
        blocks[i].add();
        for (int j=i; j<points.size(); j++){

            if(dis(points[i],points[j])<0.03){
                (temp.point).setX(points[j].getX());
                (temp.point).setY(points[j].getY());
                temp.setdis(vertex);
                if(blocks[i].dis<temp.dis){//representative is the one with max distance
                    (blocks[i].point).setX(points[j].getX());
                    (blocks[i].point).setY(points[j].getY());
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
    exit.setX((temp.point).getX());
    exit.setY((temp.point).getY());
    return;
}

double dis(Point p1, Point p2){
    return sqrt(pow(p1.getX()-p2.getX(), 2) + pow(p1.getY()-p2.getY(), 2));
}

void clearinside (std::vector<Point> &points, std::vector<Point> &outp, std::vector<Point> &vertex){
    for (int i=0; i < points.size(); i++) {
        if (!(points[i].getX()>=vertex[0].getX() && points[i].getX()<=vertex[1].getX()
              && points[i].getY()>=vertex[3].getY() && points[i].getY()<=vertex[0].getY())){
            outp.push_back(Point(points[i].getX(),points[i].getY()));
        }
    }
    return;
}

void findrectangle (std::vector<Point> &points, std::vector<Point> &vertex){// avg points and distances
    int i;
    double x=0,y=0,disx=0,disy=0;
    for (int i=0; i < points.size(); i++) {
        y += (points[i].getY()/(points.size()));
        x += (points[i].getX()/(points.size()));
    }

    //avg distance
    for (int i=0; i < points.size(); i++) {
        disy += (abs (points[i].getY()-y)/(points.size()));
        disx += (abs (points[i].getX()-x)/(points.size()));
    }


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


    //((((((((((((((((()))))))))))))))))
    std::cout<<vertex[0].getX()<<","<< vertex[0].getY();
    std::cout<< "             " <<vertex[1].getX()<<","<< vertex[1].getY()<<std::endl;
    std:: cout<<vertex[3].getX()<<","<< vertex[3].getY();
    std::cout<< "             " <<vertex[2].getX()<<","<< vertex[2].getY()<<std::endl;

    //cout << x << "   ###   " << y << endl;
    //cout << disx << "   ###   " << disy << endl;


    return;
}

void getXy(std::vector<Point> &xzy) {//from file to vector
    std::ifstream file;
    int i=0;
    file.open(SCAN_PATH);

    std::string line, num;

    while(file.good()){
        getline(file, num, ',');
        if (num == "\0"){
            break;
        }
        xzy.push_back(Point());
        xzy[i].setX(num);
        getline(file, num, ',');
        getline(file, num, '\n');
        xzy[i].setY(num);
        i++;
    }
    file.close();
}