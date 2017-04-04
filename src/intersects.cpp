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
    template <typename Geometry1, typename Geometry2>
    static bool apply(Geometry1 const& g1, Geometry2 const& g2)
    {
        return boost::geometry::intersects(g1, g2);
    }
};

struct intersects
{
    template <typename Geometry1, typename Geometry2>
    bool operator() (Geometry1 const& g1, Geometry2 const& g2) const
    {
        std::cerr << "Geometry1:" << typeid(g1).name() << std::endl;
        std::cerr << "Geometry2:" << typeid(g2).name() << std::endl;
        return impl<is_implemented<Geometry1>::value && is_implemented<Geometry2>::value>::apply(g1,g2);
    }
};

}

template <typename CoordinateType>
bool intersects(geometry<CoordinateType> const& geom1, geometry<CoordinateType> const& geom2)
{
    return mapbox::util::apply_visitor(detail::intersects(), geom1, geom2);
}


template bool intersects(geometry<double> const&, geometry<double> const&);

}}}
