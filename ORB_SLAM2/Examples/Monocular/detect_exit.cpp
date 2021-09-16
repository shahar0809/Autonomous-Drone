#include "detect_exit.hpp"

/*
*
*/
Point FindExit()
{
    std::vector<Point> points, vertex, outp,suspicious;
    int Size;

    /* 0     1
    *
    *  3     2
    */

    for (int i=0; i<4; i++)
    {
        vertex.push_back(Point());
    }

    get_xy(points);

    do
    {
        outp.clear();
        findRectangle(points, vertex);
        Size=points.size();
        clearPoints(points, outp, vertex);
        points.clear();

        for (int i=0; i<outp.size(); i++)
        {
            points.push_back(Point(outp[i].get_x(),outp[i].get_y()));
        }

        std::cout << "points "<<points.size()<<"Size  "<<Size<<std::endl;

    } while (points.size()>150 && Size!=points.size());

    Point exit;
    Exit(points, vertex, exit);
    return exit;
}

/*
*
*/
void Exit(std::vector<Point> &points, std::vector<Point> &vertex,Point& exit)
{
    /*
    wWe will use the dis to save the number of elements in the block, 
    and point to save one point.
    */
    std:: vector<Dispoint> blocks;
    Dispoint temp;

    for (int i=0; i<points.size();i++)
    {
        blocks.push_back(Dispoint(Point(points[i].get_x(),points[i].get_y())));
        blocks[i].add();

        for (int j=i; j<points.size(); j++)
        {
            if(dis(points[i], points[j]) < 0.03)
            {
                (temp.point).set_x(points[j].get_x());
                (temp.point).set_y(points[j].get_y());
                temp.set_dist(vertex);

                // Representative is the one with max distance
                if(blocks[i].dis<temp.dis)
                {
                    (blocks[i].point).set_x(points[j].get_x());
                    (blocks[i].point).set_y(points[j].get_y());
                    blocks[i].set_dist(vertex);
                }
                points.erase(points.begin()+i);
                blocks[i].add();
            }
        }
    }

    for(int i=0; i < blocks.size(); i++)
    {
        if (blocks[i].num < MIN)
        {
            blocks.erase(blocks.begin()+i);
            i--;
        }
    }


    std::sort(blocks.begin(), blocks.end());//sort by distance

    temp=blocks[blocks.size()-1];
    exit.set_x((temp.point).get_x());
    exit.set_y((temp.point).get_y());
    return;
}

/*
*
*/
double dis(Point p1, Point p2)
{
    return sqrt(pow(p1.get_x() - p2.get_x(), 2) + pow(p1.get_y()-p2.get_y(), 2));
}

void clearPoints (std::vector<Point> &points, std::vector<Point> &outp, std::vector<Point> &vertex)
{
    for (int i=0; i < points.size(); i++) 
    {
        if (!(points[i].get_x() >= vertex[0].get_x() && 
        points[i].get_x() <= vertex[1].get_x() && 
        points[i].get_y() >= vertex[3].get_y() && 
        points[i].get_y() <= vertex[0].get_y()))
        {
            outp.push_back(Point(points[i].get_x(),points[i].get_y()));
        }
    }
}

// avg points and distances
void findRectangle (std::vector<Point> &points, std::vector<Point> &vertex)
{
    int i;
    double x=0, y=0, disx=0, disy=0;
    for (int i=0; i < points.size(); i++) 
    {
        y += (points[i].get_y()/(points.size()));
        x += (points[i].get_x()/(points.size()));
    }

    // avg distance
    for (int i=0; i < points.size(); i++) 
    {
        disy += (abs (points[i].get_y()-y)/(points.size()));
        disx += (abs (points[i].get_x()-x)/(points.size()));
    }

    //0     1
    //
    //3     2

    vertex[0].set_x(x-disx);
    vertex[0].set_y(y+disy);

    vertex[1].set_x(x+disx);
    vertex[1].set_y(y+disy);

    vertex[2].set_x(x+disx);
    vertex[2].set_y(y-disy);

    vertex[3].set_x(x-disx);
    vertex[3].set_y(y-disy);
}

// from file to vector
void get_xy(std::vector<Point> &xzy) 
{
    std::ifstream file;
    int i=0;
    file.open("C:\\Users\\saker\\CLionProjects\\untitled9\\pointData3.csv");

    std::string line, num;

    while(file.good())
    {
        getline(file, num, ',');
        if (num == "\0")
        {
            break;
        }

        xzy.push_back(Point());
        xzy[i].set_x(num);
        getline(file, num, ',');
        getline(file, num, '\n');
        xzy[i].set_y(num);
        i++;
    }
    file.close();
}
