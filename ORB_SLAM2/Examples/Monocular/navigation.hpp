#ifndef EXIT_SCAN_NAVIGATION_HPP
#define EXIT_SCAN_NAVIGATION_HPP

#include "point.hpp"
#include "ctello.h"

class Navigator
{
protected:
    ctello::Tello m_tello;

    cv::Mat m_rotationMat, m_transVec;
    cv::Mat m_exitPoint;
    cv::Mat m_position;

    cv::Mat m_exitVec;
    cv::Mat m_droneVec;

    void get_vectors();



public:
    Navigator(ctello::Tello& tello);

    void get_position(cv::Mat tcw);

    void get_angle();
};


#endif //EXIT_SCAN_NAVIGATION_HPP
