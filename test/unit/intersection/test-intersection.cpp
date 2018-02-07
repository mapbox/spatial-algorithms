#include <catch.hpp>
#include "../util/check_equal.hpp"

#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/intersection.hpp>

template <typename T>
void test_intersection()
{
    using namespace mapbox::geometry;
    namespace op = algorithms;
    SECTION("Point/Point")
    {
        point<T> p1{100, 200};
        point<T> p2{100, 200};
        // p1
        auto result = op::intersection(p1, p2);
        CHECK(result.size() == 1);
        CHECK(result.front() == p1);

        p1.x += 1;
        result = op::intersection(p1, p2);
        CHECK(result.size() == 0);
    }

    SECTION("LineString/LineString")
    {
        SECTION("crossing")
        {
            /*  \ /
                / \
            */
            line_string<T> l1{{100, 100}, {200, 200}};
            line_string<T> l2{{200, 100}, {100, 200}};
            auto result = op::intersection(l1, l2);
            CHECK(result.size() == 1);
            auto const& l = result.front();
            CHECK(l.size() == 2);
            CHECK(l[0] == l[1]);
            auto p = point<T>{150, 150};
            CHECK(l[0] == p);
        }
        SECTION("Overlapping lines")
        {
            /*    /
                //
               /
            */
            line_string<T> l1{{100, 100}, {200, 200}};
            line_string<T> l2{{150, 150}, {250, 250}};
            auto result = op::intersection(l1, l2);
            CHECK(result.size() == 1);
            auto const& l = result.front();
            auto p1 = point<T>{150, 150};
            auto p2 = point<T>{200, 200};
            CHECK(l.size() == 2);
            CHECK(l[0] == p1);
            CHECK(l[1] == p2);

            /*
                 /
               /
            */

            l2.front() = point<T>{200, 200};
            result = op::intersection(l1, l2);
            CHECK(result.size() == 1);
            CHECK(result.front().front() == p2);
            CHECK(result.front().back() == p2);
        }
    }
    SECTION("Polygon/Polygon")
    {
        polygon<T> poly1{{{-100, 0}, {100, 0}, {0, 100}, {-100, 0}}};
        polygon<T> poly2{{{0, 50}, {100, 150}, {-100, 150}, {0, 50}}};

        SECTION("A ∩ B")
        {

            auto result = op::intersection(poly1, poly2);
            CHECK(result.size() == 1);

            // expected result POLYGON((-25 75,0 50,25 75,0 100,-25 75))
            linear_ring<T> expected{{-25, 75}, {0, 50}, {25, 75}, {0, 100}, {-25, 75}};
            for (auto const& poly : result)
            {
                for (auto const& ring : poly)
                {
                    CHECK(ring.size() == expected.size());
                    std::size_t index = 0;
                    for (auto const& p : ring)
                    {
                        check_equal(p, expected[index++]);
                    }
                }
            }
        }
        // intersection is commutative; thus A ∩ B = B ∩ A.
        SECTION("B ∩ A")
        {
            auto result = op::intersection(poly2, poly1);
            CHECK(result.size() == 1);

            // expected result POLYGON((-25 75,0 50,25 75,0 100,-25 75))
            linear_ring<T> expected{{-25, 75}, {0, 50}, {25, 75}, {0, 100}, {-25, 75}};
            for (auto const& poly : result)
            {
                for (auto const& ring : poly)
                {
                    CHECK(ring.size() == expected.size());
                    std::size_t index = 0;
                    for (auto const& p : ring)
                    {
                        check_equal(p, expected[index++]);
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
    SECTION("Box/Polygon + Polygon/Box")
    {
        polygon<double> poly{
            {{{0, 0}, {100, 0}, {100, 100}, {0, 100}, {0, 0}}},
            {{{25, 25}, {25, 75}, {50, 75}, {25, 25}}},
            {{{35, 25}, {60, 75}, {75, 75}, {75, 25}, {35, 25}}}};

        box<double> b{{0, 40}, {100, 60}};

        auto result1 = algorithms::intersection(b, poly);
        auto result2 = algorithms::intersection(poly, b);
        CHECK(result1 == result2);
        CHECK(result1.size() == 3);

        polygon<double> p0{{{0, 60}, {0, 40}, {25, 40}, {25, 60}, {0, 60}}};
        polygon<double> p1{{{100, 60}, {75, 60}, {75, 40}, {100, 40}, {100, 60}}};
        polygon<double> p2{{{42.5, 60}, {32.5, 40}, {42.5, 40}, {52.5, 60}, {42.5, 60}}};
        CHECK(result1[0] == p0);
        CHECK(result1[1] == p1);
        CHECK(result1[2] == p2);
        CHECK(result2[0] == p0);
        CHECK(result2[1] == p1);
        CHECK(result2[2] == p2);
    }
}

TEST_CASE("intersection double")
{
    test_intersection<double>();
}

TEST_CASE("intersection int64_t")
{
    test_intersection<std::int64_t>();
}
