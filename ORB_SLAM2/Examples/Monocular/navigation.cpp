#include <cmath>
#include <opencv2/core/mat.hpp>
#include "navigation.hpp"

float Navigator::calc_rotation_angle()
{
    calc_vectors();
    return calc_angle_between_vectors(m_viewingVec, m_exitVec);
}

void Navigator::calc_vectors()
{
    curr = cv::Mat(2, 1, CV_32F, { curr.at<float>(0, 0), curr.at<float>(2, 0) });
    std::cout << "Curr" << std::endl;
    std::cout << curr << std::endl;

    prev = cv::Mat(2, 1, CV_32F, { prev.at<float>(0, 0), prev.at<float>(2, 0) });
    std::cout << "prev" << std::endl;
    std::cout << prev << std::endl;

    // Calculating camera vector and exit vector
    m_viewingVec = prev - curr;

    cv::Mat pointMat(2, 1, CV_32F, { m_exitPoint.get_x(), m_exitPoint.get_y() });
    m_exitVec = pointMat - curr;

    std::cout << "exit vec" << std::endl;
    std::cout << m_exitVec << std::endl;
}

/**
 * Calculate rotation angle between 2 vectors.
 * @param v1 First vector (src vector)
 * @param v2 Second vector (dst vector)
 * @return The angle between the vectors inputted
 */
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
    // Convert angle from radians to degrees
    angle = angle * (180.0 / M_PI);

    std::cout << "angle : " << angle << std::endl;
    return angle;
}
