#include "merge_hull.h"
#include "utils.h"
#include "merge.h"
#include "point.h"

#include <cmath>

vector<Point> grahamScan(vector<Point> const& ptsSet) {
    vector<Point> res = {ptsSet[0], ptsSet[1]};
    for(size_t i = 2; i != ptsSet.size(); ++i) {
        if(getRotation(res[res.size() - 2], res.back(), ptsSet[i]) == CW) {
            res.pop_back();
            while(res.size() != 1) {
                if(getRotation(res[res.size() - 2], res.back(), ptsSet[i]) != CW) {
                    break;
                }
                res.pop_back();
            }
        }
        res.push_back(ptsSet[i]);
    }
    return res;
}

vector<Point> removeBeams(vector<Point> const& pts_set) {
    vector<size_t> bad_pts_ind;
    for(size_t i = 1; i != pts_set.size() - 1; ++i) {
        if(getRotation(pts_set[0], pts_set[i], pts_set[i + 1]) == COLLIN) {
            bad_pts_ind.push_back(i);
            bad_pts_ind.push_back(i + 1);
        } else if(!bad_pts_ind.empty() && bad_pts_ind.back() != 0) {
            bad_pts_ind.push_back(0);
        }
    }
    vector<size_t> rm_indexes;
    size_t max_dist = 0;
    auto dist = [&](Point const& p) { return std::pow(p.x - pts_set[0].x, 2) + std::pow(p.y - pts_set[0].y, 2); };
    for(size_t i = 0; i != bad_pts_ind.size(); ++i) {
        if(bad_pts_ind[i] != 0) {
            size_t cur_dist = dist(pts_set[bad_pts_ind[i]]);
            if(cur_dist <= max_dist) {
                rm_indexes.push_back(i);
            } else {
                max_dist = cur_dist;
            }
        } else {
            max_dist = 0;
        }
    }
    vector<Point> beams_free;
    size_t rm_pos = 0;
    for(size_t i = 0; i != pts_set.size(); ++i) {
        if(i == rm_indexes[rm_pos]) {
            ++rm_pos;
            continue;
        }
        beams_free.push_back(pts_set[i]);
    }
    return beams_free;
}

// todo: check input contract and handle special cases !!!
/*
 * [beg, end)
 */
vector<Point> mergeHull(vector<Point> const& pts_set, size_t beg, size_t end) {
    if(end - beg < 4) {
        vector<Point> conv_hull;
        for(size_t i = beg; i != end; ++i) {
            conv_hull.push_back(pts_set[i]);
        }
        if(conv_hull.size() == 3 && getRotation(conv_hull[0], conv_hull[1], conv_hull[2]) == CW) {
            Point buf(conv_hull[1]);
            conv_hull[1] = conv_hull[2];
            conv_hull[2] = buf;
        }
        return conv_hull;
    }
    size_t m = (end - beg) / 2;
    vector<Point> fst_ch = mergeHull(pts_set, beg, m);
    vector<Point> snd_ch = mergeHull(pts_set, m, end);
    vector<Point> sorted = merge(fst_ch, snd_ch);
    vector<Point> ch = grahamScan(sorted);
    if(ch.size() > 4) {
        ch = grahamScan(removeBeams(ch));
    }
    return ch;
}
