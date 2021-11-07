#include <iostream>
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

/* FUNCTIONS */
void saveMap(ORB_SLAM2::System &SLAM);
void video_stream();
void handle_drone(ctello::Tello& tello, ORB_SLAM2::System& SLAM);
cv::Mat get_position();

std::mutex queueMutex;
std::queue<cv::Mat> frames;

/* ATOMIC VARIABLES */
std::atomic<bool> isInit = { false };
std::atomic<bool> isDone = { false };

Navigator navigator;
cv::Mat tcw;

/* CONSTANTS */
const int TURN_DEGREE = 20;
const int FULL_TURN = 360;
float MIN_ANGLE = 30;

/* PATHS TO NECESSARY FILES */
const std::string TELLO_STREAM = "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000";
const std::string VOC_PATH = "/home/magshimim/Documents/exit-scan/ORB_SLAM2/Vocabulary/ORBvoc.txt";
const std::string CONFIG_PATH = "/home/magshimim/Documents/exit-scan/ORB_SLAM2/tello.yaml";

void handle_drone(ctello::Tello& tello, ORB_SLAM2::System& SLAM)
{
    std::cout << "drone" << std::endl;

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

    // Making a full turn with the drone
    for (int deg = 0; deg <= FULL_TURN;)
    {
        // Turn a bit
        tello.SendCommand("cw " + std::to_string(TURN_DEGREE));
        while (!(tello.ReceiveResponse()));
        deg += TURN_DEGREE;

        // Wait a bit for ORB-SLAM2 to detect point
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        /* Up and down */
        tello.SendCommand("up 20");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        tello.SendCommand("down 20");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        tello.SendCommand("stop");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        // Check if points were detected, if no new points, then turn back
        if(tcw.empty())
        {
            std::cout << "NOT CHANGED" << std::endl;
            tello.SendCommand("ccw " + std::to_string(TURN_DEGREE));
            while (!(tello.ReceiveResponse()));
            deg -= TURN_DEGREE;

            std::this_thread::sleep_for(std::chrono::milliseconds(5000));

            tello.SendCommand("up 25");
            while (!(tello.ReceiveResponse()));

            tello.SendCommand("down 25");
            while (!(tello.ReceiveResponse()));
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));

            tello.SendCommand("stop");
            while (!(tello.ReceiveResponse()));
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }

    saveMap(SLAM);

    tello.SendCommand("forward 15");
    while (!(tello.ReceiveResponse()));
    navigator.prev = get_position();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    tello.SendCommand("back 15");
    while (!(tello.ReceiveResponse()));
    navigator.curr = get_position();

    Point exitPoint = FindExit();
    navigator.set_exit_point(exitPoint);

    float angle = navigator.calc_rotation_angle();

    if (angle >= 0)
    {
        tello.SendCommand("cw " + std::to_string(angle));
        //Wait until tello sends response
        while (!(tello.ReceiveResponse()));
    }
    else
    {
        tello.SendCommand("ccw " + std::to_string(360 - angle));
        //Wait until tello sends response
        while (!(tello.ReceiveResponse()));
    }

    tello.SendCommand("forward 200");
    while (!(tello.ReceiveResponse()));

    isDone = true;
}

void video_stream()
{
    std::cout << "video stream" << std::endl;

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
    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(VOC_PATH,CONFIG_PATH,ORB_SLAM2::System::MONOCULAR,true);

    ctello::Tello tello;
    std::thread manage_drone(handle_drone, std::ref(tello), std::ref(SLAM));
    std::thread drone_video(video_stream);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;

    auto finish = std::chrono::system_clock::now() + 2min;
    cv::Mat currFrame;

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
            tcw = SLAM.TrackMonocular(currFrame, 0.2);
        }
        queueMutex.unlock();
    }

    std::cout << "trying to join" << std::endl;

    drone_video.join();
    std::cout << "joined drone video" <<std::endl;
    manage_drone.join();
    std::cout << "joined handle drone" <<std::endl;

    SLAM.Shutdown();

    return 0;
}

void saveMap(ORB_SLAM2::System &SLAM)
{
    std::cout << "save map" << std::endl;
    std::vector<ORB_SLAM2::MapPoint*> mapPoints = SLAM.GetMap()->GetAllMapPoints();
    std::ofstream pointData;
    pointData.open("/tmp/pointData.csv");

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

cv::Mat get_position()
{
    try {
        std::cout << tcw << std::endl;

        if (!tcw.empty())
        {
            // -Rotation.transpose * t_vec
            cv::Mat Rwc = tcw.rowRange(0, 3).colRange(0, 3).t();
            cv::Mat twc = -Rwc * tcw.rowRange(0, 3).col(3);

            //std::vector<float> quatVec = ORB_SLAM2::Converter::toQuaternion(Rwc);

            //cv::Mat t( { twc.at<float>(0), twc.at<float>(1),
            // twc.at<float>(2), quatVec[0], quatVec[1], quatVec[2], quatVec[3] });

            return twc;
        }
    }
    catch (...)
    {
    }
}
