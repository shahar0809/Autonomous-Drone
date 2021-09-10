#include <iostream>
#include "FindExit.h"
#include "FindPath.h"

int main() {

    //get position
    /*
    cv::Mat Tcw = SLAM.TrackMonocular(frame, 0.2);
    cv::Mat Rwc = Tcw.rowRange(0,3).colRange(0,3).t(); // Rotation information
    cv::Mat twc = -Rwc*Tcw.rowRange(0,3).col(3); // translation information
    pos = Point(twc.at(0,0),twc.at(2,0));
    double z=twc.at(1,0)
     */

    Point exit;
    exit = FindExit();
    std::cout << "The Exit point is: " << exit.getX() <<","<< exit.getY() <<std::endl;
    //gotoExit(exit, pos, z);


    return 0;
}
