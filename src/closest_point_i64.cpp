//
#include <mapbox/geometry/algorithms/closest_point_impl.hpp>


namespace mapbox { namespace geometry { namespace algorithms {

template closest_point_info closest_point(geometry<std::int64_t> const&, point<std::int64_t> const&);
template closest_point_info closest_point(point<std::int64_t> const&, point<std::int64_t> const&);
template closest_point_info closest_point(line_string<std::int64_t> const&, point<std::int64_t> const&);
template closest_point_info closest_point(polygon<std::int64_t>const&, point<std::int64_t> const&);
template closest_point_info closest_point(multi_point<std::int64_t>const&, point<std::int64_t> const&);
template closest_point_info closest_point(multi_line_string<std::int64_t>const&, point<std::int64_t> const&);
template closest_point_info closest_point(multi_polygon<std::int64_t>const&, point<std::int64_t> const&);
template closest_point_info closest_point(geometry_collection<std::int64_t> const&, point<std::int64_t> const&);

}}}
