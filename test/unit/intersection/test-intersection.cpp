#include <boost/test/unit_test.hpp>
#include <mapbox/geometry/geometry.hpp>
#include <mapbox/geometry/box.hpp>
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

    // LineString/LineString
    {
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
    // Polygon/Polygon
    {
        polygon<T> poly1 {{{-100,0},{100,0},{0,100},{-100,0}}};
        polygon<T> poly2 {{{0,50},{100,150},{-100,150},{0,50}}};

        // A ∩ B
        {

            auto result = op::intersection(poly1, poly2);
            BOOST_CHECK(result.size() == 1);

            // expected result POLYGON((-25 75,0 50,25 75,0 100,-25 75))
            linear_ring<T> expected {{-25,75},{0,50}, {25,75},{0,100},{-25,75}};
            for (auto const& poly : result)
            {
                for (auto const& ring : poly)
                {
                    BOOST_CHECK(ring.size() == expected.size());
                    std::size_t index = 0;
                    for (auto const& p : ring)
                    {
                        BOOST_CHECK(p.x == expected[index].x);
                        BOOST_CHECK(p.y == expected[index++].y);
                    }
                }
            }
        }
        // intersection is commutative; thus A ∩ B = B ∩ A.
        // B ∩ A
        {
            auto result = op::intersection(poly2, poly1);
            BOOST_CHECK(result.size() == 1);

            // expected result POLYGON((-25 75,0 50,25 75,0 100,-25 75))
            linear_ring<T> expected {{-25,75},{0,50}, {25,75},{0,100},{-25,75}};
            for (auto const& poly : result)
            {
                for (auto const& ring : poly)
                {
                    BOOST_CHECK(ring.size() == expected.size());
                    std::size_t index = 0;
                    for (auto const& p : ring)
                    {
                        BOOST_CHECK(p.x == expected[index].x);
                        BOOST_CHECK(p.y == expected[index++].y);
                    }
                }
            }
        }
    }

    // Box/Polygon + Polygon/Box
    //
    // A : POLYGON((0 0,100 0,100 100,0 100,0 0),(25 25,25 75,50 75,25 25),(35 25,60 75,75 75,75 25,35 25))
    // BOX : POLYGON((0 40,0 60,100 60,100 40,0 40))
    // A ∩ BOX == BOX ∩ A : POLYGON((0 60,0 40,25 40,25 60,0 60)) POLYGON((100 60,75 60,75 40,100 40,100 60)) POLYGON((42.5 60,32.5 40,42.5 40,52.5 60,42.5 60))
    {
         polygon<double> poly {
             {{ {0,0}, {100,0}, {100,100}, {0, 100}, {0,0}}},
             {{ {25,25}, {25,75}, {50,75}, {25,25} }},
             {{ {35,25}, {60,75}, {75,75}, {75,25}, {35,25} }}
         };

         box<double> b{{0,40},{100,60}};

         auto result1 = algorithms::intersection(b, poly);
         auto result2 = algorithms::intersection(poly, b);
         BOOST_CHECK(result1 == result2);
         BOOST_CHECK(result1.size() == 3);

         polygon<double> p0{{{0,60},{0,40},{25,40},{25,60},{0,60}}};
         polygon<double> p1{{{100,60},{75,60},{75,40},{100,40},{100,60}}};
         polygon<double> p2{{{42.5,60},{32.5,40},{42.5,40},{52.5,60},{42.5,60}}};
         BOOST_CHECK(result1[0] == p0);
         BOOST_CHECK(result1[1] == p1);
         BOOST_CHECK(result1[2] == p2);
         BOOST_CHECK(result2[0] == p0);
         BOOST_CHECK(result2[1] == p1);
         BOOST_CHECK(result2[2] == p2);

    }
}
}

BOOST_AUTO_TEST_CASE(intersection)
{
    testing::test_intersection<double>();
    testing::test_intersection<std::int64_t>();
}

BOOST_AUTO_TEST_SUITE_END()
