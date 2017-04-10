//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// polygon/polygon
template auto intersection(polygon<double> const& poly1, box<double> const& b)
    ->std::vector<polygon<double>>;

}}}
