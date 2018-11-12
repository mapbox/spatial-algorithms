//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// point/point
template auto intersection(point<double> const& p1, point<double> const& p2)
    ->std::vector<point<double>>;

} // namespace algorithms
} // namespace geometry
} // namespace mapbox
