//

#include <mapbox/geometry/algorithms/predicates/disjoint_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {
// point
template bool disjoint(point<std::int64_t> const&, point<std::int64_t> const&);
template bool disjoint(point<std::int64_t> const&, line_string<std::int64_t> const&);
template bool disjoint(point<std::int64_t> const&, polygon<std::int64_t> const&);
template bool disjoint(point<std::int64_t> const&, multi_point<std::int64_t> const&);
template bool disjoint(point<std::int64_t> const&, geometry<std::int64_t> const&);
// line_sting
template bool disjoint(line_string<std::int64_t> const&, point<std::int64_t> const&);
template bool disjoint(line_string<std::int64_t> const&, line_string<std::int64_t> const&);
template bool disjoint(line_string<std::int64_t> const&, polygon<std::int64_t> const&);
template bool disjoint(line_string<std::int64_t> const&, multi_point<std::int64_t> const&);
template bool disjoint(line_string<std::int64_t> const&, geometry<std::int64_t> const&);
// polygon
template bool disjoint(polygon<std::int64_t> const&, point<std::int64_t> const&);
template bool disjoint(polygon<std::int64_t> const&, line_string<std::int64_t> const&);
template bool disjoint(polygon<std::int64_t> const&, polygon<std::int64_t> const&);
template bool disjoint(polygon<std::int64_t> const&, multi_point<std::int64_t> const&);
template bool disjoint(polygon<std::int64_t> const&, geometry<std::int64_t> const&);
// multi_point
template bool disjoint(multi_point<std::int64_t> const&, point<std::int64_t> const&);
template bool disjoint(multi_point<std::int64_t> const&, line_string<std::int64_t> const&);
template bool disjoint(multi_point<std::int64_t> const&, polygon<std::int64_t> const&);
template bool disjoint(multi_point<std::int64_t> const&, multi_point<std::int64_t> const&);
template bool disjoint(multi_point<std::int64_t> const&, geometry<std::int64_t> const&);
// geometry
template bool disjoint(geometry<std::int64_t>const&, point<std::int64_t> const&);
template bool disjoint(geometry<std::int64_t>const&, line_string<std::int64_t> const&);
template bool disjoint(geometry<std::int64_t>const&, polygon<std::int64_t> const&);
template bool disjoint(geometry<std::int64_t>const&, multi_point<std::int64_t> const&);
template bool disjoint(geometry<std::int64_t>const&, geometry<std::int64_t> const&);

}}}
