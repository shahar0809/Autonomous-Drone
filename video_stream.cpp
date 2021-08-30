#include <iostream>
#include <thread>
#include <mutex>
#include <System.h>
#include "ctello.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;

void init_tello(Tello& tello);

[[noreturn]] void video_stream(bool& isDone, std::mutex& doneMutex, cv::VideoCapture& capture, ORB_SLAM2::System& SLAM);

const char* const TELLO_STREAM_URL { "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000" };

// ORB-SLAM configs
const char* const PATH_TO_VOCABULARY { "ORB_SLAM2/Vocabulary/ORBvoc.txt" };
const char* const PATH_TO_CONFIG { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/Examples/Monocular/TUM1.yaml" };

int main()
{
    ctello::Tello tello;
    bool isDone =  false;
    std::mutex doneMutex;

    // Initializing ORB-SLAM2
    ORB_SLAM2::System SLAM(PATH_TO_VOCABULARY, PATH_TO_CONFIG, ORB_SLAM2::System::MONOCULAR, true);
    
    std::cout << "init" << std::endl;
    // Binding Tello to socket
    if (!tello.Bind())
    {
        std::cerr << "Couldn't bind to Tello!" << std::endl;
    }

    // Telling Tello to takeoff
    tello.SendCommand("takeoff");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    tello.SendCommand("stop");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Starting video stream from Tello
    tello.SendCommand("streamon");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Initializing OpenCV video stream from Tello camera
    cv::VideoCapture capture{TELLO_STREAM_URL, CAP_FFMPEG};

    std::thread video(video_stream, std::ref(isDone), std::ref(doneMutex), std::ref(capture), std::ref(SLAM));

    // Scan the room 360 degrees
    //tello.SendCommand("cw 360");
    //while (!(tello.ReceiveResponse()));

    sleep(30);

    // Telling video stream thread to terminate
    doneMutex.lock();
    isDone = true;
    doneMutex.unlock();

    video.join();
}

void init_tello(Tello& tello)
{
    std::cout << "init" << std::endl;
    // Binding Tello to socket
    if (!tello.Bind())
    {
        return;
    }

    // Starting video stream from Tello
    tello.SendCommand("streamon");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));
}

void video_stream(bool& isDone, std::mutex& doneMutex, cv::VideoCapture& capture, ORB_SLAM2::System& SLAM)
{
    std::cout << "stream" << std::endl;

    bool terminate = false;

    while (!terminate)
    {
        doneMutex.lock();
        terminate = isDone;
        doneMutex.unlock();

        // Get frames from Tello video stream
        cv::Mat frame;
        capture >> frame;

        // Pass the image to the SLAM system
        SLAM.TrackMonocular(frame, 0.2);
    }

    capture.release();
    SLAM.Shutdown();
}