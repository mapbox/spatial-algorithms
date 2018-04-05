#pragma once

namespace mapbox {
namespace geometry {
namespace algorithms {

struct closest_point_info
{
    closest_point_info()
        : x(), y(), distance(-1) {}
    closest_point_info(double x_, double y_, double distance_)
        : x(x_),
          y(y_),
          distance(distance_) {}
    double x;
    double y;
    double distance;
};

template <typename T1, typename T2>
closest_point_info closest_point(T1 const& geom, mapbox::geometry::point<T2> const& pt);
}
}
}
