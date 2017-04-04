//
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/predicates/intersects.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

namespace detail {

template <typename T>
struct is_implemented
{
    static constexpr bool value = false;
};

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
struct impl
{
    template <typename Geometry1, typename Geometry2>
    static bool apply(Geometry1 const& g1, Geometry2 const& g2)
    {
        throw std::runtime_error("Not implemented!");
    }
};

template <>
struct impl<true>
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

struct predicate_binary_visitor
{
    template <typename Geometry1, typename Geometry2>
    bool operator() (Geometry1 const& g1, Geometry2 const& g2) const
    {
      return impl<is_implemented<Geometry1>::value &&
                  is_implemented<Geometry2>::value>::apply(g1, g2);
    }
};

template <typename Geometry1>
struct predicate_visitor
{
    predicate_visitor(Geometry1 const& g1_)
        : g1(g1_) {}

    template <typename Geometry2>
    bool operator() (Geometry2 const& g2) const
    {
        return impl<is_implemented<Geometry1>::value &&
                    is_implemented<Geometry2>::value>::apply(g1, g2);
    }
    Geometry1 const& g1;
};

template <typename T1, typename T2>
struct dispatcher
{
    template <typename G1 = T1, typename G2 = T2, typename std::enable_if
              <std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value
               &&
               std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value
               ,int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return mapbox::util::apply_visitor(detail::predicate_binary_visitor(), g1, g2);
    }

    template <typename G1 = T1, typename G2 = T2, typename std::enable_if
              <!std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value
               &&
               !std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value
               ,int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return detail::predicate_binary_visitor()(g1, g2);
    }

    template <typename G1 = T1, typename G2 = T2, typename std::enable_if
              <std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value
               &&
               !std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value
               ,int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return mapbox::util::apply_visitor(detail::predicate_visitor<G2>(g2), g1);
    }

    template <typename G1 = T1, typename G2 = T2, typename std::enable_if
              <!std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value
               &&
               std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value
               ,int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return mapbox::util::apply_visitor(detail::predicate_visitor<G1>(g1), g2);
    }
};

}

template <typename Geometry1, typename Geometry2>
bool intersects(Geometry1 const& g1, Geometry2 const& g2)
{
    return detail::dispatcher<Geometry1,Geometry2>::apply(g1, g2);
}

}}}
