#pragma once

#include <mapbox/geometry/point.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

template <typename T>
struct closest_point_info
{
    using coordinate_type = T;
    closest_point_info()
        : x(),y(),distance(-1) {}
    closest_point_info(coordinate_type x_, coordinate_type y_, double distance_)
        : x(x_),
          y(y_),
          distance(distance_) {}
    coordinate_type x;
    coordinate_type y;
    double distance;
};

template <typename T1, typename T2>
auto closest_point(T1 const& geom, mapbox::geometry::point<T2> const& pt)->closest_point_info<T2>;

}}}
