#pragma once

// mapbox
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/box.hpp>
// boost.geometry
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/ring.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/geometry/geometries/register/box.hpp>

BOOST_GEOMETRY_REGISTER_POINT_2D(mapbox::geometry::point<double>, double, boost::geometry::cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_POINT_2D (mapbox::geometry::point<std::int64_t>, std::int64_t, boost::geometry::cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(mapbox::geometry::line_string)
BOOST_GEOMETRY_REGISTER_RING_TEMPLATED(mapbox::geometry::linear_ring)

namespace mapbox {

template <typename CoordinateType>
struct const_interior_rings
{
    using polygon_type = mapbox::geometry::polygon<CoordinateType> const;
    using const_iterator = typename polygon_type::const_iterator;
    using iterator = const_iterator; // needed by boost::range_iterator
    using value_type = typename polygon_type::value_type;

    const_interior_rings(polygon_type const& poly)
        : poly_(poly) {}

    const_iterator begin() const
    {
        auto itr = poly_.cbegin();
        std::advance(itr, 1);
        return itr;
    }

    const_iterator end() const { return poly_.cend();}

    std::size_t size() const
    {
        return poly_.empty() ? 0 : poly_.size() - 1;
    }

    value_type const& back()  const { return poly_.back(); }
    polygon_type const& poly_;
};


template <typename CoordinateType>
struct interior_rings
{
    using polygon_type = mapbox::geometry::polygon<CoordinateType>;
    using iterator = typename polygon_type::iterator;
    using const_iterator = typename polygon_type::const_iterator;
    using value_type = typename polygon_type::value_type;

    interior_rings(polygon_type & poly)
        : poly_(poly) {}

    iterator begin()
    {
        auto itr = poly_.begin();
        std::advance(itr, 1);
        return itr;
    }

    iterator end() { return poly_.end();}
    const_iterator begin() const
    {
        auto itr = poly_.cbegin();
        std::advance(itr, 1);
        return itr;
    }

    const_iterator end() const { return poly_.cend();}

    void clear()
    {
        poly_.resize(1);
    }

    void resize(std::size_t size)
    {
        poly_.resize(size + 1);
    }

    std::size_t size() const
    {
        return poly_.empty() ? 0 : poly_.size() - 1;
    }

    void push_back(value_type const& val) { poly_.push_back(val); }
    value_type& back() { return poly_.back(); }
    value_type const& back()  const { return poly_.back(); }
    polygon_type & poly_;
};

} // ns mapbox

namespace boost { namespace geometry { namespace traits {

template <typename CoordinateType>
struct tag<mapbox::geometry::box<CoordinateType> >
{
    using type = box_tag;
};

template <typename CoordinateType> struct point_type<mapbox::geometry::box<CoordinateType> >
{
    using type = typename mapbox::geometry::point<CoordinateType>;
};

template <typename CoordinateType>
struct indexed_access<mapbox::geometry::box<CoordinateType>, min_corner, 0>
{
    using ct = CoordinateType;
    static inline ct get(mapbox::geometry::box<CoordinateType> const& b) { return b.min.x;}
    static inline void set(mapbox::geometry::box<CoordinateType> &b, ct const& value) { b.min.x = value; }
};

template <typename CoordinateType>
struct indexed_access<mapbox::geometry::box<CoordinateType>, min_corner, 1>
{
    using ct = CoordinateType;
    static inline ct get(mapbox::geometry::box<CoordinateType> const& b) { return b.min.y;}
    static inline void set(mapbox::geometry::box<CoordinateType> &b, ct const& value) { b.min.y = value; }
};

template <typename CoordinateType>
struct indexed_access<mapbox::geometry::box<CoordinateType>, max_corner, 0>
{
    using ct = CoordinateType;
    static inline ct get(mapbox::geometry::box<CoordinateType> const& b) { return b.max.x;}
    static inline void set(mapbox::geometry::box<CoordinateType> &b, ct const& value) { b.max.x = value; }
};

template <typename CoordinateType>
struct indexed_access<mapbox::geometry::box<CoordinateType>, max_corner, 1>
{
    using ct = CoordinateType;
    static inline ct get(mapbox::geometry::box<CoordinateType> const& b) { return b.max.y;}
    static inline void set(mapbox::geometry::box<CoordinateType> &b , ct const& value) { b.max.y = value; }
};

template<typename CoordinateType>
struct tag<mapbox::geometry::polygon<CoordinateType> >
{
    using type = polygon_tag;
};

template <typename CoordinateType>
struct point_order<mapbox::geometry::linear_ring<CoordinateType> >
{
    static const order_selector value = counterclockwise;
};

template<typename CoordinateType>
struct tag<mapbox::geometry::multi_point<CoordinateType> >
{
    using type = multi_point_tag;
};

template<typename CoordinateType>
struct tag<mapbox::geometry::multi_line_string<CoordinateType> >
{
    using type = multi_linestring_tag;
};

template<typename CoordinateType>
struct tag<mapbox::geometry::multi_polygon<CoordinateType> >
{
    using type = multi_polygon_tag;
};

// ring
template <typename CoordinateType>
struct ring_const_type<mapbox::geometry::polygon<CoordinateType> >
{
    using type = typename mapbox::geometry::linear_ring<CoordinateType> const&;
};

template <typename CoordinateType>
struct ring_mutable_type<mapbox::geometry::polygon<CoordinateType> >
{
    using type = typename mapbox::geometry::linear_ring<CoordinateType>&;
};

// interior
template <typename CoordinateType>
struct interior_const_type<mapbox::geometry::polygon<CoordinateType>>
{
    using type = typename mapbox::const_interior_rings<CoordinateType> const;
};

template <typename CoordinateType>
struct interior_mutable_type<mapbox::geometry::polygon<CoordinateType> >
{
    using type = typename mapbox::interior_rings<CoordinateType> ;
};

template <typename CoordinateType>
struct exterior_ring<mapbox::geometry::polygon<CoordinateType> >
{
    using ring_const_type   = typename ring_const_type<mapbox::geometry::polygon<CoordinateType> >::type;
    using ring_mutable_type = typename ring_mutable_type<mapbox::geometry::polygon<CoordinateType> >::type;
    static ring_mutable_type get(mapbox::geometry::polygon<CoordinateType> & p)
    {
        if (p.empty()) p.resize(1);
        return p[0];
    }

    static ring_const_type get(mapbox::geometry::polygon<CoordinateType> const& p)
    {
        if (p.empty()) throw std::runtime_error("Exterior ring must be initialized!");
        return p[0];
    }
};

template <typename CoordinateType>
struct interior_rings<mapbox::geometry::polygon<CoordinateType> >
{
    using interior_const_type = typename interior_const_type<mapbox::geometry::polygon<CoordinateType> >::type;
    using interior_mutable_type = typename interior_mutable_type<mapbox::geometry::polygon<CoordinateType> >::type;

    static interior_const_type get(mapbox::geometry::polygon<CoordinateType> const& p)
    {
        return mapbox::const_interior_rings<CoordinateType>(p);
    }

    static interior_mutable_type get(mapbox::geometry::polygon<CoordinateType>& p)
    {
        return mapbox::interior_rings<CoordinateType>(p);
    }
};

template <typename CoordinateType>
struct resize<mapbox::interior_rings<CoordinateType>>
{
    static inline void apply(mapbox::interior_rings<CoordinateType> interiors, std::size_t new_size)
    {
        interiors.resize(new_size);
    }
};

template <typename CoordinateType>
struct clear<mapbox::interior_rings<CoordinateType>>
{
    static inline void apply(mapbox::interior_rings<CoordinateType> interiors)
    {
        interiors.clear();
    }
};

template <typename CoordinateType>
struct push_back<mapbox::interior_rings<CoordinateType>>
{
    template <typename Ring>
    static inline void apply(mapbox::interior_rings<CoordinateType> interiors, Ring const& ring)
    {
        interiors.push_back(ring);
    }
};

}}}
