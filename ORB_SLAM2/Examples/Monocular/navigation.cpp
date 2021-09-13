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
