#include "utils.h"
#include <iostream>

using geom::structures::point_type;
using geom::structures::contour_type;

TrRot get_rotation(point_type const& s, point_type const& p, point_type const& q) {
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

bool azimuth_leq(point_type const& p0, point_type const& p1, point_type const& p2) {
    return get_rotation(p0, p1, p2) != CW;
}

bool is_line(std::vector<point_type> const& poly) {
    if(poly.size() < 3) {
        return true;
    }
    for(size_t i = 0; i != poly.size() - 2; ++i) {
        if(get_rotation(poly[i], poly[i + 1], poly[i + 2]) != COLLIN) {
            return false;
        }
    }
    return true;
}

namespace geom {
namespace structures {

    contour_type::contour_type(std::vector<point_type> && pts)
        : pts_(std::move(pts))
    {}

    struct contour_builder_type
    {
        void add_point(point_type const & pt)
        {
            pts_.push_back(pt);
        }

        contour_type get_result()
        {
            return contour_type(std::move(pts_));
        }

    private:
        std::vector<point_type> pts_;
    };
}}

contour_type to_contour_type(std::vector<point_type> const& poly) {
    geom::structures::contour_builder_type builder;
    for(size_t i = 0; i != poly.size(); ++i) {
        builder.add_point(poly[i]);
    }
    return builder.get_result();
}

void print_conv_hull(std::vector<geom::structures::point_type> conv_hull) {
    std::cout << "Convex hull:\n";
    for(size_t i = 0; i != conv_hull.size(); ++i) {
        std::cout << '(' << conv_hull[i].x <<", " << conv_hull[i].y << ")\n";
    }
}
