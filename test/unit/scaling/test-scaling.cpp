#include <boost/test/unit_test.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/scaling.hpp>
#include <iostream>
#include <cmath>
#include "../util/check_equal.hpp"

BOOST_AUTO_TEST_SUITE(scaling_tests)

using namespace mapbox::geometry;
namespace op = algorithms;

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
