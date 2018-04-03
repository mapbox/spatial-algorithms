Welcome to the spatial-algorithms wiki!


### Spatial algorithms library in C++

Why 'spatial algorithms`?

We're using spatial analysis algorithms across most of our projects - it's our domain.
When it comes to c++, we're also having a great degree of [duplication](https://github.com/mapbox/cpp-internal/issues/22) (TODO: add Mapnik algos to the list).
One of the goals of this project is to put commonly used algorithms under one umbrella. This would allow easy access, and encourage collaboration as there'll be a single point of reference. This is not to discourage anyone writing her/his own implementations! Rather, let's share successful implentations and knowledge we have accumulated so far.

### Design principles applied

* Modular design.

* Only use what you need if performance and binary size is paramount.

* Easy to connect common algorithms into custom geometry processing pipe-lines.

* High-level interface specifically targeting [geometry.hpp](https://github.com/mapbox/geometry.hpp).

* Easy to add/replace individual implementations.

* Provide multiple implementations where it makes sense.

* Comprehensive test and benchmarking frameworks.


Coding such a beast from scratch is a mammoth task, but here is the catch: we will piggy-back on the prior art. By [adapting](https://github.com/mapbox/spatial-algorithms/blob/master/include/mapbox/geometry/algorithms/detail/boost_adapters.hpp) our [geometry.hpp](https://github.com/mapbox/geometry.hpp) to [boost-geometry](http://www.boost.org/doc/libs/1_63_0/libs/geometry/doc/html/index.html) we crank it up to 10 in no time. What's left is go to 11 with our own optimised implementations but only when it makes sense. Let's be smart.

The current state of the library is [here](https://github.com/mapbox/spatial-algorithms).

To address the points above we've applied used and tried `*.hpp *_impl *.cpp` approach. This way the library could be used as a `header-only` but also as a pre-compiled archive plus high-level interface (developer APIs) that works seamlessly with [geometry.hpp](https://github.com/mapbox/geometry.hpp).

The whole effort is at the experimental stage but it's already usable. Getting it 100% right will require some iterations.

Below are some points that came up so far (feel free to add more!)

##### Supporting all or some posible geometry and coordinate types.

The number of possible permutations quickly gets out of hand. Consider our basic geomery types (let's just ignore `geometry_collection`):
    `point`, `line_string`, `polygon` plus corresponding `multi` types - `multi_point`, `multi_line_string`, `multi_polygon`.

Number of unique pairs in a set is `n(n-1)/2` (implying operations are commutative which is not always the case).
For our geometry types it yields 15. This is 15 different function signatures. Supporting more than just `double` as coordinate_type makes the compiled version potentially rather large.

One solution is to support `double` precision coordinates for the compiled version. This matches `GeoJSON` which is a basis for the `geometry.hpp`. Any extra coordinate types (e.g `std::int64_t` used in MVT/Wagyu) can be still used via `header-only` lib.

We're supporting variant based `geometry` type.

##### Return values

Spatial set operations on two geometries result in collection of geometries. Those can be represented as `multi` geometries or just a container of geometries . Currently we're using `std::vector<GeometryType>` for simplicity. From another angle, set operations can return degenerate geometries e.g consider intersecting `line_strings`. The result can be an empty set or a sequence of `line_strings` some of which can have coincident coordinates  and can be represented as `points`.

##### TODO: add more WIP
