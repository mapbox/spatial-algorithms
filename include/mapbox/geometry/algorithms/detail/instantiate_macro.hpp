#pragma once
// boost.preprocessor
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#define MAPBOX_ALGORITHM_INTERSECTS(r, args)                    \
    template bool intersects(BOOST_PP_SEQ_ELEM(0, args) const&, \
                             BOOST_PP_SEQ_ELEM(1, args) const&);

#define MAPBOX_ALGORITHM_DISJOINT(r, args)                    \
    template bool disjoint(BOOST_PP_SEQ_ELEM(0, args) const&, \
                           BOOST_PP_SEQ_ELEM(1, args) const&);

#define MAPBOX_ALGORITHM_EQUALS(r, args)                     \
    template bool equals(BOOST_PP_SEQ_ELEM(0, args) const&,  \
                         BOOST_PP_SEQ_ELEM(1, args) const&);

#define MAPBOX_ALGORITHM_INSTANTIATE(OP, ...) BOOST_PP_SEQ_FOR_EACH_PRODUCT( \
        MAPBOX_ALGORITHM_##OP, \
        (BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))         \
        (BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))        \
