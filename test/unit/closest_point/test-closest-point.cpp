#include <boost/test/unit_test.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/closest_point.hpp>
#include <iostream>
BOOST_AUTO_TEST_SUITE(closest_point_tests)

namespace testing {

void test_closest_point_d()
{
    using namespace mapbox::geometry;
    namespace op = algorithms;
    // Point => Point
    {
        point<double> p1{0.0, 0.0};
        point<double> p2{3.0, 4.0};
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

        line_string<double> line {{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        point<double> pt {50, 50};
        auto result = op::closest_point(line, pt);
        BOOST_CHECK(result.x == 0.0);
        BOOST_CHECK(result.y == 50.0);
        BOOST_CHECK(result.distance == 50.0);
    }

    // Point => Polygon
    {
        polygon<double> poly {{{0, 0},{1, 0},{1, 1},{0, 1}, {0, 0}}};

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
}

void test_closest_point_int64()
{
    using namespace mapbox::geometry;
    namespace op = algorithms;
    // Point => Point
    {
        point<std::int64_t> p1{0, 0};
        point<std::int64_t> p2{3, 4};
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
        line_string<std::int64_t> line {{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        point<std::int64_t> pt {50, 50};
        auto result = op::closest_point(line, pt);
        BOOST_CHECK(result.x == 0.0);
        BOOST_CHECK(result.y == 50.0);
        BOOST_CHECK(result.distance == 50.0);
    }

    // Point => Polygon
    {
        polygon<std::int64_t> poly {{{0, 0},{100, 0},{100, 100},{0, 100}, {0, 0}}};

        {
            // point inside polygon
            point<std::int64_t> pt {50, 25};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 50.0);
            BOOST_CHECK(result.y == 25.0);
            BOOST_CHECK(result.distance == 0.0);
        }

        {
            // point outside polygon
            point<std::int64_t> pt {125, 50};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 100.0);
            BOOST_CHECK(result.y == 50.0);
            BOOST_CHECK(result.distance == 25.0);
        }
        {
            // point outside polygon
            point<std::int64_t> pt {400, 500};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 100.0);
            BOOST_CHECK(result.y == 100.0);
            BOOST_CHECK(result.distance == 500.0);
        }
        {
            // point on polygon boundary
            point<std::int64_t> pt {0, 40};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK(result.x == 0.0);
            BOOST_CHECK(result.y == 40.0);
            BOOST_CHECK(result.distance == 0.0);
        }
    }
}

}// ns testing

BOOST_AUTO_TEST_CASE(closest_point)
{
    testing::test_closest_point_d();
    testing::test_closest_point_int64();
}

BOOST_AUTO_TEST_SUITE_END()
