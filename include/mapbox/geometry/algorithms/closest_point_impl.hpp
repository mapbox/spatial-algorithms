#include <mapbox/geometry/geometry.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/closest_point.hpp>
#include <boost/geometry/extensions/algorithms/closest_point.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

namespace detail {

template <typename T>
struct closest_point
{
    using coordinate_type = T;
    using info_type = boost::geometry::closest_point_result<mapbox::geometry::point<coordinate_type>>;
    using result_type = closest_point_info<coordinate_type>;
    closest_point(mapbox::geometry::point<coordinate_type> const& pt)
        : pt_(pt) {}

    result_type operator() (mapbox::geometry::point<coordinate_type> const& pt) const
    {
        info_type info;
        boost::geometry::closest_point(pt_, pt, info);
        return result_type(info.closest_point.x, info.closest_point.y, info.distance);
    }

    result_type operator() (mapbox::geometry::line_string<coordinate_type> const& line) const
    {
        info_type info;
        boost::geometry::closest_point(pt_ ,line, info);
        return result_type(info.closest_point.x, info.closest_point.y, info.distance);
    }

    result_type operator() (mapbox::geometry::polygon<coordinate_type> const& poly) const
    {
        info_type info;
        if (boost::geometry::within(pt_, poly))
        {
            return result_type(pt_.x, pt_.y, 0.0);
        }
        bool first = true;
        for (auto const& ring : poly)
        {
            info_type ring_info;
            boost::geometry::closest_point(pt_ ,ring, ring_info);
            if (first)
            {
                first = false;
                info = std::move(ring_info);
            }
            else if (ring_info.distance < info.distance)
            {
                info = std::move(ring_info);
            }
        }
        return result_type(info.closest_point.x, info.closest_point.y, info.distance);
    }

    // Multi* + GeometryCollection
    result_type operator() (mapbox::geometry::geometry<coordinate_type> const& geom) const
    {
        return mapbox::util::apply_visitor(*this, geom);
    }

    template <typename MultiGeometry>
    result_type operator() (MultiGeometry const& multi_geom) const
    {
        result_type result;
        bool first = true;
        for (auto const& geom : multi_geom)
        {
            if (first)
            {
                first = false;
                result = std::move(operator()(geom));
            }
            else
            {
                auto sub_result = operator()(geom);
                if (sub_result.distance < result.distance)
                {
                    result = std::move(sub_result);
                }
            }
        }
        return result;
    }
    mapbox::geometry::point<coordinate_type> pt_;
};

}

template <typename T1, typename T2>
auto closest_point(T1 const& geom, mapbox::geometry::point<T2> const& pt)->closest_point_info<T2>
{
    return detail::closest_point<T2>(pt)(geom);
}

}}}
