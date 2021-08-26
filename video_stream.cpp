#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>

#include "ctello.h"
#include <opencv2/core/core.hpp>

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;

const char* const TELLO_STREAM_URL { "udp://0.0.0.0:11111" };

// ORB-SLAM configs
const char* const PATH_TO_VOCABULARY { "ORBvoc.txt.tar.gz" };
const char* const PATH_TO_CONFIG { "TUM.yaml" };

int main()
{
    Tello tello;
    bool* isDone = false;
    std::mutex doneMutex;

    init_tello(tello);

    std::thread video(video_stream, isDone, doneMutex);

    // Scan the room 360 degress
    tello.SendCommand("cw 360");

    while (!(tello.ReceiveResponse()));

    doneMutex.lock();
    isDone = true;
    doneMutex.unlock()
}

void init_tello()
{
    // Binding Tello to socket
    if (!tello.Bind())
    {
        return 0;
    }

    // Starting video stream from Tello
    tello.SendCommand("streamon");
    // Wait until tello sends response
    while (!(tello.ReceiveResponse()));
}

void video_stream(bool* isDone, std::mutex doneMutex)
{
    cv::VideoCapture(TELLO_STREAM_URL, CAP_FFMPEG);
    ORB_SLAM2::System SLAM(PATH_TO_VOCABULARY, PATH_TO_CONFIG, ORB_SLAM2::System::MONOCULAR, true);

    bool terminate = false;
    int timestamp = 0;

    while (!terminate)
    {
        timestamp++;

        doneMutex.lock();
        terminate = *isDone;
        doneMutex.unlock();

        // See surrounding.
        cv::Mat frame;
        capture >> frame;

        // TODO: ORB_SLAM on frame from drone (don't know about timestamps)
        // Pass the image to the SLAM system
        SLAM.TrackMonocular(frame, timestamp);

        // Show what the Tello sees
        imshow("CTello Stream", frame);

        // Stop stream
        if (waitKey(1) == 27)
        {
            break;
        }
    }

    capture.release();
    SLAM.Shutdown();
}