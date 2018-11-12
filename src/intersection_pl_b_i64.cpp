//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// polygon/polygon
template auto intersection(polygon<std::int64_t> const& poly1, box<std::int64_t> const& b)
    ->std::vector<polygon<std::int64_t>>;

} // namespace algorithms
} // namespace geometry
} // namespace mapbox
