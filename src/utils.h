#ifndef UTILS_H
#define UTILS_H

#include "point.h"

#include <vector>
#include <cstdlib>

enum TrRot { CW, C_CW, COLLIN };

/*
 * S---------->Q
 * |    v
 * |u
 * |
 * v
 * P
 */
TrRot getRotation(Point const& s, Point const& p, Point const& q);

bool azimuthLeq(Point const& p0, Point const& p1, Point const& p2);

bool isLine(std::vector<Point> const& poly);

#endif // UTILS_H
