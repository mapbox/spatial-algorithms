#pragma once

//#include <mapbox/geometry/point.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

//using coordinate_type = double;

template <typename T>
struct closest_point_result
{
    using coordinate_type = T;
    coordinate_type x{};
    coordinate_type y{};
    double distance = -1.0;
};

template <typename T>
using result_type = closest_point_result<T>;

template <typename T1, typename T2>
auto closest_point(T1 const& geom, mapbox::geometry::point<T2> const& pt)->result_type<T2>;

}}}
