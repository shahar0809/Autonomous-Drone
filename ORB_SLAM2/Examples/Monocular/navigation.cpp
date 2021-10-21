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
    curr = cv::Mat(2, 1, CV_32F,{ curr.at<float>(0, 0), curr.at<float>(2, 0) });
    std::cout << "Curr" << std::endl;
    std::cout << curr << std::endl;
    prev = cv::Mat(2, 1, CV_32F,{ prev.at<float>(0, 0), prev.at<float>(2, 0) });

    std::cout << "prev" << std::endl;
    std::cout << prev << std::endl;
    // Calculating camera vector and exit vector
    m_viewingVec = prev - curr;
    cv::Mat pointMat(2, 1, CV_32F, {m_exitPoint.get_x(),m_exitPoint.get_y()});
    m_exitVec = pointMat - curr;
    std::cout << "exit vec" << std::endl;
    std::cout << m_exitVec << std::endl;
}

float Navigator::calc_angle_between_vectors(cv::Mat v1, cv::Mat v2)
{
    float dot_prod = v1.at<float>(0, 0) * v2.at<float>(0, 0) +
            v1.at<float>(1, 0) * v2.at<float>(1, 0);

    std::cout << "dot prod" << std::endl;
    std::cout << dot_prod << std::endl;

    float determinant = v1.at<float>(0, 0) * v2.at<float>(1, 0) -
                        v2.at<float>(0, 0) * v1.at<float>(1, 0);

    std::cout << "det" << std::endl;
    std::cout << determinant << std::endl;

    float angle = std::atan2(determinant , dot_prod);
    angle = angle * (180.0 / (std::atan(1.0) * 4) );
    angle = 180 - angle;

    std::cout << "angle : " << angle << std::endl;
    return angle;
}
