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
#include <netinet/in.h>
#include <arpa/inet.h>

/* FUNCTIONS */
void saveMap(ORB_SLAM2::System &SLAM);
void video_stream();
void handle_drone(ctello::Tello& tello, ORB_SLAM2::System& SLAM);
void get_position();

//(((((((((((((((((((((((((()))))))))))))))))))))))))))))))
std::mutex Mutex;

std::mutex queueMutex;
std::queue<cv::Mat> frames;

/* ATOMIC VARIABLES */
std::atomic<bool> isInit = { false };
std::atomic<bool> isDone = { false };

Navigator navigator;
cv::Mat tcw;
//((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))
bool NotLocalized = false;
bool closeProgram = false;
bool savePoints = false;



/* CONSTANTS */
const int TURN_DEGREE = 15;
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

    for (int deg = 0; deg <= FULL_TURN;)
    {
        //((((((((((()))))))))))))))
        Mutex.lock();
        if(NotLocalized){
            if (deg >= 30){
                deg -= 30;
            }else{
                deg = 0;
            }
            tello.SendCommand("backward 10");
            while (!(tello.ReceiveResponse()));
        }
        Mutex.unlock();

        tello.SendCommand("cw " + std::to_string(TURN_DEGREE));
        while (!(tello.ReceiveResponse()));
        deg += TURN_DEGREE;

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        tello.SendCommand("forward 20");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        tello.SendCommand("backward 20");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        tello.SendCommand("stop");
        while (!(tello.ReceiveResponse()));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        /*if(!SLAM.MapChanged())
        {
            std::cout << "NOT CHANGED" << std::endl;
            tello.SendCommand("ccw " + std::to_string(TURN_DEGREE - 10));
            while (!(tello.ReceiveResponse()));
            deg -= TURN_DEGREE -10;

            std::this_thread::sleep_for(std::chrono::milliseconds(5000));

            tello.SendCommand("forward 10");
            while (!(tello.ReceiveResponse()));
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));

            tello.SendCommand("backward 20");
            while (!(tello.ReceiveResponse()));
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));

            tello.SendCommand("stop");
            while (!(tello.ReceiveResponse()));
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }*/
    }
    //((((((((((((((((((((((((()))))))))))))))))))))
    Mutex.lock();
    savePoints = true;
    Mutex.unlock();
    while(savePoints);//to make sure that the map has been saved
    //saveMap(SLAM);

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
    Mutex.lock();
    closeProgram = true;
    Mutex.unlock();


}

void video_stream()
{
    std::cout << "video stream" << std::endl;

    cv::VideoCapture capture{TELLO_STREAM, cv::CAP_FFMPEG};
    cv::Mat frame;

    /* If ORB-SLAM is not initialized, move up and down */
    while(true)
    {
        std::cout << "try" << std::endl;

        capture >> frame;

        if (!frame.empty())
        {
            // Push frame into queue
            queueMutex.lock();
            frames.push(frame);
            queueMutex.unlock();
        }

        Mutex.lock();
        if(closeProgram){
            Mutex.unlock();
            break;
        }
        Mutex.unlock();
        //get_position();
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
//((((((((((((((((((()))))))))))))))
    while (true)
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
            //((((((((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))
            Mutex.lock();
            if (closeProgram) {//it's the end of the program
                Mutex.unlock();
                break;
            }

            if (tcw.empty()) {
                NotLocalized = true;
                Mutex.unlock();
                continue;
            }
            NotLocalized = false;

            get_position();//when ever we need to find the position of the drone we have it.

            if (savePoints) {//it's the end of the scan
                saveMap(SLAM);
                savePoints = false;
            }


            Mutex.unlock();

        }
        queueMutex.unlock();
    }

    std::cout << "trying to join" << std::endl;

    drone_video.join();
    manage_drone.join();

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

void get_position()
{
    try {
        std::cout << tcw << std::endl;

        if (!tcw.empty())
        {
            cv::Mat translation = tcw(cv::Range::all(), cv::Range(3, 4)).clone();
            cv::Mat rotation = -rotation * tcw.rowRange(0, 3).col(3);

            std::vector<float> quatVec = ORB_SLAM2::Converter::toQuaternion(rotation);

            cv::Mat twc( { translation.at<float>(0), translation.at<float>(1),
                           translation.at<float>(2), quatVec[0], quatVec[1], quatVec[2], quatVec[3] });

            navigator.lastLocations.push(twc);
        }
    }
    catch (...)
    {
        return;
    }
}