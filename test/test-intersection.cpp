#include <boost/test/unit_test.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/intersection.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(intersection_tests)

namespace testing {

template <typename T>
void test_intersection()
{
    using namespace mapbox::geometry;
    namespace op = algorithms;
    // Point/Point
    {
        point<T> p1{100,200};
        point<T> p2{100,200};
        // p1
        auto result = op::intersection(p1, p2);
        BOOST_CHECK(result.size() == 1);
        BOOST_CHECK(result.front() == p1);

        p1.x +=1;
        result = op::intersection(p1, p2);
        BOOST_CHECK(result.size() == 0);
    }

    {
        // LineString/LineString
        {
            /*  \ /
                / \
            */
            line_string<T> l1 {{100,100},{200,200}};
            line_string<T> l2 {{200,100},{100,200}};
            auto result = op::intersection(l1, l2);
            BOOST_CHECK(result.size() == 1);
            auto const& l = result.front();
            BOOST_CHECK(l.size() == 2);
            BOOST_CHECK(l[0] == l[1]);
            auto p = point<T>{150,150};
            BOOST_CHECK(l[0] == p);
        }
        {
            /*    /
                //
               /
            */
            line_string<T> l1 {{100,100},{200,200}};
            line_string<T> l2 {{150,150},{250,250}};
            auto result = op::intersection(l1, l2);
            BOOST_CHECK(result.size() == 1);
            auto const& l = result.front();
            auto p1 = point<T>{150,150};
            auto p2 = point<T>{200,200};
            BOOST_CHECK(l.size() == 2);
            BOOST_CHECK(l[0] == p1);
            BOOST_CHECK(l[1] == p2);

            /*
                 /
               /
            */

            l2.front() = point<T>{200,200};
            result = op::intersection(l1, l2);
            BOOST_CHECK(result.size() == 1);
            BOOST_CHECK(result.front().front() == p2);
            BOOST_CHECK(result.front().back() == p2);
        }
    }

#if 0
    // Point/LineString
    {
        point<T> p1{150,150};
        line_string<T> l2{ {100,100}, {200,200}};
        geometry<T> g1 = p1;
        geometry<T> g2 = l2;
        // p1
        BOOST_CHECK(op::intersects(p1, l2));
        BOOST_CHECK(op::intersects(p1, g2));
        // g1
        BOOST_CHECK(op::intersects(g1, l2));
        BOOST_CHECK(op::intersects(g1, g2));
        // l2
        BOOST_CHECK(op::intersects(l2, p1));
        BOOST_CHECK(op::intersects(l2, g1));
        // g2
        BOOST_CHECK(op::intersects(g2, l2));
        BOOST_CHECK(op::intersects(g2, g1));
    }

    // TODO: add missing permutations !!!!!

    // LineString/Polygon
    {
        line_string<T> l1{ {25,70}, {70,30}};
        geometry<T> g1 = l1;

        linear_ring<T> exterior = {{0,0}, {100,0}, {100,100}, {0, 100}, {0,0} };
        linear_ring<T> interior = {{25,25}, {25,75}, {75,75}, {75, 25}, {25,25} };
        polygon<T> poly = { {exterior} , {interior} };

        BOOST_CHECK(op::intersects(l1, poly));
        BOOST_CHECK(op::intersects(poly, l1));
        geometry<T> g2 = poly;
        BOOST_CHECK(op::intersects(g1, g2));
        BOOST_CHECK(op::intersects(g2, g1));
    }

    // MultiPoint/Point
    {
        geometry<T> g1 = multi_point<T>{{100,100}, { 200,100}, {300, 100}};
        geometry<T> g2 = point<T>{200,100};
        BOOST_CHECK(op::intersects(g1, g2));
        BOOST_CHECK(op::intersects(g2, g1));
    }

    // MultiPoint/MultiPoint
    {
        geometry<T> g1 = multi_point<T>{{200,200}, { 100,101}, {300, 300}};
        geometry<T> g2 = multi_point<T>{{100,100}, { 200,100}, {300, 100}};
        BOOST_CHECK(!op::intersects(g1, g2));
    }
    // MultiPoint/LineString
    {
        geometry<T> g1 = multi_point<T>{{200,200}, { 100,101}, {300, 300}};
        geometry<T> g2 = line_string<T>{{100,100}, { 200,100}, {300, 100}};
        BOOST_CHECK(!op::intersects(g1, g2));
        BOOST_CHECK(!op::intersects(g2, g1));
    }
#endif
}
}

BOOST_AUTO_TEST_CASE(intersection)
{
    testing::test_intersection<double>();
    //testing::test_intersection<std::int64_t>();
}

BOOST_AUTO_TEST_SUITE_END()
