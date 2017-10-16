//
#include <mapbox/geometry/geometry.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/detail/predicate_dispatcher.hpp>
#include <mapbox/geometry/algorithms/predicates/disjoint.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>

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
struct disjoint
{
    template <typename Geometry1, typename Geometry2>
    static bool apply(Geometry1 const& g1, Geometry2 const& g2)
    {
        throw std::runtime_error("Not implemented!");
    }
};

template <>
struct disjoint<true>
{
    template <typename CoordinateType, typename Geometry2>
    static bool apply(mapbox::geometry::multi_point<CoordinateType> const& mp, Geometry2 const& g2)
    {
        for (auto const& p : mp)
        {
            if (!boost::geometry::disjoint(p, g2)) return false;
        }
        return true;
    }

    template <typename Geometry1, typename CoordinateType>
    static bool apply(Geometry1 const& g1, mapbox::geometry::multi_point<CoordinateType> const& mp)
    {
        for (auto const& p : mp)
        {
            if (!boost::geometry::disjoint(g1, p)) return false;
        }
        return true;
    }

    template <typename CoordinateType>
    static bool apply(mapbox::geometry::multi_point<CoordinateType> const& mp1,
                      mapbox::geometry::multi_point<CoordinateType> const& mp2)
    {
        for (auto const& p1 : mp1)
        {
            for (auto const& p2 : mp2)
            {
                if (!boost::geometry::disjoint(p1, p2))
                    return false;
            }
        }
        return true;
    }

    template <typename Geometry1, typename Geometry2>
    static bool apply(Geometry1 const& g1, Geometry2 const& g2)
    {
        return boost::geometry::disjoint(g1, g2);
    }
};
}

template <typename Geometry1, typename Geometry2>
bool disjoint(Geometry1 const& g1, Geometry2 const& g2)
{
    return detail::dispatcher<detail::disjoint, Geometry1,Geometry2>::apply(g1, g2);
}

}}}
