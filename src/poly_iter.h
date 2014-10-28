#ifndef POLY_ITER_H
#define POLY_ITER_H

#include <vector>
#include "geom/primitives/point.h"
#include <cassert>

using std::vector;
using geom::structures::point_type;

// not used for now
class poly_iter {
public:
    poly_iter(vector<point_type> const& poly, size_t iters_num, size_t start_pos)
        : poly_(poly)
        , iters_num_(iters_num)
        , cur_pos_(start_pos)
    {
        assert(start_pos < poly.size());
    }

    bool has_next() { return iters_num_ != 0; }
    size_t next() {
        size_t next = cur_pos_ % poly_.size();
        ++cur_pos_;
        --iters_num_;
        return next;
    }
    size_t neighbour(size_t base, size_t offset) { return (base + offset) % poly_.size(); }

private:
    vector<point_type> const& poly_;
    size_t iters_num_;
    size_t cur_pos_;
};

#endif // POLY_ITER_H
