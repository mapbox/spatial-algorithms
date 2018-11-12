#include <iostream>
#include <mapbox/geometry/algorithms/predicates.hpp>
#include <mapbox/geometry/box.hpp>
#include <mapbox/geometry/geometry.hpp>

#include <boost/geometry.hpp>
#include <fstream>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/intersection.hpp>

int main ()
{
    using namespace mapbox::geometry;
    line_string<double> line {{70,50},{50,70}};
    polygon<double> poly {
        {{ {0,0}, {100,0}, {100,100}, {0, 100}, {0,0}}},
        {{ {25,25}, {25,75}, {50,75}, {25,25} }},
        {{ {35,25}, {60,75}, {75,75}, {75,25}, {35,25} }}
    };

    std::cerr <<  "Intersects? " << algorithms::intersects(line, poly) << std::endl;
    std::cerr <<  "Disjoint? " << algorithms::disjoint(line, poly) << std::endl;

    // It should work with variant based `mapbox::geometry::geometry<T>` and all permutations also.
    geometry<double> g = line;
    std::cerr <<  "Intersects? " << algorithms::intersects(g, poly) << std::endl;
    std::cerr <<  "Disjoint? " << algorithms::disjoint(poly, g) << std::endl;


    box<double> b{{0,40},{100,60}};

    std::cerr << "A:" << boost::geometry::wkt(poly) << std::endl;
    std::cerr << "B:" << boost::geometry::wkt(b) << std::endl;
    std::ofstream svg("intersection.svg");
    boost::geometry::svg_mapper<mapbox::geometry::point<double>> mapper(svg, 400, 400);
    mapper.add(poly);
    mapper.add(b);
    mapper.map(poly, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2", 5);
    mapper.map(b, "fill-opacity:0.3;fill:rgb(51,51,153);stroke:rgb(51,51,153);stroke-width:2");
    auto result = algorithms::intersection(b, poly);
    for (auto const& pl : result)
    {
        std::cerr << boost::geometry::wkt(pl) << std::endl;
        mapper.add(pl);
        mapper.map(pl, "opacity:0.4;fill:red;stroke:rgb(212,0,0);stroke-width:5");
    }

    return 0;
}
