#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cstdlib>

#include "geom/primitives/contour.h"

using geom::structures::point_type;
using geom::structures::contour_type;

enum TrRot { CW, C_CW, COLLIN };

/*
 * S---------->Q
 * |    v
 * |u
 * |
 * v
 * P
 */
TrRot get_rotation(point_type const& s, point_type const& p, point_type const& q);

bool azimuth_leq(point_type const& p0, point_type const& p1, point_type const& p2);

bool is_line(std::vector<point_type> const& poly);

contour_type to_contour_type(std::vector<point_type> const& poly);

void print_conv_hull(std::vector<point_type> conv_hull);

#endif // UTILS_H
