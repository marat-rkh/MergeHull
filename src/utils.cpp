#include "utils.h"

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

bool azimuthLeq(Point const& p0, Point const& p1, Point const& p2) { return getRotation(p0, p1, p2) != CW; }

bool isLine(std::vector<Point> const& poly) {
    if(poly.size() < 3) {
        return true;
    }
    for(size_t i = 0; i != poly.size() - 2; ++i) {
        if(getRotation(poly[i], poly[i + 1], poly[i + 2]) != COLLIN) {
            return false;
        }
    }
    return true;
}
