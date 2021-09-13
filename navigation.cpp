#include "navigation.hpp"

Navigator::Navigator(ctello::Tello &tello) : m_tello(tello) {}

void Navigator::get_position(int tcw)
{
    m_transVec = tcw(Range::all(), Range(3, 4)).clone();
    m_rotationMat = tcw(Range::all(), Range(0, 3)).clone();

    m_position = cv::transpose(m_rotationMat) * m_transVec;
}

void Navigator::get_vectors()
{
    m_exitVec = cv::Mat()
}

double get_angle()
{
    double x1,x2,y1,y2,z1,z2;

    x1 = m_exitVec.at<double>(0,0);x2 = m_droneVec.at<double>(0,0);
    y1 = m_exitVec.at<double>(2,0);y2 = m_droneVec.at<double>(2,0);
    z1 = m_exitVec.at<double>(1,0);z2 = m_droneVec.at<double>(1,0);

    double dot = x1*x2 + y1*y2 + z1*z2;
    double lenSq1 = x1*x1 + y1*y1 + z1*z1;
    double lenSq2 = x2*x2 + y2*y2 + z2*z2;
    return acos(dot/sqrt(lenSq1 * lenSq2));

}

