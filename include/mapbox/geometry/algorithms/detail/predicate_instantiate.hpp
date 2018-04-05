#pragma once

// boost.preprocessor
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#define MAPBOX_ALGORITHM_INSTANTIATE(OP, ...) BOOST_PP_SEQ_FOR_EACH_PRODUCT( \
        MAPBOX_ALGORITHM_##OP, \
        (BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))         \
        (BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))))

#define MAPBOX_ALGORITHM_INTERSECTS(r, product)                                         \
    template bool mapbox::algorithms::intersects(BOOST_PP_SEQ_ELEM(0, product) const &, \
                                                 BOOST_PP_SEQ_ELEM(1, product) const &);

#define MAPBOX_ALGORITHM_DISJOINT(r, product)                                         \
    template bool mapbox::algorithms::disjoint(BOOST_PP_SEQ_ELEM(0, product) const &, \
                                               BOOST_PP_SEQ_ELEM(1, product) const &);

#define MAPBOX_ALGORITHM_EQUALS(r, product)                                         \
    template bool mapbox::algorithms::equals(BOOST_PP_SEQ_ELEM(0, product) const &, \
                                             BOOST_PP_SEQ_ELEM(1, product) const &);
