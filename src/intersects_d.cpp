//

#include <mapbox/geometry/algorithms/predicates/intersects_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {
// point
template bool intersects(point<double> const&, point<double> const&);
template bool intersects(point<double> const&, line_string<double> const&);
template bool intersects(point<double> const&, polygon<double> const&);
template bool intersects(point<double> const&, multi_point<double> const&);
// line_sting
template bool intersects(line_string<double> const&, point<double> const&);
template bool intersects(line_string<double> const&, line_string<double> const&);
template bool intersects(line_string<double> const&, polygon<double> const&);
template bool intersects(line_string<double> const&, multi_point<double> const&);
// polygon
template bool intersects(polygon<double> const&, point<double> const&);
template bool intersects(polygon<double> const&, line_string<double> const&);
template bool intersects(polygon<double> const&, polygon<double> const&);
template bool intersects(polygon<double> const&, multi_point<double> const&);
// geometry
template bool intersects(geometry<double> const&, geometry<double> const&);

}}}
