#include <cmath>
#include <opencv2/core/mat.hpp>
#include "navigation.hpp"

float Navigator::calc_rotation_angle()
{
    calc_vectors();
    return calc_angle_between_vectors(m_exitVec, m_viewingVec);
}

void Navigator::calc_vectors()
{
    locMutex.lock();
    cv::Mat currLocation = lastLocations.back();
    currLocation = { currLocation.at<float>(0), currLocation.at<float>(1) };
    lastLocations.pop();
    cv::Mat prevLocation = lastLocations.back();
    prevLocation = { prevLocation.at<float>(0), prevLocation.at<float>(1) };
    lastLocations.pop();
    locMutex.unlock();

    m_viewingVec = prevLocation - currLocation;
    m_exitVec = (cv::Mat)m_exitPoint - currLocation;
}

float Navigator::calc_angle_between_vectors(cv::Mat v1, cv::Mat v2)
{
    float dot_prod = v1.at<float>(0) * v2.at<float>(0) +
            v1.at<float>(1) * v2.at<float>(1);

    float determinant = v1.at<float>(0) * v2.at<float>(1) -
                        v2.at<float>(0) * v1.at<float>(1);

    return std::atan2(determinant , dot_prod);
}
