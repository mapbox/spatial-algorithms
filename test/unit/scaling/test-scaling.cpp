#include <boost/test/unit_test.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/scaling.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(scaling_tests)

using namespace mapbox::geometry;
namespace op = algorithms;

namespace testing {

template <typename T>
void check_equal(point<T> const& pt1, point<T> const& pt2) {
    BOOST_CHECK_EQUAL(pt1.x, pt2.x);
    BOOST_CHECK_EQUAL(pt1.y, pt2.y);
}

template <>
void check_equal<double>(point<double> const& pt1, point<double> const& pt2) {
    BOOST_CHECK_CLOSE(pt1.x, pt2.x, 0.001);
    BOOST_CHECK_CLOSE(pt1.y, pt2.y, 0.001);
}

template <>
void check_equal<float>(point<float> const& pt1, point<float> const& pt2) {
    BOOST_CHECK_CLOSE(pt1.x, pt2.x, 0.001);
    BOOST_CHECK_CLOSE(pt1.y, pt2.y, 0.001);
}

template <typename T>
void check_equal(multi_point<T> const& mp1, multi_point<T> const& mp2) {
    BOOST_REQUIRE_EQUAL(mp1.size(), mp2.size());
    for (int i = 0; i < mp1.size(); ++i) {
        check_equal(mp1[i], mp2[i]);
    }
}

template <typename T>
void check_equal(line_string<T> const& ls1, line_string<T> const& ls2) {
    BOOST_REQUIRE_EQUAL(ls1.size(), ls2.size());
    for (int i = 0; i < ls1.size(); ++i) {
        check_equal(ls1[i], ls2[i]);
    }
}

template <typename T>
void check_equal(multi_line_string<T> const& mls1, multi_line_string<T> const& mls2) {
    BOOST_REQUIRE_EQUAL(mls1.size(), mls2.size());
    for (int i = 0; i < mls1.size(); ++i) {
        check_equal(mls1[i], mls2[i]);
    }
}

template <typename T>
void check_equal(linear_ring<T> const& lr1, linear_ring<T> const& lr2) {
    BOOST_REQUIRE_EQUAL(lr1.size(), lr2.size());
    for (int i = 0; i < lr1.size(); ++i) {
        check_equal(lr1[i], lr2[i]);
    }
}

template <typename T>
void check_equal(polygon<T> const& poly1, polygon<T> const& poly2) {
    BOOST_REQUIRE_EQUAL(poly1.size(), poly2.size());
    for (int i = 0; i < poly1.size(); ++i) {
        check_equal(poly1[i], poly2[i]);
    }
}

template <typename T>
void check_equal(multi_polygon<T> const& mp1, multi_polygon<T> const& mp2) {
    BOOST_REQUIRE_EQUAL(mp1.size(), mp2.size());
    for (int i = 0; i < mp1.size(); ++i) {
        check_equal(mp1[i], mp2[i]);
    }
}

} // end namespace testing

BOOST_AUTO_TEST_CASE(scaling_point_d_d)
{
    {
        point<double> input{100.0,200.0};
        point<double> expected{250.0,500.0};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        point<double> input{100.0, 200.0};
        point<double> expected{50.0, 100.0};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        point<double> input{100.0, 200.0};
        double scale = M_PI;
        point<double> expected{100.0 * scale, 200.0 * scale};
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);

    }
}

BOOST_AUTO_TEST_CASE(scaling_multi_point_d_d)
{
    {
        multi_point<double> input{ {100.0, 200.0}, {-120.0, -300.0} };
        multi_point<double> expected{ {250.0, 500.0}, {-300.0, -750.0} };
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        multi_point<double> input{ {100.0, 200.0}, {-120.0, -300.0} };
        multi_point<double> expected{ {50.0, 100.0}, {-60.0, -150.0} };
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        multi_point<double> input{ {100.0, 200.0}, {-120.0, -300.0} };
        double scale = M_PI;
        multi_point<double> expected{ {100.0 * scale, 200.0 * scale}, {-120.0 * scale, -300.0 * scale} };
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
}

BOOST_AUTO_TEST_CASE(scaling_line_string_d_d)
{
    {
        line_string<double> input{ {100.0, 200.0}, {-120.0, -300.0} };
        line_string<double> expected{ {250.0, 500.0}, {-300.0, -750.0} };
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        line_string<double> input{ {100.0, 200.0}, {-120.0, -300.0} };
        line_string<double> expected{ {50.0, 100.0}, {-60.0, -150.0} };
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        line_string<double> input{ {100.0, 200.0}, {-120.0, -300.0} };
        double scale = M_PI;
        line_string<double> expected{ {100.0 * scale, 200.0 * scale}, {-120.0 * scale, -300.0 * scale} };
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
}

BOOST_AUTO_TEST_CASE(scaling_multi_line_string_d_d)
{
    {
        multi_line_string<double> input{{{100.0, 200.0}, {-120.0, -300.0}},{{50.0, 25.0}, {3.1, 5.6}}};
        multi_line_string<double> expected{{{250.0, 500.0}, {-300.0, -750.0}},{{125.0, 62.5}, {7.75, 14.0}}};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        multi_line_string<double> input{{{100.0, 200.0}, {-120.0, -300.0}},{{50.0, 25.0}, {3.1, 5.6}}};
        multi_line_string<double> expected{{{50.0, 100.0}, {-60.0, -150.0}},{{25.0, 12.5}, {1.55, 2.8}}};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        multi_line_string<double> input{{{100.0, 200.0}, {-120.0, -300.0}},{{50.0, 25.0}, {3.1, 5.6}}};
        double scale = M_PI;
        multi_line_string<double> expected{{{100.0*scale, 200.0*scale}, {-120.0*scale, -300.0*scale}},{{50.0*scale, 25.0*scale}, {3.1*scale, 5.6*scale}}};
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
}

BOOST_AUTO_TEST_CASE(scaling_polygon_d_d)
{
    // Note that these are invalid polygons just testing the values scale properly.
    {
        polygon<double> input{{{100.0, 200.0}, {-120.0, -300.0}},{{50.0, 25.0}, {3.1, 5.6}}};
        polygon<double> expected{{{250.0, 500.0}, {-300.0, -750.0}},{{125.0, 62.5}, {7.75, 14.0}}};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        polygon<double> input{{{100.0, 200.0}, {-120.0, -300.0}},{{50.0, 25.0}, {3.1, 5.6}}};
        polygon<double> expected{{{50.0, 100.0}, {-60.0, -150.0}},{{25.0, 12.5}, {1.55, 2.8}}};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
    {
        polygon<double> input{{{100.0, 200.0}, {-120.0, -300.0}},{{50.0, 25.0}, {3.1, 5.6}}};
        double scale = M_PI;
        polygon<double> expected{{{100.0*scale, 200.0*scale}, {-120.0*scale, -300.0*scale}},{{50.0*scale, 25.0*scale}, {3.1*scale, 5.6*scale}}};
        auto output = op::scale<double, double>(input, scale);
        testing::check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        testing::check_equal(input, output_2);
    }
}

BOOST_AUTO_TEST_SUITE_END()
