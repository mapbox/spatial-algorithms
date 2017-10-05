#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/scaling.hpp>
#include <boost/geometry/algorithms/transform.hpp>

namespace mapbox { namespace geometry { namespace algorithms {

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
mapbox::geometry::point<coordinate_type_2> scale(mapbox::geometry::point<coordinate_type_1> const& pt, calculation_type val) {
    mapbox::geometry::point<coordinate_type_2> out;
    boost::geometry::strategy::transform::scale_transformer<calculation_type, 2, 2> scale(val);
    boost::geometry::transform(pt, out, scale);
    return out;
}

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
mapbox::geometry::multi_point<coordinate_type_2> scale(mapbox::geometry::multi_point<coordinate_type_1> const& mp, calculation_type val) {
    mapbox::geometry::multi_point<coordinate_type_2> out;
    boost::geometry::strategy::transform::scale_transformer<calculation_type, 2, 2> scale(val);
    boost::geometry::transform(mp, out, scale);
    return out;
}

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
mapbox::geometry::line_string<coordinate_type_2> scale(mapbox::geometry::line_string<coordinate_type_1> const& ls, calculation_type val) {
    mapbox::geometry::line_string<coordinate_type_2> out;
    boost::geometry::strategy::transform::scale_transformer<calculation_type, 2, 2> scale(val);
    boost::geometry::transform(ls, out, scale);
    return out;
}

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
mapbox::geometry::multi_line_string<coordinate_type_2> scale(mapbox::geometry::multi_line_string<coordinate_type_1> const& mls, calculation_type val) {
    mapbox::geometry::multi_line_string<coordinate_type_2> out;
    boost::geometry::strategy::transform::scale_transformer<calculation_type, 2, 2> scale(val);
    boost::geometry::transform(mls, out, scale);
    return out;
}

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
mapbox::geometry::polygon<coordinate_type_2> scale(mapbox::geometry::polygon<coordinate_type_1> const& poly, calculation_type val) {
    mapbox::geometry::polygon<coordinate_type_2> out;
    boost::geometry::strategy::transform::scale_transformer<calculation_type, 2, 2> scale(val);
    boost::geometry::transform(poly, out, scale);
    return out;
}

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
mapbox::geometry::multi_polygon<coordinate_type_2> scale(mapbox::geometry::multi_polygon<coordinate_type_1> const& mp, calculation_type val) {
    mapbox::geometry::multi_polygon<coordinate_type_2> out;
    boost::geometry::strategy::transform::scale_transformer<calculation_type, 2, 2> scale(val);
    boost::geometry::transform(mp, out, scale);
    return out;
}

namespace detail {


template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
struct scaling_visitor {

    using result_type = mapbox::geometry::geometry<coordinate_type_2>;
    
    boost::geometry::strategy::transform::scale_transformer<calculation_type, 2, 2> scale;

    scaling_visitor(calculation_type val)
        : scale(val) {}

    result_type operator() (mapbox::geometry::point<coordinate_type_1> const& pt) const {
        mapbox::geometry::point<coordinate_type_2> out;
        boost::geometry::transform(pt, out, scale);
        return result_type(out);
    }
    
    result_type operator() (mapbox::geometry::multi_point<coordinate_type_1> const& mp) const {
        mapbox::geometry::multi_point<coordinate_type_2> out;
        boost::geometry::transform(mp, out, scale);
        return result_type(out);
    }
    
    result_type operator() (mapbox::geometry::line_string<coordinate_type_1> const& line) const {
        mapbox::geometry::line_string<coordinate_type_2> out;
        boost::geometry::transform(line, out, scale);
        return result_type(out);
    }
    
    result_type operator() (mapbox::geometry::multi_line_string<coordinate_type_1> const& ml) const {
        mapbox::geometry::multi_line_string<coordinate_type_2> out;
        boost::geometry::transform(ml, out, scale);
        return result_type(out);
    }
    
    result_type operator() (mapbox::geometry::polygon<coordinate_type_1> const& poly) const {
        mapbox::geometry::polygon<coordinate_type_2> out;
        boost::geometry::transform(poly, out, scale);
        return result_type(out);
    }
    
    result_type operator() (mapbox::geometry::multi_polygon<coordinate_type_1> const& mp) const {
        mapbox::geometry::multi_polygon<coordinate_type_2> out;
        boost::geometry::transform(mp, out, scale);
        return result_type(out);
    }
    
    result_type operator() (mapbox::geometry::geometry<coordinate_type_1> const& geom) const
    {
        return mapbox::util::apply_visitor(*this, geom);
    }
    
    result_type operator() (mapbox::geometry::geometry_collection<coordinate_type_1> const& gc) const {
        mapbox::geometry::geometry_collection<coordinate_type_2> out;
        out.reserve(gc.size());
        for (auto const& geom : gc) {
            out.push_back(operator()(geom));
        }
        return result_type(out);
    }

};

}

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type>
mapbox::geometry::geometry<coordinate_type_2> scale(mapbox::geometry::geometry<coordinate_type_1> const& geom, calculation_type val) {
    using visitor_type = detail::scaling_visitor<coordinate_type_1, coordinate_type_2, calculation_type>;
    return mapbox::util::apply_visitor(visitor_type(val), geom);
}

}}}
