#include <mapbox/geometry.hpp>
#include <mapbox/geometry/box.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/intersection.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

template <typename Geometry1, typename Geometry2>
auto intersection(Geometry1 const&, Geometry2 const&)
    ->typename std::vector<typename detail::intersection_value_type<Geometry1, Geometry2>::type>
{
    //using value_type = typename detail::intersection_value_type<Geometry1, Geometry2>::type;
    //return std::vector<value_type>();
    throw std::runtime_error("Not supported");
}

// point/point
template <typename CoordinateType>
auto intersection(point<CoordinateType> const& p1, point<CoordinateType> const& p2)
    ->std::vector<point<CoordinateType>>
{
    std::vector<point<CoordinateType>> result;
    boost::geometry::intersection(p1, p2, result);
    return result;
}

// line_string/line_string
template <typename CoordinateType>
auto intersection(line_string<CoordinateType> const& l1, line_string<CoordinateType> const& l2)
    ->std::vector<line_string<CoordinateType>>
{
    std::vector<line_string<CoordinateType>> result;
    boost::geometry::intersection(l1, l2, result);
    return result;
}

// polygon/polygon
template <typename CoordinateType>
auto intersection(polygon<CoordinateType> const& poly1, polygon<CoordinateType> const& poly2)
    ->std::vector<polygon<CoordinateType>>
{
    std::vector<polygon<CoordinateType>> result;
    boost::geometry::intersection(poly1, poly2, result);
    return result;
}

// box/polygon
template <typename CoordinateType>
auto intersection(box<CoordinateType> const& b, polygon<CoordinateType> const& poly2)
    ->std::vector<polygon<CoordinateType>>
{
    std::vector<polygon<CoordinateType>> result;
    boost::geometry::intersection(poly2, b, result);
    return result;
}

// polygon/box
template <typename CoordinateType>
auto intersection(polygon<CoordinateType> const& poly1, box<CoordinateType> const& b)
    ->std::vector<polygon<CoordinateType>>
{
    std::vector<polygon<CoordinateType>> result;
    boost::geometry::intersection(poly1, b, result);
    return result;
}

}}}
