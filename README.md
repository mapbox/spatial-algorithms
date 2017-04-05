## Spatial algorithms library for geometry.hpp



```c++

#include <mapbox/geometry/geometry.hpp>
#include <mapbox/geometry/algorithms/predicates.hpp>
#include <iostream>

int main ()
{
    using namespace mapbox::geometry;
    line_string<double> line{ {70,50},{50,70}};
    polygon<double> poly {{{{0,0}, {100,0}, {100,100}, {0, 100}, {0,0}}},
        {{{25,25}, {25,75}, {75,75}, {75, 25}, {25,25} }}};

    std::cerr <<  "Intersects? " << algorithms::intersects(line, poly) << std::endl;
    std::cerr <<  "Disjoint? " << algorithms::disjoint(line, poly) << std::endl;

    // It should work with variant based `mapbox::geometry::geometry<T>` and all permutations also.

    geometry<double> g = line;

    std::cerr <<  "Intersects? " << algorithms::intersects(g, poly) << std::endl;
    std::cerr <<  "Disjoint? " << algorithms::disjoint(poly, g) << std::endl;
    return 0;
}

```
