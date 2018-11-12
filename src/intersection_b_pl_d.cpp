//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// polygon/polygon
template auto intersection(box<double> const& b, polygon<double> const& poly2)
    ->std::vector<polygon<double>>;

} // namespace algorithms
} // namespace geometry
} // namespace mapbox
