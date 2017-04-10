//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// geometry/geometry
template auto intersection(geometry<std::int64_t> const& g1, geometry<std::int64_t> const& g2)
    ->typename std::vector<typename detail::intersection_value_type<geometry<std::int64_t>,geometry<std::int64_t>>::type>;

}}}
