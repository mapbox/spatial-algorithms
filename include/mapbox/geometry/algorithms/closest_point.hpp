#pragma once

namespace mapbox { namespace geometry { namespace algorithms {

template <typename T>
struct closest_point_info
{
    using coordinate_type = T;
    coordinate_type x{};
    coordinate_type y{};
    double distance = -1.0;
};

template <typename T1, typename T2>
auto closest_point(T1 const& geom, mapbox::geometry::point<T2> const& pt)->closest_point_info<T2>;

}}}
