#include "split_poly.h"

#include <cassert>

using std::vector;
using std::pair;

/*
 * S---------->Q
 * |    v
 * |u
 * |
 * v
 * P
 */
TrRot getRotation(Point const& s, Point const& p, Point const& q) {
    const long xu = p.x - s.x;
    const long yu = p.y - s.y;
    const long xv = q.x - s.x;
    const long yv = q.y - s.y;
    const long cross_prod = xu * yv - xv * yu;
    if(cross_prod > 0) {
        return C_CW;
    } else if (cross_prod < 0) {
        return CW;
    }
    return COLLIN;
}

/*
 * Contract:
 * Poly must have at least 3 vertices, be convex and not be a line.
 * Point must be outer point of the poly
 */
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

/*
 * Contract:
 * Poly must have at least 3 vertices, be convex and not be a line.
 * Point must be outer point of the poly
 */
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
