#include "tests.h"

#include <cassert>

#include "utils.h"
#include "merge.h"

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

void Tests::testMergeSimple() {
    vector<Point> m1 = merge(poly5_, poly3_);
    assert(m1.size() == poly3_.size() + poly5_.size());
    assert(m1[0] == poly5_[3]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == poly5_[0]);
    assert(m1[3] == poly3_[0]);
    assert(m1[4] == poly3_[1]);
    assert(m1[5] == poly3_[2]);
    assert(m1[6] == poly5_[1]);
    assert(m1[7] == poly5_[2]);
}

void Tests::testMergeSimpleReversed() {
    vector<Point> m1 = merge(poly3_, poly5_);
    assert(m1.size() == poly3_.size() + poly5_.size());
    assert(m1[0] == poly5_[3]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == poly5_[0]);
    assert(m1[3] == poly3_[0]);
    assert(m1[4] == poly3_[1]);
    assert(m1[5] == poly3_[2]);
    assert(m1[6] == poly5_[1]);
    assert(m1[7] == poly5_[2]);
}

void Tests::testMergeBelow() {
    vector<Point> polyBelow = {{-3,-1}, {-1,0}, {-2,1}};
    vector<Point> m1 = merge(polyBelow, poly5_);
    assert(m1.size() == polyBelow.size() + poly5_.size() - 1);
    assert(m1[0] == poly5_[3]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == polyBelow[0]);
    assert(m1[3] == polyBelow[1]);
    assert(m1[4] == poly5_[0]);
    assert(m1[5] == poly5_[1]);
    assert(m1[6] == poly5_[2]);
}

void Tests::testMergeLeftBelow() {
    vector<Point> polyBl = {{-5,-2}, {-3,-1}, {-4,0}};
    vector<Point> m1 = merge(poly5_, polyBl);
    assert(m1.size() == polyBl.size() + poly5_.size() - 1);
    assert(m1[0] == polyBl[0]);
    assert(m1[1] == poly5_[0]);
    assert(m1[2] == polyBl[1]);
    assert(m1[3] == poly5_[1]);
    assert(m1[4] == polyBl[2]);
    assert(m1[5] == poly5_[2]);
    assert(m1[6] == poly5_[3]);
}

void Tests::testMergeOverlapped() {
    vector<Point> polyO = {{-3,5}, {-3,2}, {3,2}, {3, 5}};
    vector<Point> m1 = merge(poly5_, polyO);
    assert(m1.size() == polyO.size() + poly5_.size() - 1);
    assert(m1[0] == polyO[0]);
    assert(m1[1] == polyO[1]);
    assert(m1[2] == poly5_[4]);
    assert(m1[3] == poly5_[0]);
    assert(m1[4] == poly5_[1]);
    assert(m1[5] == polyO[2]);
    assert(m1[6] == polyO[3]);
    assert(m1[7] == poly5_[2]);

    polyO = {{-3,2}, {-3,1}, {3,2}};
    m1 = merge(poly5_, polyO);
    assert(m1.size() == polyO.size() + poly5_.size() - 1);
    assert(m1[0] == poly5_[3]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == polyO[1]);
    assert(m1[3] == poly5_[0]);
    assert(m1[4] == polyO[2]);
    assert(m1[5] == poly5_[1]);
    assert(m1[6] == poly5_[2]);

    polyO = {{-3,2}, {-3,-3}, {-1,-3}};
    m1 = merge(poly5_, polyO);
    assert(m1.size() == polyO.size() + poly5_.size() - 1);
    assert(m1[0] == poly5_[3]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == polyO[1]);
    assert(m1[3] == polyO[2]);
    assert(m1[4] == poly5_[0]);
    assert(m1[5] == poly5_[1]);
    assert(m1[6] == poly5_[2]);
}

void Tests::testMergeLineFst() {
    vector<Point> line = {{0,0}, {1,1}};
    vector<Point> m1 = merge(poly3_, line);
    assert(m1.size() == line.size() + poly3_.size());
    assert(m1[0] == line[0]);
    assert(m1[1] == poly3_[0]);
    assert(m1[2] == poly3_[1]);
    assert(m1[3] == line[1]);
    assert(m1[4] == poly3_[2]);

    line = {{-5,1}, {-2,1}};
    m1 = merge(poly5_, line);
    assert(m1.size() == line.size() + poly5_.size() - 1);
    assert(m1[0] == line[0]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == poly5_[0]);
    assert(m1[3] == line[1]);
    assert(m1[4] == poly5_[1]);
    assert(m1[5] == poly5_[2]);

    line = {{-5,4}, {-2,4}};
    m1 = merge(poly5_, line);
    assert(m1.size() == line.size() + poly5_.size() - 1);
    assert(m1[0] == line[0]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == poly5_[0]);
    assert(m1[3] == poly5_[1]);
    assert(m1[4] == line[1]);
    assert(m1[5] == poly5_[2]);

    line = {{-5,3}, {-5,2}};
    m1 = merge(poly5_, line);
    assert(m1.size() == line.size() + poly5_.size() - 1);
    assert(m1[0] == line[0]);
    assert(m1[1] == line[1]);
    assert(m1[2] == poly5_[4]);
    assert(m1[3] == poly5_[0]);
    assert(m1[4] == poly5_[1]);
    assert(m1[5] == poly5_[2]);
}

void Tests::testMergeLineSnd() {
    vector<Point> line = {{2,1}, {4,1}, {7,1}};
    vector<Point> m1 = merge(poly3_, line);
    assert(m1.size() == line.size() + poly3_.size());
    assert(m1[0] == poly3_[0]);
    assert(m1[1] == line[2]);
    assert(m1[2] == line[1]);
    assert(m1[3] == poly3_[1]);
    assert(m1[4] == line[0]);
    assert(m1[5] == poly3_[2]);

    line = {{5,2}, {7,3}};
    m1 = merge(poly3_, line);
    assert(m1.size() == line.size() + poly3_.size());
    assert(m1[0] == poly3_[0]);
    assert(m1[1] == poly3_[1]);
    assert(m1[2] == line[0]);
    assert(m1[3] == line[1]);
    assert(m1[4] == poly3_[2]);

    line = {{-3,2}, {-1,2}, {1,2}, {4,2}};
    m1 = merge(line, poly5_);
    assert(m1.size() == line.size() + poly5_.size());
    assert(m1[0] == poly5_[3]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == line[0]);
    assert(m1[3] == poly5_[0]);
    assert(m1[4] == line[1]);
    assert(m1[5] == line[2]);
    assert(m1[6] == line[3]);
    assert(m1[7] == poly5_[1]);
    assert(m1[8] == poly5_[2]);

    line = {{-3,-3}, {-3,-1}};
    m1 = merge(line, poly5_);
    assert(m1.size() == line.size() + poly5_.size());
    assert(m1[0] == poly5_[3]);
    assert(m1[1] == poly5_[4]);
    assert(m1[2] == line[0]);
    assert(m1[3] == line[1]);
    assert(m1[4] == poly5_[0]);
    assert(m1[5] == poly5_[1]);
    assert(m1[6] == poly5_[2]);
}

void Tests::testMergeLines() {
    vector<Point> line1 = {{0,0}, {2,0}};
    vector<Point> line2 = {{3,0}, {7,0}};
    vector<Point> m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[0]);
    assert(m1[1] == line1[1]);
    assert(m1[2] == line2[0]);
    assert(m1[3] == line2[1]);

    line1 = {{0,0}, {2,0}};
    line2 = {{3,0}, {7,1}};
    m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[0]);
    assert(m1[1] == line1[1]);
    assert(m1[2] == line2[0]);
    assert(m1[3] == line2[1]);

    line1 = {{0,0}, {2,0}};
    line2 = {{1,-1}, {1,-3}};
    m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[0]);
    assert(m1[1] == line2[1]);
    assert(m1[2] == line2[0]);
    assert(m1[3] == line1[1]);

    line1 = {{0,0}, {2,0}};
    line2 = {{2,2}, {4,2}};
    m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[0]);
    assert(m1[1] == line1[1]);
    assert(m1[2] == line2[1]);
    assert(m1[3] == line2[0]);

    line1 = {{0,0}, {2,0}};
    line2 = {{1,4}, {3,4}};
    m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[0]);
    assert(m1[1] == line1[1]);
    assert(m1[2] == line2[1]);
    assert(m1[3] == line2[0]);

    line1 = {{0,2}, {0,4}};
    line2 = {{0,0}, {3,0}};
    m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[1]);
    assert(m1[1] == line1[0]);
    assert(m1[2] == line2[0]);
    assert(m1[3] == line2[1]);

    line1 = {{0,0}, {2,0}};
    line2 = {{2,3}, {4,1}};
    m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[0]);
    assert(m1[1] == line1[1]);
    assert(m1[2] == line2[1]);
    assert(m1[3] == line2[0]);

    line1 = {{0,0}, {2,0}};
    line2 = {{2,80}, {2,1}};
    m1 = merge(line1, line2);
    assert(m1.size() == line1.size() + line2.size());
    assert(m1[0] == line1[0]);
    assert(m1[1] == line1[1]);
    assert(m1[2] == line2[1]);
    assert(m1[3] == line2[0]);
}
