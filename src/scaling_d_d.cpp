//
#include <mapbox/geometry/algorithms/scaling_impl.hpp>


namespace mapbox { namespace geometry { namespace algorithms {

template point<double> scale(point<double> const&, double);
template multi_point<double> scale(multi_point<double> const&, double);
template line_string<double> scale(line_string<double> const&, double);
template multi_line_string<double> scale(multi_line_string<double> const&, double);
template polygon<double> scale(polygon<double> const&, double);
template multi_polygon<double> scale(multi_polygon<double> const&, double);
template geometry<double> scale(geometry<double> const&, double);

}  // namespace algorithms
}  // namespace geometry
}  // namespace mapbox
