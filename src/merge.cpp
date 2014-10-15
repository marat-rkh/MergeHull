#include "merge.h"
#include "point.h"
#include "utils.h"

#include <cassert>
#include <algorithm>

using std::vector;
using std::pair;

pair<size_t, size_t> tangencyPoints(Point const &p, vector<Point> const& poly) {
    vector<size_t> res_buf;
    TrRot lastRot = getRotation(p, poly[0], poly[1]);
    for(size_t i = 1; i != poly.size() + 1; ++i) {
        size_t i_mod = i % poly.size();
        size_t ii_mod = (i + 1) % poly.size();
        TrRot rot = getRotation(p, poly[i_mod], poly[ii_mod]);
        if(rot != lastRot && rot != COLLIN) {
            res_buf.push_back(i_mod);
        }
        lastRot = rot;
    }
    assert(res_buf.size() == 2);
    return std::make_pair(res_buf[0], res_buf[1]);
}

bool chainIsIncreasing(Point const& p, vector<Point> const& chain) {
    for(size_t i = 0; i != chain.size() - 1; ++i) {
        if(getRotation(p, chain[i], chain[i + 1]) == C_CW) {
            return true;
        }
    }
    return false;
}

vector<Point> getIncreasingChain(Point const& p, vector<Point> const& poly) {
    pair<size_t, size_t> tps = tangencyPoints(p, poly);
    vector<Point> chain1, chain2;
    for(size_t i = tps.first; i != tps.second; i = (i + 1) % poly.size()) {
        chain1.push_back(poly[i]);
    }
    chain1.push_back(poly[tps.second]);
    for(size_t i = tps.second; i != tps.first; i = (i + 1) % poly.size()) {
        chain2.push_back(poly[i]);
    }
    chain2.push_back(poly[tps.first]);
    return chainIsIncreasing(p, chain1) ? chain1 : chain2;
}

vector<Point> makeLineCcwRotated(Point const& p, vector<Point> const& line) {
    TrRot rot = getRotation(p, line[0], line[1]);
    if(rot == CW) {
        vector<Point> rotated_line(line);
        std::reverse(rotated_line.begin(), rotated_line.end());
        return rotated_line;
    }
    return line;
}

vector<Point> getSorted(size_t lmostPtInd, vector<Point> const& lPoly, vector<Point> const& rPoly) {
    vector<Point> sorted;
    sorted.push_back(lPoly[lmostPtInd]);
    size_t il = 1;
    size_t ir = 0;
    while(il != lPoly.size() && ir != rPoly.size()) {
        size_t ilMod = (il + lmostPtInd) % lPoly.size();
        if(azimuthLeq(lPoly[lmostPtInd], lPoly[ilMod], rPoly[ir])) {
            sorted.push_back(lPoly[ilMod]);
            ++il;
        } else {
            sorted.push_back(rPoly[ir]);
            ++ir;
        }
    }
    for(; il != lPoly.size(); ++il) {
        size_t ilMod = (il + lmostPtInd) % lPoly.size();
        sorted.push_back(lPoly[ilMod]);
    }
    for(; ir != rPoly.size(); ++ir) {
        sorted.push_back(rPoly[ir]);
    }
    return sorted;
}

vector<Point> merge(vector<Point> const& poly1, vector<Point> const& poly2) {
    auto fstXLeqYGreater = [](Point const& a, Point const& b){ return a.x < b.x || (a.x == b.x && a.y > b.y); };
    vector<Point>::const_iterator min1 = std::min_element(poly1.begin(), poly1.end(), fstXLeqYGreater);
    vector<Point>::const_iterator min2 = std::min_element(poly2.begin(), poly2.end(), fstXLeqYGreater);
    if(fstXLeqYGreater(*min1, *min2)) {
        vector<Point> const& normPoly = isLine(poly2) ? makeLineCcwRotated(*min1, poly2): getIncreasingChain(*min1, poly2);
        return getSorted(min1 - poly1.begin(), poly1, normPoly);
    }
    vector<Point> const& normPoly = isLine(poly1) ? makeLineCcwRotated(*min2, poly1) : getIncreasingChain(*min2, poly1);
    return getSorted(min2 - poly2.begin(), poly2, normPoly);
}
