#include <catch.hpp>
#include <cmath>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/closest_point.hpp>

TEST_CASE("closest_point - double")
{
    using namespace mapbox::geometry;
    namespace op = algorithms;
    SECTION("Point => Empty")
    {
        empty e;
        point<double> p1{0.0, 0.0};
        point<double> p2{3.0, 4.0};
        SECTION("Empty, P2")
        {
            auto result = op::closest_point(e, p2);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(0.0));
            CHECK(result.distance == Approx(-1.0));
        }
        SECTION("Empty, P1")
        {
            auto result = op::closest_point(e, p1);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(0.0));
            CHECK(result.distance == Approx(-1.0));
        }
    }

    SECTION("Point => Point")
    {
        point<double> p1{0.0, 0.0};
        point<double> p2{3.0, 4.0};
        SECTION("p1, p2")
        {
            auto result = op::closest_point(p1, p2);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(0.0));
            CHECK(result.distance == Approx(5.0));
        }
        SECTION("p2, p1")
        {
            auto result = op::closest_point(p2, p1);
            CHECK(result.x == Approx(3.0));
            CHECK(result.y == Approx(4.0));
            CHECK(result.distance == Approx(5.0));
        }
    }

    SECTION("Point => MultiPoint")
    {
        point<double> p{0.0, 0.0};
        multi_point<double> mp{{-1.0, -1.0}, {1.0, 1.1}};
        auto result = op::closest_point(mp, p);
        CHECK(result.x == Approx(-1.0));
        CHECK(result.y == Approx(-1.0));
        CHECK(result.distance == Approx(1.41421356));
    }

    SECTION("Point => LineString")
    {
        line_string<double> line{{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        point<double> pt{50, 50};
        auto result = op::closest_point(line, pt);
        CHECK(result.x == Approx(0.0));
        CHECK(result.y == Approx(50.0));
        CHECK(result.distance == Approx(50.0));
    }

    SECTION("Point => MultiLineString")
    {
        multi_line_string<double> mline{
            {{0, 0}, {0, 100}, {100, 100}, {100, 0}},
            {{50, 0}, {100, 50}}};
        point<double> pt{50, 50};
        auto result = op::closest_point(mline, pt);
        CHECK(result.x == Approx(75.0));
        CHECK(result.y == Approx(25.0));
        CHECK(result.distance == Approx(35.3553));
    }

    SECTION("Point => Polygon")
    {
        polygon<double> poly{{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}};
        SECTION("Point inside Polygon")
        {
            point<double> pt{0.5, 0.25};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(0.5));
            CHECK(result.y == Approx(0.25));
            CHECK(result.distance == Approx(0.0));
        }
        SECTION("Point outside Polygon")
        {
            point<double> pt{1.25, 0.5};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(1.0));
            CHECK(result.y == Approx(0.5));
            CHECK(result.distance == Approx(0.25));
        }
        SECTION("Point outside polygon 2")
        {
            point<double> pt{4.0, 5.0};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(1.0));
            CHECK(result.y == Approx(1.0));
            CHECK(result.distance == Approx(5.0));
        }
        SECTION("Point on polygon boundary")
        {
            point<double> pt{0, 0.4};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(0.4));
            CHECK(result.distance == Approx(0.0));
        }
    }

    SECTION("Point => MultiPolygon")
    {
        multi_polygon<double> mpoly{
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}};
        point<double> pt{4.0, 5.0};
        auto result = op::closest_point(mpoly, pt);
        CHECK(result.x == Approx(3.0));
        CHECK(result.y == Approx(3.0));
        CHECK(result.distance == Approx(std::sqrt(5.0)));
    }

    SECTION("Point => Geometry")
    {
        multi_polygon<double> mpoly{
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}};
        geometry<double> geom(std::move(mpoly));
        point<double> pt{4.0, 5.0};
        auto result = op::closest_point(geom, pt);
        CHECK(result.x == Approx(3.0));
        CHECK(result.y == Approx(3.0));
        CHECK(result.distance == Approx(std::sqrt(5.0)));
    }

    SECTION("Point => Geometry Collection")
    {
        multi_polygon<double> mpoly{
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}};
        geometry<double> geom1(std::move(mpoly));
        geometry<double> geom2; // empty geometry
        multi_point<double> mp{{-1, -1}, {1, 1}};
        geometry<double> geom3(std::move(mp));

        geometry_collection<double> gc;
        gc.push_back(geom1);
        gc.push_back(geom2);
        gc.push_back(geom3);

        point<double> pt{4, 5};
        auto result = op::closest_point(gc, pt);
        CHECK(result.x == Approx(3.0));
        CHECK(result.y == Approx(3.0));
        CHECK(result.distance == Approx(std::sqrt(5.0)));

        geometry_collection<double> gc2;
        gc2.push_back(geom2); // First is a empty geometry
        gc2.push_back(geom1);
        gc2.push_back(geom3);

        auto result2 = op::closest_point(gc2, pt);
        CHECK(result2.x == Approx(3.0));
        CHECK(result2.y == Approx(3.0));
        CHECK(result2.distance == Approx(std::sqrt(5.0)));
    }
}

TEST_CASE("closest_point - int64_t")
{
    using namespace mapbox::geometry;
    namespace op = algorithms;
    SECTION("Point => Empty")
    {
        empty e;
        point<std::int64_t> p1{0, 0};
        point<std::int64_t> p2{3, 4};
        SECTION("Empty, P2")
        {
            auto result = op::closest_point(e, p2);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(0.0));
            CHECK(result.distance == Approx(-1.0));
        }
        SECTION("Empty, P1")
        {
            auto result = op::closest_point(e, p1);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(0.0));
            CHECK(result.distance == Approx(-1.0));
        }
    }

    SECTION("Point => Point")
    {
        point<std::int64_t> p1{0, 0};
        point<std::int64_t> p2{3, 4};
        SECTION("p1, p2")
        {
            auto result = op::closest_point(p1, p2);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(0.0));
            CHECK(result.distance == Approx(5.0));
        }
        SECTION("p2, p1")
        {
            auto result = op::closest_point(p2, p1);
            CHECK(result.x == Approx(3.0));
            CHECK(result.y == Approx(4.0));
            CHECK(result.distance == Approx(5.0));
        }
    }

    SECTION("Point => MultiPoint")
    {
        point<std::int64_t> p{0, 0};
        multi_point<std::int64_t> mp{{-1, -1}, {1, 1}};
        auto result = op::closest_point(mp, p);
        CHECK(result.x == Approx(-1.0));
        CHECK(result.y == Approx(-1.0));
        CHECK(result.distance == Approx(1.41421356));
    }

    SECTION("Point => LineString")
    {
        line_string<std::int64_t> line{{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        point<std::int64_t> pt{50, 50};
        auto result = op::closest_point(line, pt);
        CHECK(result.x == Approx(0.0));
        CHECK(result.y == Approx(50.0));
        CHECK(result.distance == Approx(50.0));
    }

    SECTION("Point => MultiLineString")
    {
        multi_line_string<std::int64_t> mline{
            {{0, 0}, {0, 100}, {100, 100}, {100, 0}},
            {{50, 0}, {100, 50}}};
        point<std::int64_t> pt{50, 50};
        auto result = op::closest_point(mline, pt);
        CHECK(result.x == Approx(75.0));
        CHECK(result.y == Approx(25.0));
        CHECK(result.distance == Approx(35.3553));
    }

    SECTION("Point => Polygon")
    {
        polygon<std::int64_t> poly{{{0, 0}, {100, 0}, {100, 100}, {0, 100}, {0, 0}}};
        SECTION("Point inside Polygon")
        {
            point<std::int64_t> pt{50, 25};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(50.0));
            CHECK(result.y == Approx(25.0));
            CHECK(result.distance == Approx(0.0));
        }
        SECTION("Point outside Polygon")
        {
            point<std::int64_t> pt{125, 50};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(100.0));
            CHECK(result.y == Approx(50.0));
            CHECK(result.distance == Approx(25.0));
        }
        SECTION("Point outside polygon 2")
        {
            point<std::int64_t> pt{400, 500};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(100.0));
            CHECK(result.y == Approx(100.0));
            CHECK(result.distance == Approx(500.0));
        }
        SECTION("Point on polygon boundary")
        {
            point<std::int64_t> pt{0, 40};
            auto result = op::closest_point(poly, pt);
            CHECK(result.x == Approx(0.0));
            CHECK(result.y == Approx(40.0));
            CHECK(result.distance == Approx(0.0));
        }
    }

    SECTION("Point => MultiPolygon")
    {
        multi_polygon<std::int64_t> mpoly{
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}};
        point<std::int64_t> pt{4, 5};
        auto result = op::closest_point(mpoly, pt);
        CHECK(result.x == Approx(3.0));
        CHECK(result.y == Approx(3.0));
        CHECK(result.distance == Approx(std::sqrt(5.0)));
    }

    SECTION("Point => Geometry")
    {
        multi_polygon<std::int64_t> mpoly{
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}};
        geometry<std::int64_t> geom(std::move(mpoly));
        point<std::int64_t> pt{4, 5};
        auto result = op::closest_point(geom, pt);
        CHECK(result.x == Approx(3.0));
        CHECK(result.y == Approx(3.0));
        CHECK(result.distance == Approx(std::sqrt(5.0)));
    }

    SECTION("Point => Geometry Collection")
    {
        multi_polygon<std::int64_t> mpoly{
            {{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}},
            {{{2, 2}, {3, 2}, {3, 3}, {2, 3}, {2, 2}}}};
        geometry<std::int64_t> geom1(std::move(mpoly));
        geometry<std::int64_t> geom2; // empty geometry
        multi_point<std::int64_t> mp{{-1, -1}, {1, 1}};
        geometry<std::int64_t> geom3(std::move(mp));

        geometry_collection<std::int64_t> gc;
        gc.push_back(geom1);
        gc.push_back(geom2);
        gc.push_back(geom3);

        point<std::int64_t> pt{4, 5};
        auto result = op::closest_point(gc, pt);
        CHECK(result.x == Approx(3.0));
        CHECK(result.y == Approx(3.0));
        CHECK(result.distance == Approx(std::sqrt(5.0)));

        geometry_collection<std::int64_t> gc2;
        gc2.push_back(geom2); // First is a empty geometry
        gc2.push_back(geom1);
        gc2.push_back(geom3);

        auto result2 = op::closest_point(gc2, pt);
        CHECK(result2.x == Approx(3.0));
        CHECK(result2.y == Approx(3.0));
        CHECK(result2.distance == Approx(std::sqrt(5.0)));
    }
}
