//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// geometry/geometry
template auto intersection(geometry<double> const& g1, geometry<double> const& g2)
    ->typename std::vector<typename detail::intersection_value_type<geometry<double>,geometry<double>>::type>;

} // namespace algorithms
} // namespace geometry
} // namespace mapbox
