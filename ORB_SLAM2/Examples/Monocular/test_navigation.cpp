#include "detect_exit.hpp"
#include "navigation.hpp"

cv::Mat get_position(cv::Mat tcw);

int main()
{
    Navigator navigator;
    Point exitPoint = FindExit("/home/magshimim/Documents/exit-scan/Data Examples/pointData_drone.csv");
    navigator.set_exit_point(exitPoint);

    float prev_arr[4][4] = {0.7651552, -0.10523132, 0.6351881, 0.20486319,
        0.14435345, 0.98947603, -0.0099638673, 0.095739007,
        -0.62745488, 0.099315502, 0.77229321, -0.031095805,
        0, 0, 0, 1};

    float curr_arr[4][4] = {0.76549113, -0.098876514, 0.63580406, 0.22287761,
        0.13696532, 0.99051625, -0.010863317, 0.08497747,
        -0.62870014, 0.095398881, 0.77177405, -0.046553496,
        0, 0, 0, 1};

    cv::Mat prev(4, 4, CV_64F, prev_arr);
    cv::Mat curr(4, 4, CV_64F, curr_arr);

    navigator.prev = get_position(prev);
    navigator.curr = get_position(curr);

    float rot_angle = navigator.calc_rotation_angle();
}

cv::Mat get_position(cv::Mat tcw)
{
    try {
        std::cout << tcw << std::endl;

        if (!tcw.empty())
        {
            // -Rotation.transpose * t_vec
            cv::Mat Rwc = tcw.rowRange(0, 3).colRange(0, 3).t();
            cv::Mat twc = -Rwc * tcw.rowRange(0, 3).col(3);
            std::cout << twc << std::endl;
            return twc;
        }
    }
    catch (...)
    {
    }
}
