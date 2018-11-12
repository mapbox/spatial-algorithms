//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// line_string/line_string
template auto intersection(line_string<std::int64_t> const& p1, line_string<std::int64_t> const& p2)
    ->std::vector<line_string<std::int64_t>>;

} // namespace algorithms
} // namespace geometry
} // namespace mapbox
