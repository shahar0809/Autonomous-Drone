#include "ctello.h"
const char* const TELLO_STREAM_URL{ "udp://0.0.0.0:11111" };
#define Degree 30


int main()
{
    int i;
    ctello::Tello tello;
    if (!tello.Bind())
    {
        return 0;
    }
    //start 
    tello.SendCommand("streamon ");//Enable video stream     
    while (!(tello.ReceiveResponse()));

    //cv::VideoCapture capture{ TELLO_STREAM_URL, CAP_FFMPEG };
    /*?????????????????????????????????????????????????
    
        while (true)
    {
        cv::Mat frame;
        capture >> frame;
        if (!frame.empty())
        {
            imshow("CTello Stream", frame);
        }
        if (waitKey(1) == 27)
        {
            break;
        }
    }
    // Show what the Tello sees
        resize(frame, frame, Size(), 0.75, 0.75);
        imshow("CTello Stream", frame);
        if (waitKey(1) == 27)
        {
            break;
        }
    */
    tello.SendCommand("takeoff");
    while (!(tello.ReceiveResponse()));// Wait for response

    //scan the room
    //scan
    //

    for (i = 0; i < 360; i += Degree) {//complete a scan
        tello.SendCommand("forward 5");
        while (!(tello.ReceiveResponse()));
        tello.SendCommand("back 5");
        while (!(tello.ReceiveResponse()));
        tello.SendCommand("cw Degree");
        while (!(tello.ReceiveResponse()));

        // ####################################
        if () {//if there is no new points in the map (didn't scan any thing)
            tello.SendCommand("back 10");
            while (!(tello.ReceiveResponse()));
            i -= Degree;
        }
    }
    //complete a round
    // 
    //find exit 

    //locate 
    //########################################
    while () {//didn't get to the exit point
        while ()//there is something in front of the drone(according to the map)
        {
            tello.SendCommand("cw Degree");
            while (!(tello.ReceiveResponse()));
        }
        tello.SendCommand("forward 10");
        while (!(tello.ReceiveResponse()));
    }


    //end
    tello.SendCommand("land");
    while (!(tello.ReceiveResponse()));
    tello.SendCommand("streamoff ");//Disable video stream     
    while (!(tello.ReceiveResponse()));

    return 0;
}


/*
up x          Ascend to 'x' cm[20 - 500]                        ok / error\n"
"  down x        Descend to 'x' cm [20-500]                       ok / error\n"
"  left x        Fly left for 'x' cm [20-500]                     ok / error\n"
"  right x       Fly right for 'x' cm [20-500]                    ok / error\n"
"  forward x     Fly forward for 'x' cm [20-500]                  ok / error\n"
"  back x        Fly backward for 'x' cm [20-500]  





"  cw            Rotate 'x' degrees in clockwise [1-360]          ok / error\n"
"  ccw           Rotate 'x' degrees in counterclockwise [1-360]   ok / error\n"
"  flip x        Flip in 'x' direction [l, r, f, b]               ok / error\n"
"  go x y z s    Fly to (x, y, z) at speed 's' [10-100]           ok / error\n"
"  stop          Hovers in the air  


"  battery?      Obtain current battery percentage
"  wifi?         Obtain Wi-Fi SNR 
*/
