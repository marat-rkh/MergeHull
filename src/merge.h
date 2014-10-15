#ifndef MERGE_H
#define MERGE_H

#include <vector>
#include <utility>
#include <cstdlib>

#include "point.h"

using std::vector;
using std::pair;

vector<Point> merge(vector<Point> const& poly1, vector<Point> const& poly2);

/*
 * Returns tangency points of the polynom passed elatively to the point p
 * Contract:
 * Poly must have at least 3 vertices, be convex and not be a line.
 * Point must be outer point of the poly
 */
pair<size_t, size_t> tangencyPoints(Point const &p, vector<Point> const& poly);

/*
 * Returns chain that increases relatively to passed point p. Chain is considered
 * increasing if iterating it's vertices their azimuth increases monotonically
 * relatively to the point.
 * Contract:
 * Poly must have at least 3 vertices, be convex and not be a line.
 * Point must be outer point of the poly
 */
vector<Point> getIncreasingChain(Point const& p, vector<Point> const& poly);

/*
 * Rotates line so that it becomes counterclockwise rotated relatevily to passed point p.
 * If line is collinear to the point it will be returned unchanged
 */
vector<Point> makeLineCcwRotated(Point const& p, vector<Point> const& line);


#endif
