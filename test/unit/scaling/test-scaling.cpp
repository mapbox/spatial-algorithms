#include "../util/check_equal.hpp"
#include <catch.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/scaling.hpp>

using namespace mapbox::geometry;
namespace op = algorithms;

TEST_CASE("scaling point double double")
{
    SECTION("scale by 2.5")
    {
        point<double> input{100.0, 200.0};
        point<double> expected{250.0, 500.0};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by 0.5")
    {
        point<double> input{100.0, 200.0};
        point<double> expected{50.0, 100.0};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by PI")
    {
        point<double> input{100.0, 200.0};
        double scale = M_PI;
        point<double> expected{100.0 * scale, 200.0 * scale};
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
}

TEST_CASE("scaling multi point double double")
{
    SECTION("scale by 2.5")
    {
        multi_point<double> input{{100.0, 200.0}, {-120.0, -300.0}};
        multi_point<double> expected{{250.0, 500.0}, {-300.0, -750.0}};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by 0.5")
    {
        multi_point<double> input{{100.0, 200.0}, {-120.0, -300.0}};
        multi_point<double> expected{{50.0, 100.0}, {-60.0, -150.0}};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by PI")
    {
        multi_point<double> input{{100.0, 200.0}, {-120.0, -300.0}};
        double scale = M_PI;
        multi_point<double> expected{{100.0 * scale, 200.0 * scale}, {-120.0 * scale, -300.0 * scale}};
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
}

TEST_CASE("scaling linestring double double")
{
    SECTION("scale by 2.5")
    {
        line_string<double> input{{100.0, 200.0}, {-120.0, -300.0}};
        line_string<double> expected{{250.0, 500.0}, {-300.0, -750.0}};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by 0.5")
    {
        line_string<double> input{{100.0, 200.0}, {-120.0, -300.0}};
        line_string<double> expected{{50.0, 100.0}, {-60.0, -150.0}};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by PI")
    {
        line_string<double> input{{100.0, 200.0}, {-120.0, -300.0}};
        double scale = M_PI;
        line_string<double> expected{{100.0 * scale, 200.0 * scale}, {-120.0 * scale, -300.0 * scale}};
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
}

TEST_CASE("scaling multi_line_string double double")
{
    SECTION("scale by 2.5")
    {
        multi_line_string<double> input{{{100.0, 200.0}, {-120.0, -300.0}}, {{50.0, 25.0}, {3.1, 5.6}}};
        multi_line_string<double> expected{{{250.0, 500.0}, {-300.0, -750.0}}, {{125.0, 62.5}, {7.75, 14.0}}};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by 0.5")
    {
        multi_line_string<double> input{{{100.0, 200.0}, {-120.0, -300.0}}, {{50.0, 25.0}, {3.1, 5.6}}};
        multi_line_string<double> expected{{{50.0, 100.0}, {-60.0, -150.0}}, {{25.0, 12.5}, {1.55, 2.8}}};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by PI")
    {
        multi_line_string<double> input{{{100.0, 200.0}, {-120.0, -300.0}}, {{50.0, 25.0}, {3.1, 5.6}}};
        double scale = M_PI;
        multi_line_string<double> expected{{{100.0 * scale, 200.0 * scale}, {-120.0 * scale, -300.0 * scale}}, {{50.0 * scale, 25.0 * scale}, {3.1 * scale, 5.6 * scale}}};
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
}

TEST_CASE("scaling polygon double double")
{
    // Note that these are invalid polygons just testing the values scale properly.
    SECTION("scale by 2.5")
    {
        polygon<double> input{{{100.0, 200.0}, {-120.0, -300.0}}, {{50.0, 25.0}, {3.1, 5.6}}};
        polygon<double> expected{{{250.0, 500.0}, {-300.0, -750.0}}, {{125.0, 62.5}, {7.75, 14.0}}};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by 0.5")
    {
        polygon<double> input{{{100.0, 200.0}, {-120.0, -300.0}}, {{50.0, 25.0}, {3.1, 5.6}}};
        polygon<double> expected{{{50.0, 100.0}, {-60.0, -150.0}}, {{25.0, 12.5}, {1.55, 2.8}}};
        double scale = 0.5;
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
    SECTION("scale by PI")
    {
        polygon<double> input{{{100.0, 200.0}, {-120.0, -300.0}}, {{50.0, 25.0}, {3.1, 5.6}}};
        double scale = M_PI;
        polygon<double> expected{{{100.0 * scale, 200.0 * scale}, {-120.0 * scale, -300.0 * scale}}, {{50.0 * scale, 25.0 * scale}, {3.1 * scale, 5.6 * scale}}};
        auto output = op::scale<double, double>(input, scale);
        check_equal(expected, output);
        auto output_2 = op::scale<double, double>(output, 1.0 / scale);
        check_equal(input, output_2);
    }
}
