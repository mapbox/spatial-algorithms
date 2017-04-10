//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// polygon/polygon
template auto intersection(box<std::int64_t> const& b, polygon<std::int64_t> const& poly2)
    ->std::vector<polygon<std::int64_t>>;

}}}
