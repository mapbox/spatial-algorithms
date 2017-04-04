//

#include <mapbox/geometry/algorithms/predicates/disjoint_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {
// point
template bool disjoint(point<double> const&, point<double> const&);
template bool disjoint(point<double> const&, line_string<double> const&);
template bool disjoint(point<double> const&, polygon<double> const&);
template bool disjoint(point<double> const&, multi_point<double> const&);
template bool disjoint(point<double> const&, geometry<double> const&);
// line_sting
template bool disjoint(line_string<double> const&, point<double> const&);
template bool disjoint(line_string<double> const&, line_string<double> const&);
template bool disjoint(line_string<double> const&, polygon<double> const&);
template bool disjoint(line_string<double> const&, multi_point<double> const&);
template bool disjoint(line_string<double> const&, geometry<double> const&);
// polygon
template bool disjoint(polygon<double> const&, point<double> const&);
template bool disjoint(polygon<double> const&, line_string<double> const&);
template bool disjoint(polygon<double> const&, polygon<double> const&);
template bool disjoint(polygon<double> const&, multi_point<double> const&);
template bool disjoint(polygon<double> const&, geometry<double> const&);
// multi_point
template bool disjoint(multi_point<double> const&, point<double> const&);
template bool disjoint(multi_point<double> const&, line_string<double> const&);
template bool disjoint(multi_point<double> const&, polygon<double> const&);
template bool disjoint(multi_point<double> const&, multi_point<double> const&);
template bool disjoint(multi_point<double> const&, geometry<double> const&);
// geometry
template bool disjoint(geometry<double>const&, point<double> const&);
template bool disjoint(geometry<double>const&, line_string<double> const&);
template bool disjoint(geometry<double>const&, polygon<double> const&);
template bool disjoint(geometry<double>const&, multi_point<double> const&);
template bool disjoint(geometry<double>const&, geometry<double> const&);

}}}
