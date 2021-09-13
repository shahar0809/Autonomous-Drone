#include<iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <Converter.h>
#include <System.h>
#include <mutex>
#include <queue>
#include "ctello.h"
#include <atomic>
#include "detect_exit.hpp"
#include "navigation.hpp"

void saveMap(ORB_SLAM2::System &SLAM);
void video_stream();
void handle_drone(ctello::Tello& tello);
void get_position(cv::Mat tcw);

std::mutex queueMutex;
std::queue<cv::Mat> frames;

std::atomic<bool> isInit = { false };
std::atomic<bool> isDone = { false };
std::atomic<bool> saveM = { false };

Navigator navigator;

const int TURN_DEGREE = 25;
const int FULL_TURN = 360;
float MIN_ANGLE = 30;

cv::Mat tcw1, tcw2;

// Constants
const std::string TELLO_STREAM = "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000";
const std::string VOC_PATH = "/home/magshimim/Documents/exit-scan/ORB_SLAM2/Vocabulary/ORBvoc.txt";
const std::string CONFIG_PATH = "/home/magshimim/Documents/exit-scan/ORB_SLAM2/tello.yaml";

void handle_drone(ctello::Tello& tello)
{
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

    // Telling Tello to hover in the air
    tello.SendCommand("speed 10");
    //Wait until tello sends response
    while (!(tello.ReceiveResponse()));


    /* While ORB-SLAM isn't initialized, move up and down */
    while (!isInit)
    {
        tello.SendCommand("up 2");
        //Wait until tello sends response
        while (!(tello.ReceiveResponse()));

        tello.SendCommand("down 2");
        //Wait until tello sends response
        while (!(tello.ReceiveResponse()));

        // Telling Tello to hover in the air
        tello.SendCommand("stop");
        //Wait until tello sends response
        while (!(tello.ReceiveResponse()));
    }

    for (int deg = 0; deg <= FULL_TURN; deg += TURN_DEGREE)
    {
        tello.SendCommand("cw " + std::to_string(TURN_DEGREE));
        while (!(tello.ReceiveResponse()));

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        tello.SendCommand("forward 30");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        tello.SendCommand("backward 30");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        tello.SendCommand("stop");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    saveM = true;
    navigator.set_exit_point(FindExit());

    float angle = navigator.calc_rotation_angle();

    if (angle <= MIN_ANGLE)
    {
        if (navigator.m_clockwise)
        {
            tello.SendCommand("cw " + std::to_string(angle));
            //Wait until tello sends response
            while (!(tello.ReceiveResponse()));
        }
        else
        {
            tello.SendCommand("ccw " + std::to_string(angle));
            //Wait until tello sends response
            while (!(tello.ReceiveResponse()));
        }
    }
    else
    {
        int amountOfTurns = angle / MIN_ANGLE;

        for(int i = 0; i < amountOfTurns; i++)
        {
            if (navigator.m_clockwise)
            {
                tello.SendCommand("cw " + std::to_string(MIN_ANGLE));
                //Wait until tello sends response
                while (!(tello.ReceiveResponse()));
            }
            else
            {
                tello.SendCommand("ccw " + std::to_string(MIN_ANGLE));
                //Wait until tello sends response
                while (!(tello.ReceiveResponse()));
            }
        }

        if (navigator.m_clockwise)
        {
            tello.SendCommand("cw " + std::to_string(int(fmod(angle, MIN_ANGLE))));
            //Wait until tello sends response
            while (!(tello.ReceiveResponse()));
        }
        else
        {
            tello.SendCommand("ccw " + std::to_string(int(fmod(angle, MIN_ANGLE))));
            //Wait until tello sends response
            while (!(tello.ReceiveResponse()));
        }

    }

    tello.SendCommand("cw " + std::to_string(angle));
    while (!(tello.ReceiveResponse()));

    tello.SendCommand("forward 200");
    while (!(tello.ReceiveResponse()));

    isDone = true;
    //this_thread::sleep_for(3000);
}

void video_stream()
{
    cv::VideoCapture capture{TELLO_STREAM, cv::CAP_FFMPEG};
    cv::Mat frame;

    /* If ORB-SLAM is not initialized, move up and down */
    while(!isDone)
    {
        capture >> frame;

        if (!frame.empty())
        {
            // Push frame into queue
            queueMutex.lock();
            frames.push(frame);
            queueMutex.unlock();
        }
    }
}

int main()
{
    ctello::Tello tello;
    std::thread manage_drone(handle_drone, std::ref(tello));
    std::thread drone_video(video_stream);

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(VOC_PATH,CONFIG_PATH,ORB_SLAM2::System::MONOCULAR,true);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;

    auto finish = std::chrono::system_clock::now() + 2min;
    cv::Mat currFrame, tcw;

    while (!isDone)
    {
        isInit = SLAM.GetTrackingState() == ORB_SLAM2::Tracking::OK;

        queueMutex.lock();
        if (!frames.empty())
        {
            currFrame = frames.back();
            frames = std::queue<cv::Mat>();
            queueMutex.unlock();

            if (currFrame.empty())
            {
                cerr << endl << "Failed to load image." << endl;
                return 1;
            }

            // Pass the image to the SLAM system
            tcw1 = SLAM.TrackMonocular(currFrame, 0.2);
        }
        queueMutex.unlock();

        if (isInit && saveM)
        {
            saveMap(SLAM);
            saveM = false;
        }
    }

    std::cout << "trying to join" << std::endl;
    drone_video.join();
    manage_drone.join();
    std::cout << "trying to save" << std::endl;
    std::cout << "SAVED MAP" << std::endl;
    SLAM.Shutdown();

    return 0;
}

void saveMap(ORB_SLAM2::System &SLAM)
{
    std::vector<ORB_SLAM2::MapPoint*> mapPoints = SLAM.GetMap()->GetAllMapPoints();
    std::ofstream pointData;
    pointData.open("/Map/pointData.csv");

    for(auto p : mapPoints)
    {
        if (p != nullptr)
        {
            auto point = p->GetWorldPos();
            Eigen::Matrix<double, 3, 1> v = ORB_SLAM2::Converter::toVector3d(point);
            pointData << v.x() << "," << v.y() << "," << v.z()<<  std::endl;
        }
    }
    pointData.close();
}

void get_position(cv::Mat tcw)
{
    cv::Mat rotation = tcw(cv::Range::all(), cv::Range(3, 4)).clone();
    cv::Mat translation = -rotation * tcw.rowRange(0, 3).col(3);

    std::vector<float> quatVec = ORB_SLAM2::Converter::toQuaternion(rotation);

    cv::Mat twc( { translation.at<float>(0), translation.at<float>(1),
            translation.at<float>(2), quatVec[0], quatVec[1], quatVec[2], quatVec[3] });

    navigator.lastLocations.push(twc);
}