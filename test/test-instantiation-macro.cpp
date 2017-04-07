#include <mapbox/geometry/algorithms/detail/instantiate_macro.hpp>
#include <iostream>
#include <mapbox/geometry/algorithms/predicates/intersects_impl.hpp>

int main ()
{
    MAPBOX_ALGORITHM_INSTANTIATE(INTERSECTS,
                                 point<double>,
                                 line_string<double>,
                                 polygon<double>);


    MAPBOX_ALGORITHM_INSTANTIATE(DISJOINT,
                                 point<double>,
                                 line_string<double>,
                                 polygon<double>);
    return 0;
}
