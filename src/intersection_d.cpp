//
#include <mapbox/geometry/algorithms/intersection_impl.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

// point/point

//template auto intersection(point<double> const& g1, point<double> const& g2)
//    ->typename std::vector<typename detail::intersection_value_type<point<double>, point<double>>::type>;

template auto intersection(point<double> const& p1, point<double> const& p2)
    ->std::vector<point<double>>;

template auto intersection(line_string<double> const& p1, line_string<double> const& p2)
    ->std::vector<line_string<double>>;

template auto intersection(polygon<double> const& p1, polygon<double> const& p2)
    ->std::vector<polygon<double>>;

// geometry/geometry
template auto intersection(geometry<double> const& g1, geometry<double> const& g2)
    ->typename std::vector<typename detail::intersection_value_type<geometry<double>,geometry<double>>::type>;

}}}
