/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 RaÃºl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/

#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>
#include <unistd.h>	
#include<opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include<System.h>
#include <Converter.h>

#include "ctello.h"
//const char* const TELLO_STREAM_URL{ "udp://0.0.0.0:11111" };//???????????????????????? should sent as an arg to main ?
#define Degree 30

using namespace std;

void LoadImages(const string &strFile, vector<string> &vstrImageFilenames,
                vector<double> &vTimestamps);
                
void saveMap(ORB_SLAM2::System &SLAM);

int main(int argc, char **argv)// TELLO_STREAM_URL =argv[4]
{
    int i;
    ctello::Tello tello;
    if (!tello.Bind())
    {
        return 0;
    }


    if(argc != 5)
    {
        cerr << endl << "Usage: ./mono_tum path_to_vocabulary path_to_settings path_to_sequence" << endl;
        return 1;
    }


    tello.SendCommand("streamon ");//Enable video stream     
    while (!(tello.ReceiveResponse()));

    cv::VideoCapture cap(argv[4]);
    //cv::VideoCapture cap{ argv[4], CAP_FFMPEG };
    //******************* 1  OR 2
    //***********1
    if (!cap.isOpened())
    {
    	cerr << endl  <<"Could not open camera feed."  << endl;
    	return -1;
    }
    /*****************************2

        while (true)
    {
        cv::Mat frame;
        cap >> frame;
        if (!frame.empty())
        {
            imshow("CTello Stream", frame);
        }
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    */

    // Retrieve paths to images
    //???????????????????
    vector<string> vstrImageFilenames;
    vector<double> vTimestamps;
    string strFile = string(argv[3])+"/rgb.txt";
    LoadImages(strFile, vstrImageFilenames, vTimestamps);

    int nImages = vstrImageFilenames.size();

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

    // Vector for tracking time statistics
    vector<float> vTimesTrack;
    vTimesTrack.resize(nImages);

    //start
    tello.SendCommand("takeoff");
    while (!(tello.ReceiveResponse()));// Wait for response

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;
    cout << "Images in the sequence: " << nImages << endl << endl;

    // Main loop
    cv::Mat im;
    for (int ni = 0,i = 0; i < 360; i += Degree,ni++)
    {

        tello.SendCommand("forward 5");
        while (!(tello.ReceiveResponse()));
        tello.SendCommand("back 5");
        while (!(tello.ReceiveResponse()));
        tello.SendCommand("cw Degree");
        while (!(tello.ReceiveResponse()));




        // Read image from file
       
        im = cv::imread(string(argv[3])+"/"+vstrImageFilenames[ni],CV_LOAD_IMAGE_UNCHANGED);
        double tframe = vTimestamps[ni];

        //Create a new Mat
    	cv::Mat frame;

    	//Send the captured frame to the new Mat
    	cap>>im;
        

        //?????????????????????????????????????
        if (im.empty() {//if there is no new points in the map (didn't scan any thing)
            tello.SendCommand("back 10");
            while (!(tello.ReceiveResponse()));
            i -= Degree;
        }
       /* if (im.empty())
        {
            cerr << endl << "Failed to load image at: "
                 << string(argv[3]) << "/" << vstrImageFilenames[ni] << endl;
            return 1;
        }
        */

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
#endif

        // Pass the image to the SLAM system
        SLAM.TrackMonocular(im,tframe);

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t2 = std::chrono::monotonic_clock::now();
#endif

        double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

        vTimesTrack[ni]=ttrack;

        // Wait to load the next frame
        double T=0;
        if(ni<nImages-1)
            T = vTimestamps[ni+1]-tframe;
        else if(ni>0)
            T = tframe-vTimestamps[ni-1];

        if(ttrack<T)
            usleep((T-ttrack)*1e6);
    }

    // Stop all threads
    SLAM.Shutdown();
    saveMap(SLAM);
    /*
    cap.release();

    // Tracking time statistics
    sort(vTimesTrack.begin(),vTimesTrack.end());
    float totaltime = 0;
    for(int ni=0; ni<nImages; ni++)
    {
        totaltime+=vTimesTrack[ni];
    }
    cout << "-------" << endl << endl;
    cout << "median tracking time: " << vTimesTrack[nImages/2] << endl;
    cout << "mean tracking time: " << totaltime/nImages << endl;

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");
    */
    


    //find exit 

   //locate 
    while () {//didn't get to the exit point
        while ()//there is something in front of the drone(according to the map)
        {
            tello.SendCommand("cw Degree");
            while (!(tello.ReceiveResponse()));
        }
        tello.SendCommand("forward 10");
        while (!(tello.ReceiveResponse()));
    }

    //end
    tello.SendCommand("land");
    while (!(tello.ReceiveResponse()));
    tello.SendCommand("streamoff ");//Disable video stream     
    while (!(tello.ReceiveResponse()));

    return 0;
}

void saveMap(ORB_SLAM2::System &SLAM){
    std::vector<ORB_SLAM2::MapPoint*> mapPoints = SLAM.GetMap()->GetAllMapPoints();
    std::ofstream pointData;
    pointData.open("/tmp/pointData.csv");
    for(auto p : mapPoints) {
        if (p != NULL)
        {
            auto point = p->GetWorldPos();
            Eigen::Matrix<double, 3, 1> v = ORB_SLAM2::Converter::toVector3d(point);
            pointData << v.x() << "," << v.y() << "," << v.z()<<  std::endl;
        }
    }
    pointData.close();
}

void LoadImages(const string &strFile, vector<string> &vstrImageFilenames, vector<double> &vTimestamps)
{
    ifstream f;
    f.open(strFile.c_str());

    // skip first three lines
    string s0;
    getline(f,s0);
    getline(f,s0);
    getline(f,s0);

    while(!f.eof())
    {
        string s;
        getline(f,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            double t;
            string sRGB;
            ss >> t;
            vTimestamps.push_back(t);
            ss >> sRGB;
            vstrImageFilenames.push_back(sRGB);
        }
    }
}


