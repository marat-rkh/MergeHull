#ifndef MERGE_H
#define MERGE_H

#include <vector>
#include <utility>
#include <cstdlib>

#include "geom/primitives/point.h"

using std::vector;
using std::pair;
using geom::structures::point_type;

vector<point_type> merge(vector<point_type> const& poly1, vector<point_type> const& poly2);

/*
 * Removes all the intermidiate points of the line
 */
vector<point_type> simplify_line(vector<point_type> const& line);

/*
 * Returns tangency points of the polynom passed elatively to the point p
 * Contract:
 * Poly must have at least 3 vertices, be convex and not be a line.
 * Point must be outer point of the poly
 */
pair<size_t, size_t> tangency_pts(point_type const &p, vector<point_type> const& poly);

/*
 * Returns chain that increases relatively to passed point p. Chain is considered
 * increasing if iterating it's vertices their azimuth increases monotonically
 * relatively to the point.
 * Contract:
 * Poly must have at least 3 vertices, be convex and not be a line.
 * Point must be outer point of the poly
 */
vector<point_type> get_incr_chain(point_type const& p, vector<point_type> const& poly);

/*
 * Rotates line so that it becomes counterclockwise rotated relatevily to passed point p.
 * If line is collinear to the point it will be returned unchanged
 */
vector<point_type> rotate_line_ccw(point_type const& p, vector<point_type> const& line);

#endif
