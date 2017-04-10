//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// polygon/polygon
template auto intersection(polygon<std::int64_t> const& p1, polygon<std::int64_t> const& p2)
    ->std::vector<polygon<std::int64_t>>;

}}}
