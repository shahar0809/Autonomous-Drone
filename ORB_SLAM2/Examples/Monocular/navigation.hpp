#ifndef EXIT_SCAN_NAVIGATION_HPP
#define EXIT_SCAN_NAVIGATION_HPP

#include "point.hpp"
#include <queue>
#include <mutex>
#include <math.h>

#define M_PI

class Navigator
{
public:
    cv::Mat curr, prev;
    std::mutex locMutex;

    bool m_clockwise;

    cv::Mat m_exitVec, m_viewingVec;

    void set_exit_point(Point p) { m_exitPoint = p; };

    float calc_rotation_angle();

    void calc_vectors();

    float calc_angle_between_vectors(cv::Mat v1, cv::Mat v2);


protected:
    Point m_exitPoint;

};

#endif //EXIT_SCAN_NAVIGATION_HPP
