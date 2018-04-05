#pragma once

namespace mapbox {
namespace geometry {
namespace algorithms {
namespace detail {

template <typename T>
struct is_implemented
{
    static constexpr bool value = false;
};

template <template <bool> class Predicate>
struct predicate_binary_visitor
{
    template <typename Geometry1, typename Geometry2>
    bool operator()(Geometry1 const& g1, Geometry2 const& g2) const
    {
        return Predicate < is_implemented<Geometry1>::value &&
               is_implemented<Geometry2>::value > ::apply(g1, g2);
    }
};

template <template <bool> class Predicate, typename Geometry1>
struct predicate_visitor
{
    predicate_visitor(Geometry1 const& g1_)
        : g1(g1_) {}

    template <typename Geometry2>
    bool operator()(Geometry2 const& g2) const
    {
        return Predicate < is_implemented<Geometry1>::value &&
               is_implemented<Geometry2>::value > ::apply(g1, g2);
    }
    Geometry1 const& g1;
};

template <template <bool> class Predicate, typename T1, typename T2>
struct dispatcher
{
    template <typename G1 = T1, typename G2 = T2, typename std::enable_if<std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value && std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value, int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return mapbox::util::apply_visitor(detail::predicate_binary_visitor<Predicate>(), g1, g2);
    }

    template <typename G1 = T1, typename G2 = T2, typename std::enable_if<!std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value && !std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value, int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return detail::predicate_binary_visitor<Predicate>()(g1, g2);
    }

    template <typename G1 = T1, typename G2 = T2, typename std::enable_if<std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value && !std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value, int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return mapbox::util::apply_visitor(detail::predicate_visitor<Predicate, G2>(g2), g1);
    }

    template <typename G1 = T1, typename G2 = T2, typename std::enable_if<!std::is_same<G1, mapbox::geometry::geometry<typename G1::coordinate_type>>::value && std::is_same<G2, mapbox::geometry::geometry<typename G2::coordinate_type>>::value, int>::type = 0>
    static bool apply(G1 const& g1, G2 const& g2)
    {
        return mapbox::util::apply_visitor(detail::predicate_visitor<Predicate, G1>(g1), g2);
    }
};
}
}
}
}
