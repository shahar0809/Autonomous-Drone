/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
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
#include <fstream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <Converter.h>
#include <System.h>
#include <mutex>
#include <queue>
#include "ctello.h"
#include <atomic>

using namespace std;

void saveMap(ORB_SLAM2::System &SLAM);
void video_stream();

std::mutex queueMutex;
std::queue<cv::Mat>* frames = new std::queue<cv::Mat>();

std::atomic<bool> isInit = { false };
std::atomic<bool> isDone = { false };

// Constants
const std::string TELLO_STREAM = "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000";
const std::string VOC_PATH = "/home/magshimim/Documents/exit-scan/ORB_SLAM2/ORBvoc.txt";
const std::string CONFIG_PATH = "/home/magshimim/Documents/exit-scan/ORB_SLAM2/tello.yaml";

void video_stream()
{
    ctello::Tello tello;

    if (!tello.Bind())
    {
        std::cerr << "Couldn't bind to Tello!" << std::endl;
    }

    // Starting video stream from Tello
    tello.SendCommand("streamon");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Telling Tello to takeoff
    tello.SendCommand("takeoff");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Telling Tello to hover in the air
    tello.SendCommand("stop");
    //Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    cv::VideoCapture capture{TELLO_STREAM, cv::CAP_FFMPEG};
    cv::Mat frame;

    int counter = 0;

    while (capture.isOpened() && !isDone)
    {
        counter++;
        if (isInit && counter % 100 == 0)
        {
            tello.SendCommand("cw 30");
            //Wait until tello sends response
            while (!(tello.ReceiveResponse()));
        }
        else
        {
            tello.SendCommand("down 10");
            //Wait until tello sends response
            while (!(tello.ReceiveResponse()));
        }

        capture >> frame;
        queueMutex.lock();
        frames->push(frame);
        queueMutex.unlock();

        if (!isInit)
        {
            tello.SendCommand("up 10");
            //Wait until tello sends response
            while (!(tello.ReceiveResponse()));
        }
    }
    std::cout << "thread done" << std::endl;
}


int main(int argc, char **argv)
{
    std::thread drone_video(video_stream);

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(VOC_PATH,CONFIG_PATH,ORB_SLAM2::System::MONOCULAR,true);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;

    auto finish = std::chrono::system_clock::now() + 1min;
    cv::Mat currFrame;

    do
    {
        isInit = SLAM.GetTrackingState() == ORB_SLAM2::Tracking::OK;

        queueMutex.lock();
        if (!frames->empty())
        {
            currFrame = frames->front();
            frames->pop();
            queueMutex.unlock();

            if (currFrame.empty())
            {
                cerr << endl << "Failed to load image." << endl;
                return 1;
            }

            // Pass the image to the SLAM system
            SLAM.TrackMonocular(currFrame, 0.2);
        }
        queueMutex.unlock();

    } while(std::chrono::system_clock::now() < finish);

    isDone = true;
    std::cout << "DONE" << std::endl;
    drone_video.join();
    SLAM.saveMap(SLAM);

    // Stop all threads
    SLAM.Shutdown();
    delete frames;

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    return 0;
}