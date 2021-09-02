#include <thread>
#include <mutex>
#include <System.h>
#include "ctello.h"
#include <opencv2/opencv.hpp>
#include<chrono>
#include <Converter.h>
#include "camera_calibration.hpp"

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;

void video_stream(bool& isDone, std::mutex& doneMutex, cv::VideoCapture& capture,
                  ORB_SLAM2::System& SLAM, Calibration& cal, Mat& proj, Tello& tello);
void saveMap(ORB_SLAM2::System &SLAM);

const char* const TELLO_STREAM_URL { "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000" };

// ORB-SLAM configs
const char* const PATH_TO_VOCABULARY { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/Vocabulary/ORBvoc.txt" };
const char* const PATH_TO_CONFIG { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/tello.yaml" };
const char* const PATH_TO_SETTINGS { "/home/magshimim/Documents/exit-scan/CameraCalibration/in_VID5.xml" };

const int CIRCLE_DEGREES = 360;
const int TURN_DEGREES = 15;

/*
 * The main function of the project, connects all modules of the project:
 * - Scan the room
 * - Detect exit
 * - Navigate to exit
 */
int main()
{
    ctello::Tello tello;
    bool isDone =  false;
    std::mutex doneMutex;
    Calibration cal;

    try
    {
        cal = user_calibrate_camera(PATH_TO_SETTINGS);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }

    // Initializing ORB-SLAM2
    ORB_SLAM2::System SLAM(PATH_TO_VOCABULARY, PATH_TO_CONFIG, ORB_SLAM2::System::MONOCULAR, true);
    
    // Binding Tello to socket
    if (!tello.Bind())
    {
        std::cerr << "Couldn't bind to Tello!" << std::endl;
    }

    // Telling Tello to takeoff
    tello.SendCommand("takeoff");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Telling Tello to hover in the air
    tello.SendCommand("stop");
    //Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Starting video stream from Tello
    tello.SendCommand("streamon");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Initializing OpenCV video stream from Tello camera
    cv::VideoCapture capture{TELLO_STREAM_URL, CAP_FFMPEG};
    cv::Mat proj;
    std::thread video(video_stream, std::ref(isDone), std::ref(doneMutex), std::ref(capture),
                      std::ref(SLAM), std::ref(cal), std::ref(proj), std::ref(tello));

    // Telling video stream thread to terminate
    /*doneMutex.lock();
    isDone = true;
    doneMutex.unlock();*/

    while(SLAM.GetTrackingState() == ORB_SLAM2::Tracking::NOT_INITIALIZED)
    {
        tello.SendCommand("speed 10");
        while (!(tello.ReceiveResponse()));

        tello.SendCommand("up 30");
        while (!(tello.ReceiveResponse()));
        tello.SendCommand("down 30");
        while (!(tello.ReceiveResponse()));
    }

    video.join();

    // An ORB-SLAM map was created
    //cv::Point exitPoint = detectExit();
    //cv::Mat translationVec, rotationMat;
    //proj.col(3).copyTo(translationVec);

    //cv::Mat tmp = proj(cv::Rect(0,0,2,2));
    //tmp.copyTo(rotationMat);

    //navigateExit(exitPoint, &SLAM, translationVec, rotationMat);
}

void video_stream(bool& isDone, std::mutex& doneMutex, cv::VideoCapture& capture,
                  ORB_SLAM2::System& SLAM, Calibration& cal, Mat& proj, ctello::Tello& tello)
{
    while (true)
    {
        // ORBSLAM created a map -> proceed to detection
        if(SLAM.GetTrackingState() == ORB_SLAM2::Tracking::OK)
        {
            std::cout << "slam init" << std::endl;
            break;
        }

        // Get frames from Tello video stream
        cv::Mat frame, undistorted_frame, resized;
        capture >> frame;

        std::cout << cal.cameraMatrix << std::endl;
        std::cout << cal.distCoeffs << std::endl;

        // Using camera calibration to improve the image
        //cv::undistort(frame.clone(), undistorted_frame, cal.cameraMatrix, cal.distCoeffs);

        // Pass the image to the SLAM system
        proj = SLAM.TrackMonocular(undistorted_frame, 0.2);
    }

    std::cout << "while loop done" << std::endl;
    capture.release();
    saveMap(SLAM);
    SLAM.Shutdown();
    std::cout << "thread ended" << std::endl;
}

void saveMap(ORB_SLAM2::System &SLAM)
{
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