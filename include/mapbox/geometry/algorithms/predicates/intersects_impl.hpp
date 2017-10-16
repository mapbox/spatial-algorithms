//
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/detail/predicate_dispatcher.hpp>
#include <mapbox/geometry/algorithms/predicates/intersects.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

namespace detail {

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::point<CoordinateType>>
{
    static constexpr bool value = true;
};

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::line_string<CoordinateType>>
{
    static constexpr bool value = true;
};

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::polygon<CoordinateType>>
{
    static constexpr bool value = true;
};

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::multi_point<CoordinateType>>
{
    static constexpr bool value = true;
};


template <bool implemented = false>
struct intersects
{
    template <typename Geometry1, typename Geometry2>
    static bool apply(Geometry1 const&, Geometry2 const&)
    {
        throw std::runtime_error("Not implemented!");
    }
};

template <>
struct intersects<true>
{
    template <typename CoordinateType, typename Geometry2>
    static bool apply(mapbox::geometry::multi_point<CoordinateType> const& mp, Geometry2 const& g2)
    {
        for (auto const& p : mp)
        {
            if (boost::geometry::intersects(p, g2)) return true;
        }
        return false;
    }

    template <typename Geometry1, typename CoordinateType>
    static bool apply(Geometry1 const& g1, mapbox::geometry::multi_point<CoordinateType> const& mp)
    {
        for (auto const& p : mp)
        {
            if (boost::geometry::intersects(g1, p)) return true;
        }
        return false;
    }

    template <typename CoordinateType>
    static bool apply(mapbox::geometry::multi_point<CoordinateType> const& mp1,
                      mapbox::geometry::multi_point<CoordinateType> const& mp2)
    {
        for (auto const& p1 : mp1)
        {
            for (auto const& p2 : mp2)
            {
                if (boost::geometry::intersects(p1, p2)) return true;
            }
        }
        return false;
    }

    template <typename Geometry1, typename Geometry2>
    static bool apply(Geometry1 const& g1, Geometry2 const& g2)
    {
        return boost::geometry::intersects(g1, g2);
    }
};
}

template <typename Geometry1, typename Geometry2>
bool intersects(Geometry1 const& g1, Geometry2 const& g2)
{
    return detail::dispatcher<detail::intersects, Geometry1,Geometry2>::apply(g1, g2);
}

}}}
