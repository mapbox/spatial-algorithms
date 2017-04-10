#pragma once

#include <vector>

namespace mapbox { namespace geometry { namespace algorithms {

namespace detail {

template <typename Geometry1, typename Geometry2>
struct intersection_value_type {} ; // dummy

template <typename CoordinateType>
struct intersection_value_type<point<CoordinateType>, point<CoordinateType>>
{
    using type = point<CoordinateType>;
};

template <typename CoordinateType>
struct intersection_value_type<line_string<CoordinateType>, point<CoordinateType>>
{
    using type = point<CoordinateType>;
};

template <typename CoordinateType>
struct intersection_value_type<point<CoordinateType>, line_string<CoordinateType>>
{
    using type = point<CoordinateType>;
};

template <typename CoordinateType>
struct intersection_value_type<line_string<CoordinateType>, line_string<CoordinateType>>
{
    using type = line_string<CoordinateType>;
};

template <typename CoordinateType>
struct intersection_value_type<polygon<CoordinateType>, line_string<CoordinateType>>
{
    using type = line_string<CoordinateType>;
};

template <typename CoordinateType>
struct intersection_value_type<line_string<CoordinateType>, polygon<CoordinateType>>
{
    using type = line_string<CoordinateType>;
};

template <typename CoordinateType>
struct intersection_value_type<polygon<CoordinateType>, polygon<CoordinateType>>
{
    using type = polygon<CoordinateType>;
};

template <typename CoordinateType>
struct intersection_value_type<geometry<CoordinateType>, geometry<CoordinateType>>
{
    using type = geometry<CoordinateType>;
};
}

template <typename Geometry1, typename Geometry2>
auto intersection(Geometry1 const& g1, Geometry2 const& g2)
    ->typename std::vector<typename detail::intersection_value_type<Geometry1, Geometry2>::type>;

template <typename CoordinateType>
auto intersection(point<CoordinateType> const& p1, point<CoordinateType> const& p2)
    ->std::vector<point<CoordinateType>>;

template <typename CoordinateType>
auto intersection(point<CoordinateType> const& p1, line_string<CoordinateType> const& l2)
    ->std::vector<point<CoordinateType>>;

template <typename CoordinateType>
auto intersection(line_string<CoordinateType> const& l1, point<CoordinateType> const& p2)
    ->std::vector<point<CoordinateType>>;

template <typename CoordinateType>
auto intersection(line_string<CoordinateType> const& l1, line_string<CoordinateType> const& l2)
    ->std::vector<line_string<CoordinateType>> ;


template <typename CoordinateType>
auto intersection(polygon<CoordinateType> const& poly1, polygon<CoordinateType> const& poly2)
    ->std::vector<polygon<CoordinateType>> ;


}}}
