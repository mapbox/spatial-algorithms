#include <boost/test/unit_test.hpp>
#include <mapbox/geometry/geometry.hpp>
#include <mapbox/geometry/algorithms/closest_point.hpp>
#include <iostream>
BOOST_AUTO_TEST_SUITE(closest_point_tests)

namespace testing {

template <typename T>
void test_closest_point()
{
    using namespace mapbox::geometry;
    namespace op = algorithms;
    // Point => Point
    {
        point<T> p1{0.0, 0.0};
        point<T> p2{3.0, 4.0};
        {
            auto result = op::closest_point(p1, p2);
            BOOST_CHECK(result.x == 0.0);
            BOOST_CHECK(result.y == 0.0);
            BOOST_CHECK(result.distance == 5.0);
        }
        {
            auto result = op::closest_point(p2, p1);
            BOOST_CHECK(result.x == 3.0);
            BOOST_CHECK(result.y == 4.0);
            BOOST_CHECK(result.distance == 5.0);
        }
    }

    // Point => LineString
    {

        line_string<T> line {{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        point<T> pt {50, 50};
        auto result = op::closest_point(line, pt);
        BOOST_CHECK(result.x == 0.0);
        BOOST_CHECK(result.y == 50.0);
        BOOST_CHECK(result.distance == 50.0);
    }

    // Point => Polygon
    {
        polygon<T> poly {{{0, 0},{1, 0},{1, 1},{0, 1}, {0, 0}}};

        {
            // point inside polygon
            point<double> pt {0.5, 0.25};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 0.5);
            BOOST_CHECK(result.y == 0.25);
            BOOST_CHECK(result.distance == 0.0);
        }

        {
            // point outside polygon
            point<double> pt {1.25, 0.5};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 1.0);
            BOOST_CHECK(result.y == 0.5);
            BOOST_CHECK(result.distance == 0.25);
        }
        {
            // point outside polygon
            point<double> pt {4.0, 5.0};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 1.0);
            BOOST_CHECK(result.y == 1.0);
            BOOST_CHECK(result.distance == 5.0);
        }
        {
            // point on polygon boundary
            point<double> pt {0, 0.4};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 0.0);
            BOOST_CHECK(result.y == 0.4);
            BOOST_CHECK(result.distance == 0.0);
        }
    }
}}

BOOST_AUTO_TEST_CASE(closest_point)
{
    testing::test_closest_point<double>();
    //testing::test_closest_point<std::int64_t>();
}

BOOST_AUTO_TEST_SUITE_END()
