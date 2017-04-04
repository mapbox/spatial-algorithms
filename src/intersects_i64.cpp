//

#include <mapbox/geometry/algorithms/predicates/intersects_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

template bool intersects(point<std::int64_t> const&, point<std::int64_t> const&);
template bool intersects(point<std::int64_t> const&, line_string<std::int64_t> const&);
template bool intersects(point<std::int64_t> const&, polygon<std::int64_t> const&);
template bool intersects(point<std::int64_t> const&, multi_point<std::int64_t> const&);
// line_sting
template bool intersects(line_string<std::int64_t> const&, point<std::int64_t> const&);
template bool intersects(line_string<std::int64_t> const&, line_string<std::int64_t> const&);
template bool intersects(line_string<std::int64_t> const&, polygon<std::int64_t> const&);
template bool intersects(line_string<std::int64_t> const&, multi_point<std::int64_t> const&);
// polygon
template bool intersects(polygon<std::int64_t> const&, point<std::int64_t> const&);
template bool intersects(polygon<std::int64_t> const&, line_string<std::int64_t> const&);
template bool intersects(polygon<std::int64_t> const&, polygon<std::int64_t> const&);
template bool intersects(polygon<std::int64_t> const&, multi_point<std::int64_t> const&);
// geometry
template bool intersects(geometry<std::int64_t> const&, geometry<std::int64_t> const&);
}}}
