#pragma once

#include <mapbox/geometry/geometry.hpp>

namespace mapbox {
namespace geometry {
namespace algorithms {

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type = double>
mapbox::geometry::point<coordinate_type_2> scale(mapbox::geometry::point<coordinate_type_1> const& pt, calculation_type val);

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type = double>
mapbox::geometry::multi_point<coordinate_type_2> scale(mapbox::geometry::multi_point<coordinate_type_1> const& mp, calculation_type val);

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type = double>
mapbox::geometry::line_string<coordinate_type_2> scale(mapbox::geometry::line_string<coordinate_type_1> const& ls, calculation_type val);

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type = double>
mapbox::geometry::multi_line_string<coordinate_type_2> scale(mapbox::geometry::multi_line_string<coordinate_type_1> const& mls, calculation_type val);

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type = double>
mapbox::geometry::polygon<coordinate_type_2> scale(mapbox::geometry::polygon<coordinate_type_1> const& poly, calculation_type val);

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type = double>
mapbox::geometry::multi_polygon<coordinate_type_2> scale(mapbox::geometry::multi_polygon<coordinate_type_1> const& mp, calculation_type val);

template <typename coordinate_type_1, typename coordinate_type_2, typename calculation_type = double>
mapbox::geometry::geometry<coordinate_type_2> scale(mapbox::geometry::geometry<coordinate_type_1> const& geom, calculation_type val);
}
}
}
