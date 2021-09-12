//
// Created by saker on 9/12/2021.
//
#include "Dispoint.h"

#ifndef UNTITLED2_DETECTOR_H
#define UNTITLED2_DETECTOR_H


class Detector {

    void getxy();
    void findrectangle ();
    void clearinside ();
    void getExit();
    Point FindExit();

    std::vector<Point> points, vertex, outp;
    Point exit;
};


#endif //UNTITLED2_DETECTOR_H
