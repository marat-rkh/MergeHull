#include "merge_hull.h"
#include "utils.h"
#include "merge.h"

#include <cmath>
#include <iostream>
#include <algorithm>

using geom::structures::point_type;

/*
 * Rotates triangle counterclockwise
 */
void rotate_triangle_ccw(vector<point_type> & conv_hull) {
    point_type buf(conv_hull[1]);
    conv_hull[1] = conv_hull[2];
    conv_hull[2] = buf;
}

vector<point_type> graham_scan(vector<point_type> const& ptsSet) {
    vector<point_type> res = {ptsSet[0], ptsSet[1]};
    for(size_t i = 2; i != ptsSet.size(); ++i) {
        if(get_rotation(res[res.size() - 2], res.back(), ptsSet[i]) == CW) {
            res.pop_back();
            while(res.size() != 1) {
                if(get_rotation(res[res.size() - 2], res.back(), ptsSet[i]) != CW) {
                    break;
                }
                res.pop_back();
            }
        }
        res.push_back(ptsSet[i]);
    }
    return res;
}

/*
 * Returns vector of positions in pts_set, sequences of positions are separated by 0.
 * This sequences consist of at least 2 positions. Points in pts_set in this sequential
 * positions form a line with first point of pts_set.
 */
vector<size_t> bad_pts_positions(vector<point_type> const& pts_set) {
    vector<size_t> bad_pts_pos;
    for(size_t i = 1; i != pts_set.size() - 1; ++i) {
        if(get_rotation(pts_set[0], pts_set[i], pts_set[i + 1]) == COLLIN) {
            bad_pts_pos.push_back(i);
            bad_pts_pos.push_back(i + 1);
        } else if(!bad_pts_pos.empty() && bad_pts_pos.back() != 0) {
            bad_pts_pos.push_back(0);
        }
    }
    bad_pts_pos.erase(std::unique(bad_pts_pos.begin(), bad_pts_pos.end()), bad_pts_pos.end());
    return bad_pts_pos;
}

/*
 * Finds positions in pts_set which should be removed to avoid beams problem
 */
vector<size_t> positions_to_remove(vector<point_type> const& pts_set) {
    vector<size_t> const& bad_pts_pos = bad_pts_positions(pts_set);
    if(bad_pts_pos.empty()) {
        return bad_pts_pos;
    }
    vector<size_t> pos_to_rm;
    auto fdist = [&](point_type const& p) {
        return std::pow(p.x - pts_set[0].x, 2) + std::pow(p.y - pts_set[0].y, 2);
    };
    size_t max_dist = 0;
    size_t max_dist_pos = 0;
    for(size_t i = 0; i != bad_pts_pos.size(); ++i) {
        if(bad_pts_pos[i] != 0) {
            size_t cur_dist = fdist(pts_set[bad_pts_pos[i]]);
            if(cur_dist <= max_dist) {
                pos_to_rm.push_back(bad_pts_pos[i]);
            } else {
                max_dist = cur_dist;
                if(max_dist_pos != 0) {
                    pos_to_rm.push_back(max_dist_pos);
                }
                max_dist_pos = bad_pts_pos[i];
            }
        } else {
            max_dist = 0;
            max_dist_pos = 0;
        }
    }
    return pos_to_rm;
}

/*
 * Removes beams from pts_set. Beam is a set of points collinear to the first
 * (in this implementation it is leftmost and highest point) point in pts_set.
 * In some situations graham scan can not detect them and produce wrong convex hull.
 * Example:
 * (-150, 150)
 * (-100, -100)
 * (100, -100)
 * (0, 0)
 * (150, -150)
 * These points are sorted by azimuth but 4 of them are collinear (lie in one beam)
 * so it produces the problem.
 */
vector<point_type> remove_beams(vector<point_type> const& pts_set) {
    vector<size_t> pos_to_rm = positions_to_remove(pts_set);
    if(pos_to_rm.empty()) {
        return pts_set;
    }
    vector<point_type> beams_free;
    size_t rm_pos = 0;
    bool all_rms_done = false;
    for(size_t i = 0; i != pts_set.size(); ++i) {
        if(!all_rms_done && i == pos_to_rm[rm_pos]) {
            ++rm_pos;
            if(rm_pos == pos_to_rm.size()) {
                all_rms_done = true;
            }
            continue;
        }
        beams_free.push_back(pts_set[i]);
    }
    return beams_free;
}

vector<point_type> merge_hull(vector<point_type> const& pts_set, size_t beg, size_t end) {
    if(end - beg < 4) {
        vector<point_type> conv_hull;
        for(size_t i = beg; i != end; ++i) {
            conv_hull.push_back(pts_set[i]);
        }
        if(conv_hull.size() == 3 && get_rotation(conv_hull[0], conv_hull[1], conv_hull[2]) == CW) {
            rotate_triangle_ccw(conv_hull);
        }
        return conv_hull;
    }
    size_t m = (end - beg) / 2;
    vector<point_type> fst = merge_hull(pts_set, beg, beg + m);
    vector<point_type> snd = merge_hull(pts_set, beg + m, end);
    vector<point_type> sorted = merge(fst, snd);
    vector<point_type> conv_hull = graham_scan(sorted);
    if(conv_hull.size() > 4) {
        conv_hull = graham_scan(remove_beams(conv_hull));
    }
    return conv_hull;
}
