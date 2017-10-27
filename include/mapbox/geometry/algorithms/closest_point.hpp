#pragma once

namespace mapbox { namespace geometry { namespace algorithms {

struct closest_point_info
{
    closest_point_info()
        : x(), y(), comparable_distance(-1) {}
    closest_point_info(double x_, double y_, double comparable_distance_)
        : x(x_),
          y(y_),
          comparable_distance(comparable_distance_) {}
    double x;
    double y;
    double comparable_distance;
};

template <typename T1, typename T2>
closest_point_info closest_point(T1 const& geom, mapbox::geometry::point<T2> const& pt);
}}}
