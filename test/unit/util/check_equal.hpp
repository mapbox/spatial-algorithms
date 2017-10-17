#pragma once

#include <boost/test/unit_test.hpp>
#include <mapbox/geometry.hpp>

namespace testing {

using namespace mapbox::geometry;

template <typename T>
inline void check_equal(point<T> const& pt1, point<T> const& pt2) {
    BOOST_CHECK_EQUAL(pt1.x, pt2.x);
    BOOST_CHECK_EQUAL(pt1.y, pt2.y);
}

template <>
inline void check_equal<double>(point<double> const& pt1, point<double> const& pt2) {
    BOOST_CHECK_CLOSE(pt1.x, pt2.x, 1e-6);
    BOOST_CHECK_CLOSE(pt1.y, pt2.y, 1e-6);
}

template <>
inline void check_equal<float>(point<float> const& pt1, point<float> const& pt2) {
    BOOST_CHECK_CLOSE(pt1.x, pt2.x, 1e-6);
    BOOST_CHECK_CLOSE(pt1.y, pt2.y, 1e-6);
}

template <typename T>
inline void check_equal(multi_point<T> const& mp1, multi_point<T> const& mp2) {
    BOOST_REQUIRE_EQUAL(mp1.size(), mp2.size());
    for (std::size_t i = 0; i < mp1.size(); ++i) {
        check_equal(mp1[i], mp2[i]);
    }
}

template <typename T>
inline void check_equal(line_string<T> const& ls1, line_string<T> const& ls2) {
    BOOST_REQUIRE_EQUAL(ls1.size(), ls2.size());
    for (std::size_t i = 0; i < ls1.size(); ++i) {
        check_equal(ls1[i], ls2[i]);
    }
}

template <typename T>
inline void check_equal(multi_line_string<T> const& mls1, multi_line_string<T> const& mls2) {
    BOOST_REQUIRE_EQUAL(mls1.size(), mls2.size());
    for (std::size_t i = 0; i < mls1.size(); ++i) {
        check_equal(mls1[i], mls2[i]);
    }
}

template <typename T>
inline void check_equal(linear_ring<T> const& lr1, linear_ring<T> const& lr2) {
    BOOST_REQUIRE_EQUAL(lr1.size(), lr2.size());
    for (std::size_t i = 0; i < lr1.size(); ++i) {
        check_equal(lr1[i], lr2[i]);
    }
}

template <typename T>
void check_equal(polygon<T> const& poly1, polygon<T> const& poly2) {
    BOOST_REQUIRE_EQUAL(poly1.size(), poly2.size());
    for (std::size_t i = 0; i < poly1.size(); ++i) {
        check_equal(poly1[i], poly2[i]);
    }
}

template <typename T>
inline void check_equal(multi_polygon<T> const& mp1, multi_polygon<T> const& mp2) {
    BOOST_REQUIRE_EQUAL(mp1.size(), mp2.size());
    for (std::size_t i = 0; i < mp1.size(); ++i) {
        check_equal(mp1[i], mp2[i]);
    }
}

} // end namespace testing
