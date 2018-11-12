//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// point/point
template auto intersection(point<std::int64_t> const& p1, point<std::int64_t> const& p2)
    ->std::vector<point<std::int64_t>>;

} // namespace algorithms
} // namespace geometry
} // namespace mapbox
