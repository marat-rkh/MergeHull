#ifndef MERGE_HULL_H
#define MERGE_HULL_H

#include <vector>
#include <cstdlib>

#include "geom/primitives/point.h"

using std::vector;
using geom::structures::point_type;

/*
 * Convex hull construction algorithm based on divide and conquer principle.
 * Note, that 'beg' is inclusive and 'end' is explusive: [beg, end)
 */
vector<point_type> merge_hull(vector<point_type> const& pts_set, size_t beg, size_t end);

#endif // MERGE_HULL_H
