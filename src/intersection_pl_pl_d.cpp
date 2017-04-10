//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// polygon/polygon
template auto intersection(polygon<double> const& p1, polygon<double> const& p2)
    ->std::vector<polygon<double>>;

}}}
