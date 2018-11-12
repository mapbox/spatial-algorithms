//
#include <mapbox/geometry/algorithms/closest_point_impl.hpp>


namespace mapbox { namespace geometry { namespace algorithms {

template closest_point_info closest_point(empty const&, point<double> const&);
template closest_point_info closest_point(geometry<double> const&, point<double> const&);
template closest_point_info closest_point(point<double> const&, point<double> const&);
template closest_point_info closest_point(line_string<double> const&, point<double> const&);
template closest_point_info closest_point(polygon<double>const&, point<double> const&);
template closest_point_info closest_point(multi_point<double>const&, point<double> const&);
template closest_point_info closest_point(multi_line_string<double>const&, point<double> const&);
template closest_point_info closest_point(multi_polygon<double>const&, point<double> const&);
template closest_point_info closest_point(geometry_collection<double> const&, point<double> const&);

}  // namespace algorithms
}  // namespace geometry
}  // namespace mapbox
