#ifndef SPLIT_POLY_H
#define SPLIT_POLY_H

#include <vector>
#include <utility>
#include <cstdlib>

#include "point.h"

using std::vector;
using std::pair;

enum TrRot { CW, C_CW, COLLIN };

TrRot getRotation(Point const& s, Point const& p, Point const& q);

/*
 * Contract:
 * Poly must have at least 3 vertices, be convex and not be a line.
 * Point must be outer point of the poly
 */
pair<size_t, size_t> tangencyPoints(Point const &p, vector<Point> const& poly);

/*
 * Returns chain
 */
vector<Point> getIncreasingChain(Point const& p, vector<Point> const& poly);

#endif // SPLIT_POLY_H
