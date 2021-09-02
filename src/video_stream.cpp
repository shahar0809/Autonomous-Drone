#include <thread>
#include <mutex>
#include <System.h>
#include "ctello.h"
#include <opencv2/opencv.hpp>
#include <Converter.h>
#include "camera_calibration.hpp"

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;

void video_stream(bool& isDone, std::mutex& doneMutex, cv::VideoCapture& capture,
                  ORB_SLAM2::System& SLAM, Calibration& cal);
void saveMap(ORB_SLAM2::System &SLAM);

const char* const TELLO_STREAM_URL { "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000" };

// ORB-SLAM configs
const char* const PATH_TO_VOCABULARY { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/Vocabulary/ORBvoc.txt" };
const char* const PATH_TO_CONFIG { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/tello.yaml" };
const char* const PATH_TO_SETTINGS { "/home/magshimim/Documents/exit-scan/in_VID5.xml" };

const int CIRCLE_DEGREES = 360;
const int TURN_DEGREES = 15;

int main()
{
    ctello::Tello tello;
    bool isDone =  false;
    std::mutex doneMutex;
    Calibration cal;

    try
    {
        cal = user_calibrate_camera(PATH_TO_SETTINGS);
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
    //Wait until tello sends response
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

    int counter = 0;

    while (counter <= 30)
    {
        for (int i = 0; i < CIRCLE_DEGREES; i += TURN_DEGREES)
        {
            tello.SendCommand("forward 2");
            while (!(tello.ReceiveResponse()));
            tello.SendCommand("back 2");
            while (!(tello.ReceiveResponse()));
            tello.SendCommand("cw " + std::to_string(TURN_DEGREES));
            while (!(tello.ReceiveResponse()));
            sleep(3);

            if (SLAM.GetTrackingState())
            {
                tello.SendCommand("cw -" + std::to_string(TURN_DEGREES));
                while (!(tello.ReceiveResponse()));
                sleep(3);
            }

            counter += 3;
        }
    }

    std::cout << "temmmm true " << std::endl;
    // Telling video stream thread to terminate
    doneMutex.lock();
    isDone = true;
    doneMutex.unlock();

    video.join();
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

        cout << "term " << terminate << std::endl;

        // Get frames from Tello video stream
        cv::Mat frame, undist_frame, resized;
        capture >> frame;
        cout << "hello" << std::endl;
        //cv::resize(frame, resized, cv::Size(500, 500));
        //cout << "resize" << std::endl;

        std::cout << cal.cameraMatrix << std::endl;
        std::cout << cal.distCoeffs << std::endl;

        cv::undistort(frame.clone(), undist_frame, cal.cameraMatrix, cal.distCoeffs);
        cout << "undistort" << std::endl;
        // Pass the image to the SLAM system
        SLAM.TrackMonocular(undist_frame, 0.2);
        cout << "orb" << std::endl;
    }

    std::cout << "doneeeeee" << std::endl;
    capture.release();
    saveMap(SLAM);
    SLAM.Shutdown();
    std::cout << "doneeeeee" << std::endl;
}

void saveMap(ORB_SLAM2::System &SLAM)
{
    std::vector<ORB_SLAM2::MapPoint*> mapPoints = SLAM.GetMap()->GetAllMapPoints();
    std::ofstream pointData;
    pointData.open("/tmp/pointData.csv");

    for(auto p : mapPoints)
    {
        if (p != NULL)
        {
            auto point = p->GetWorldPos();
            Eigen::Matrix<double, 3, 1> v = ORB_SLAM2::Converter::toVector3d(point);
            pointData << v.x() << "," << v.y() << "," << v.z()<<  std::endl;
        }
    }
    pointData.close();
}