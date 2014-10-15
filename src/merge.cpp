#include "merge.h"
#include "point.h"
#include "utils.h"
#include "split_poly.h"

#include <algorithm>

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
    auto fstXLeqYGreater = [](Point const& a, Point const& b){ return a.x < b.x || a.x == b.x && a.y > b.y; };
    vector<Point>::const_iterator min1 = std::min_element(poly1.begin(), poly1.end(), fstXLeqYGreater);
    vector<Point>::const_iterator min2 = std::min_element(poly2.begin(), poly2.end(), fstXLeqYGreater);
    if(fstXLeqYGreater(*min1, *min2)) {
        vector<Point> const& normPoly = isLine(poly2) ? makeLineCcwRotated(*min1, poly2): getIncreasingChain(*min1, poly2);
        return getSorted(min1 - poly1.begin(), poly1, normPoly);
    }
    vector<Point> const& normPoly = isLine(poly1) ? makeLineCcwRotated(*min2, poly1) : getIncreasingChain(*min2, poly1);
    return getSorted(min2 - poly2.begin(), poly2, normPoly);
}
