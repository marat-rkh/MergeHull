#include "merge.h"
#include "utils.h"

#include <cassert>
#include <algorithm>

using std::vector;
using std::pair;
using geom::structures::point_type;

pair<size_t, size_t> tangency_pts(point_type const &p, vector<point_type> const& poly) {
    vector<size_t> res_buf;
    TrRot lastRot = get_rotation(p, poly[0], poly[1]);
    for(size_t i = 1; i != poly.size() + 1; ++i) {
        size_t i_mod = i % poly.size();
        size_t ii_mod = (i + 1) % poly.size();
        TrRot rot = get_rotation(p, poly[i_mod], poly[ii_mod]);
        if(rot != lastRot && rot != COLLIN) {
            res_buf.push_back(i_mod);
        }
        lastRot = rot;
    }
    assert(res_buf.size() == 2);
    return std::make_pair(res_buf[0], res_buf[1]);
}

bool chainIsIncreasing(point_type const& p, vector<point_type> const& chain) {
    for(size_t i = 0; i != chain.size() - 1; ++i) {
        if(get_rotation(p, chain[i], chain[i + 1]) == C_CW) {
            return true;
        }
    }
    return false;
}

vector<point_type> get_incr_chain(point_type const& p, vector<point_type> const& poly) {
    pair<size_t, size_t> tps = tangency_pts(p, poly);
    vector<point_type> chain1, chain2;
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

vector<point_type> rotate_line_ccw(point_type const& p, vector<point_type> const& line) {
    TrRot rot = get_rotation(p, line[0], line[1]);
    if(rot == CW) {
        vector<point_type> rotated_line(line);
        std::reverse(rotated_line.begin(), rotated_line.end());
        return rotated_line;
    }
    return line;
}

vector<point_type> getSorted(size_t lmostPtInd, vector<point_type> const& lPoly, vector<point_type> const& rPoly) {
    vector<point_type> sorted;
    sorted.push_back(lPoly[lmostPtInd]);
    size_t il = 1;
    size_t ir = 0;
    while(il != lPoly.size() && ir != rPoly.size()) {
        size_t ilMod = (il + lmostPtInd) % lPoly.size();
        if(azimuth_leq(lPoly[lmostPtInd], lPoly[ilMod], rPoly[ir])) {
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

vector<point_type> merge(vector<point_type> const& poly1, vector<point_type> const& poly2) {
    auto fstXLeqYGreater = [](point_type const& a, point_type const& b){ return a.x < b.x || (a.x == b.x && a.y > b.y); };
    vector<point_type>::const_iterator min1 = std::min_element(poly1.begin(), poly1.end(), fstXLeqYGreater);
    vector<point_type>::const_iterator min2 = std::min_element(poly2.begin(), poly2.end(), fstXLeqYGreater);
    if(fstXLeqYGreater(*min1, *min2)) {
        vector<point_type> const& normPoly = is_line(poly2) ? rotate_line_ccw(*min1, poly2): get_incr_chain(*min1, poly2);
        return getSorted(min1 - poly1.begin(), poly1, normPoly);
    }
    vector<point_type> const& normPoly = is_line(poly1) ? rotate_line_ccw(*min2, poly1) : get_incr_chain(*min2, poly1);
    return getSorted(min2 - poly2.begin(), poly2, normPoly);
}
