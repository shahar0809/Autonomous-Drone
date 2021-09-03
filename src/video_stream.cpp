#include <thread>
#include <mutex>
#include <System.h>
#include <Converter.h>
#include <queue>
#include <atomic>

#include "ctello.h"
#include "camera_calibration.hpp"

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;

void saveMap(ORB_SLAM2::System &SLAM);
void handle_drone(ctello::Tello& tello, std::mutex& initMutex, bool& isInit);
void capture_frames(std::mutex& initMutex, bool& isInit);

const char* const TELLO_STREAM_URL { "udp://0.0.0.0:11111?overrun_nonfatal=1&fifo_size=50000000" };

// ORB-SLAM configs
const char* const PATH_TO_VOCABULARY { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/Vocabulary/ORBvoc.txt" };
const char* const PATH_TO_CONFIG { "/home/magshimim/Documents/exit-scan/ORB_SLAM2/tello.yaml" };
const char* const PATH_TO_SETTINGS { "/home/magshimim/Documents/exit-scan/CameraCalibration/in_VID5.xml" };

const int CIRCLE_DEGREES = 360;
const int TURN_DEGREES = 15;

std::queue<cv::Mat> frames;
std::atomic<bool> signal { false };

/*
 * The main function of the project, connects all modules of the project:
 * - Scan the room
 * - Detect exit
 * - Navigate to exit
 */
int main()
{
    ctello::Tello tello;
    bool isInit =  false;
    std::mutex initMutex;

    std::thread drone_t(handle_drone, std::ref(tello), std::ref(initMutex), std::ref(isInit));
    std::thread capture_t(capture_frames, std::ref(initMutex), std::ref(isInit));

    // Initializing ORB-SLAM2
    ORB_SLAM2::System SLAM(PATH_TO_VOCABULARY, PATH_TO_CONFIG, ORB_SLAM2::System::MONOCULAR, true);
    cv::Mat projection;
    signal = true;

    while (!frames.empty())
    {
        // ORBSLAM created a map -> proceed to detection
        if(SLAM.GetTrackingState() == ORB_SLAM2::Tracking::OK)
        {
            initMutex.lock();
            isInit = true;
            initMutex.unlock();
            break;
        }

        cv::Mat frame = frames.front();
        frames.pop();

        // Pass the image to the SLAM system
        if(!frame.empty())
        {
            projection = SLAM.TrackMonocular(frame, 0.2);
            std::cout << "Projection mat: " << projection << std::endl;
        }
    }

    drone_t.join();
    capture_t.join();

    saveMap(SLAM);

    SLAM.Shutdown();

    // An ORB-SLAM map was created
    //cv::Point exitPoint = detectExit();
    //cv::Mat translationVec, rotationMat;
    //proj.col(3).copyTo(translationVec);

    //cv::Mat tmp = proj(cv::Rect(0,0,2,2));
    //tmp.copyTo(rotationMat);

    //navigateExit(exitPoint, &SLAM, translationVec, rotationMat);
}

void capture_frames(std::mutex& initMutex, bool& isInit)
{
    while (!signal);

    cv::VideoCapture capture{TELLO_STREAM_URL, CAP_FFMPEG};
    cv::Mat frame;

    bool endLoop = false;

    while (capture.isOpened() && !endLoop)
    {
        initMutex.lock();
        endLoop = isInit;
        initMutex.unlock();

        capture >> frame;
        frames.push(frame);
    }
}

void handle_drone(ctello::Tello& tello, std::mutex& initMutex, bool& isInit)
{
    // Binding Tello to socket
    if (!tello.Bind())
    {
        std::cerr << "Couldn't bind to Tello!" << std::endl;
    }

    // Starting video stream from Tello
    tello.SendCommand("streamon");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    while (!signal);

    // Telling Tello to takeoff
    tello.SendCommand("takeoff");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    // Telling Tello to hover in the air
    tello.SendCommand("stop");
    //Wait until tello sends response
    while (!(tello.ReceiveResponse()));

    bool endLoop = false;
    while(!endLoop)
    {
        initMutex.lock();
        endLoop = isInit;
        initMutex.unlock();

        tello.SendCommand("speed 10");
        while (!(tello.ReceiveResponse()));

        tello.SendCommand("up 30");
        while (!(tello.ReceiveResponse()));
        tello.SendCommand("down 30");
        while (!(tello.ReceiveResponse()));
    }
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