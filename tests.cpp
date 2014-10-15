#include "tests.h"

#include <cassert>

#include "split_poly.h"

using std::vector;
using std::pair;

Tests::Tests() {
    poly3_ = {{1,0}, {3,1}, {2,2}};
    poly5_ = {{0,0}, {0,3}, {-2, 5}, {-3,3}, {-3,0}};
}

void Tests::testGetRotation() {
    assert(getRotation({0,0}, {0, -2}, {2, 0}) == C_CW);
    assert(getRotation({0,0}, {2, 0}, {0, -2}) == CW);
    assert(getRotation({0,0}, {0, -2}, {0, 2}) == COLLIN);
}

void Tests::testTangencyPointsTriangle() {
    pair<size_t, size_t> tps1 = tangencyPoints({0,0}, poly3_);
    assert(tps1.first == 2);
    assert(tps1.second == 0);
}

void Tests::testTangencyPointsTriangleCol() {
    pair<size_t, size_t> tps1 = tangencyPoints({-1,-1}, poly3_);
    assert(tps1.first == 1);
    assert(tps1.second == 2);
}

void Tests::testTangencyPoints5() {
    pair<size_t, size_t> tps1 = tangencyPoints({-2,-1}, poly5_);
    assert(tps1.first == 4);
    assert(tps1.second == 0);

    tps1 = tangencyPoints({2,0}, poly5_);
    assert(tps1.first == 1);
    assert(tps1.second == 0);

    tps1 = tangencyPoints({2,5}, poly5_);
    assert(tps1.first == 2);
    assert(tps1.second == 0);

    tps1 = tangencyPoints({-2,7}, poly5_);
    assert(tps1.first == 1);
    assert(tps1.second == 3);
}

void Tests::testGetIncreasingChain() {
    vector<Point> ch3 = getIncreasingChain({0,0}, poly3_);
    assert(ch3.size() == 3);
    assert(ch3[0] == poly3_[0]);
    assert(ch3[1] == poly3_[1]);
    assert(ch3[2] == poly3_[2]);

    vector<Point> ch3col = getIncreasingChain({-1,-1}, poly3_);
    assert(ch3col.size() == 2);
    assert(ch3col[0] == poly3_[1]);
    assert(ch3col[1] == poly3_[2]);

    vector<Point> ch5 = getIncreasingChain({-2,-1}, poly5_);
    assert(ch5.size() == 5);
    assert(ch5[0] == poly5_[0]);
    assert(ch5[1] == poly5_[1]);
    assert(ch5[2] == poly5_[2]);
    assert(ch5[3] == poly5_[3]);
    assert(ch5[4] == poly5_[4]);

    ch5 = getIncreasingChain({2,0}, poly5_);
    assert(ch5.size() == 5);
    assert(ch5[0] == poly5_[1]);
    assert(ch5[1] == poly5_[2]);
    assert(ch5[2] == poly5_[3]);
    assert(ch5[3] == poly5_[4]);
    assert(ch5[4] == poly5_[0]);

    ch5 = getIncreasingChain({2,5}, poly5_);
    assert(ch5.size() == 4);
    assert(ch5[0] == poly5_[2]);
    assert(ch5[1] == poly5_[3]);
    assert(ch5[2] == poly5_[4]);
    assert(ch5[3] == poly5_[0]);

    ch5 = getIncreasingChain({-2,7}, poly5_);
    assert(ch5.size() == 4);
    assert(ch5[0] == poly5_[3]);
    assert(ch5[1] == poly5_[4]);
    assert(ch5[2] == poly5_[0]);
    assert(ch5[3] == poly5_[1]);
}
