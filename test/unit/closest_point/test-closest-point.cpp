#include <boost/test/unit_test.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/closest_point.hpp>
#include <cmath>
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
            BOOST_CHECK_CLOSE(result.x, 0.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 0.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 5.0, 1e-06);
        }
        {
            auto result = op::closest_point(p2, p1);
            BOOST_CHECK_CLOSE(result.x, 3.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 4.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 5.0, 1e-06);
        }
    }

    // Point => MultiPoint
    {
        point<double> p{0.0, 0.0};
        multi_point<double> mp{{-1.0,-1.0}, {1.0, 1.1}};
        auto result = op::closest_point(mp, p);
        BOOST_CHECK_CLOSE(result.x, -1.0, 1e-6);
        BOOST_CHECK_CLOSE(result.y, -1.0, 1e-6);
        BOOST_CHECK_CLOSE(result.distance, 1.41421356, 1e-6);
    }

    // Point => LineString
    {

        line_string<double> line {{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        point<double> pt {50, 50};
        auto result = op::closest_point(line, pt);
        BOOST_CHECK_CLOSE(result.x, 0.0, 1e-06);
        BOOST_CHECK_CLOSE(result.y, 50.0, 1e-06);
        BOOST_CHECK_CLOSE(result.distance, 50.0, 1e-06);
    }

    // Point => MultiLineString
    {
        multi_line_string<double> mline {
            {{0, 0}, {0, 100}, {100, 100}, {100, 0}},
            {{50, 0}, {100, 50}}
        };
        point<double> pt {50, 50};
        auto result = op::closest_point(mline, pt);
        BOOST_CHECK_CLOSE(result.x, 75.0, 1e-06);
        BOOST_CHECK_CLOSE(result.y, 25.0, 1e-06);
        BOOST_CHECK_CLOSE(result.distance, 35.3553, 1e-03);
    }

    // Point => Polygon
    {
        polygon<double> poly {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}};
        {
            // point inside polygon
            point<double> pt {0.5, 0.25};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 0.5, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 0.25, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 0.0, 1e-06);
        }

        {
            // point outside polygon
            point<double> pt {1.25, 0.5};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 1.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 0.5, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 0.25, 1e-06);
        }
        {
            // point outside polygon
            point<double> pt {4.0, 5.0};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 1.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 1.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 5.0, 1e-06);
        }
        {
            // point on polygon boundary
            point<double> pt {0, 0.4};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 0.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 0.4, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 0.0, 1e-06);
        }
    }

    // Point => MultiPolygon
    {
        multi_polygon<double> mpoly {
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}
        };
        point<double> pt {4.0, 5.0};
        auto result = op::closest_point(mpoly, pt);
        BOOST_CHECK_CLOSE(result.x, 3.0, 1e-06);
        BOOST_CHECK_CLOSE(result.y, 3.0, 1e-06);
        BOOST_CHECK_CLOSE(result.distance, std::sqrt(5.0), 1e-03);
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
            BOOST_CHECK_CLOSE(result.x, 0.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 0.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 5.0, 1e-06);
        }
        {
            auto result = op::closest_point(p2, p1);
            BOOST_CHECK_CLOSE(result.x, 3.0, 1e-0);
            BOOST_CHECK_CLOSE(result.y, 4.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 5.0, 1e-06);
        }
    }

    // Point => MultiPoint
    {
        point<std::int64_t> p{0, 0};
        multi_point<std::int64_t> mp{{-1,-1}, {1, 1}};
        auto result = op::closest_point(mp, p);
        BOOST_CHECK_CLOSE(result.x, -1.0, 1e-6);
        BOOST_CHECK_CLOSE(result.y, -1.0, 1e-6);
        BOOST_CHECK_CLOSE(result.distance, 1.41421356, 1e-6);
    }

    // Point => LineString
    {
        line_string<std::int64_t> line {{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        point<std::int64_t> pt {50, 50};
        auto result = op::closest_point(line, pt);
        BOOST_CHECK_CLOSE(result.x, 0.0, 1e-06);
        BOOST_CHECK_CLOSE(result.y, 50.0, 1e-06);
        BOOST_CHECK_CLOSE(result.distance, 50.0, 1e-06);
    }

    // Point => MultiLineString
    {
        multi_line_string<std::int64_t> mline {
            {{0, 0}, {0, 100}, {100, 100}, {100, 0}},
            {{50, 0}, {100, 50}}
        };
        point<std::int64_t> pt {50, 50};
        auto result = op::closest_point(mline, pt);
        BOOST_CHECK_CLOSE(result.x, 75.0, 1e-06);
        BOOST_CHECK_CLOSE(result.y, 25.0, 1e-06);
        BOOST_CHECK_CLOSE(result.distance, 35.3553, 1e-03);
    }

    // Point => Polygon
    {
        polygon<std::int64_t> poly {{{0, 0},{100, 0},{100, 100},{0, 100}, {0, 0}}};

        {
            // point inside polygon
            point<std::int64_t> pt {50, 25};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 50.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 25.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 0.0, 1e-06);
        }

        {
            // point outside polygon
            point<std::int64_t> pt {125, 50};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 100.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 50.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 25.0, 1e-06);
        }
        {
            // point outside polygon
            point<std::int64_t> pt {400, 500};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 100.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 100.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 500.0, 1e-06);
        }
        {
            // point on polygon boundary
            point<std::int64_t> pt {0, 40};
            auto result = op::closest_point(poly, pt);
            BOOST_CHECK_CLOSE(result.x, 0.0, 1e-06);
            BOOST_CHECK_CLOSE(result.y, 40.0, 1e-06);
            BOOST_CHECK_CLOSE(result.distance, 0.0, 1e-06);
        }
    }
     // Point => MultiPolygon
    {
        multi_polygon<std::int64_t> mpoly {
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}
        };
        point<std::int64_t> pt {4, 5};
        auto result = op::closest_point(mpoly, pt);
        BOOST_CHECK_CLOSE(result.x, 3.0, 1e-06);
        BOOST_CHECK_CLOSE(result.y, 3.0, 1e-06);
        BOOST_CHECK_CLOSE(result.distance, std::sqrt(5.0), 1e-03);
    }
}

}// ns testing

BOOST_AUTO_TEST_CASE(closest_point)
{
    testing::test_closest_point_d();
    testing::test_closest_point_int64();
}

BOOST_AUTO_TEST_SUITE_END()
