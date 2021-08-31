#include <thread>
#include <mutex>
#include <System.h>
#include "ctello.h"
#include <opencv2/opencv.hpp>
#include "camera_calibration.hpp"

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;

void video_stream(bool& isDone, std::mutex& doneMutex, cv::VideoCapture& capture,
                  ORB_SLAM2::System& SLAM, Calibration& cal);

const char* const TELLO_STREAM_URL { "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000" };

// ORB-SLAM configs
const char* const PATH_TO_VOCABULARY { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/Vocabulary/ORBvoc.txt" };
const char* const PATH_TO_CONFIG { "/home/magshimim/Documents/exit-scan/TUM1.yaml" };

const int CIRCLE_DEGREES = 360;
const int TURN_DEGREES = 15;

int main()
{
    ctello::Tello tello;
    bool isDone =  false;
    std::mutex doneMutex;
    Calibration cal;

    try {
        cal = user_calibrate_camera("/home/magshimim/Documents/exit-scan/in_VID5.xml");
    } catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }

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

    std::thread video(video_stream, std::ref(isDone), std::ref(doneMutex), std::ref(capture),
                      std::ref(SLAM), std::ref(cal));

    // Scan the room 360 degrees
    //tello.SendCommand("cw 360");
    //while (!(tello.ReceiveResponse()));

    while (true)
    {
        for (int i = 0; i < CIRCLE_DEGREES; i += TURN_DEGREES)
        {
            //tello.SendCommand("forward 2");
            //while (!(tello.ReceiveResponse()));
            //tello.SendCommand("back 2");
            //while (!(tello.ReceiveResponse()));
            tello.SendCommand("cw " + std::to_string(TURN_DEGREES));
            while (!(tello.ReceiveResponse()));
            sleep(3);

            if (SLAM.GetTrackingState())
            {
                tello.SendCommand("cw -" + std::to_string(TURN_DEGREES));
                while (!(tello.ReceiveResponse()));
                sleep(3);
            }
        }
    }


    //sleep(30);

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

void video_stream(bool& isDone, std::mutex& doneMutex, cv::VideoCapture& capture,
                  ORB_SLAM2::System& SLAM, Calibration& cal)
{
    std::cout << "stream" << std::endl;

    bool terminate = false;

    while (!terminate)
    {
        doneMutex.lock();
        terminate = isDone;
        doneMutex.unlock();

        // Get frames from Tello video stream
        cv::Mat frame, undist_frame;
        capture >> frame;

        cv::undistort(frame.clone(), undist_frame, cal.cameraMatrix, cal.distCoeffs);

        // Pass the image to the SLAM system
        SLAM.TrackMonocular(undist_frame, 0.2);
    }

    capture.release();
    SLAM.Shutdown();
}