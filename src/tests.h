#ifndef TESTS_H
#define TESTS_H

#include <vector>
#include <utility>
#include <cstdlib>

#include "point.h"

using std::vector;
using std::pair;

class Tests {
public:
    Tests();
    void run() {
        testGetRotation();
        testTangencyPointsTriangle();
        testTangencyPointsTriangleCol();
        testTangencyPoints5();
        testGetIncreasingChain();
    }

private:
    void testGetRotation();
    void testTangencyPointsTriangle();
    void testTangencyPointsTriangleCol();
    void testTangencyPoints5();
    void testGetIncreasingChain();

    vector<Point> poly3_;
    vector<Point> poly5_;
};

#endif // TESTS_H
