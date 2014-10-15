#ifndef TESTS_H
#define TESTS_H

#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <exception>

#include "point.h"

using std::vector;
using std::pair;

class Tests {
public:
    Tests();
    void run() {
        try {
            testGetRotation();
            testTangencyPointsTriangle();
            testTangencyPointsTriangleCol();
            testTangencyPoints5();
            testGetIncreasingChain();

            testMergeSimple();
            testMergeSimpleReversed();
            testMergeBelow();
            testMergeLeftBelow();
            testMergeOverlapped();
            testMergeLineFst();
            testMergeLineSnd();
            testMergeLines();
        } catch(std::exception& e) {
            std::cout << "Tests faild due to exception:\n" << e.what() << std::endl;
        }
    }

private:
    void testGetRotation();
    void testTangencyPointsTriangle();
    void testTangencyPointsTriangleCol();
    void testTangencyPoints5();
    void testGetIncreasingChain();
    void testGetIncreasingChainForHat1();

    void testMergeSimple();
    void testMergeSimpleReversed();
    void testMergeBelow();
    void testMergeLeftBelow();
    void testMergeOverlapped();
    void testMergeLineFst();
    void testMergeLineSnd();
    void testMergeLines();

    vector<Point> poly3_;
    vector<Point> poly5_;
};

#endif // TESTS_H
