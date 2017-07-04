//----------------------------------------------------------------------------
/// @file low_level.hpp
/// @brief low level functions of create, destroy, move and merge functions
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_UTIL_LOW_LEVEL_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_UTIL_LOW_LEVEL_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
#include <boost/sort/spinsort/util/low_level.hpp>

namespace boost
{
namespace sort
{
namespace parallel
{
namespace detail
{
namespace util
{
//---------------------------------------------------------------------------
//                         USING SENTENCES
//---------------------------------------------------------------------------
using namespace boost::sort::spinsort::util;
using std::iterator_traits;

//
//-----------------------------------------------------------------------------
//  function : in_place_merge_uncontiguous
/// @brief : merge two uncontiguous buffers, placing the results in the buffers
///          Use an auxiliary buffer pointed by aux
///
/// @param src1 : iterator to the first element of the first buffer
/// @param end_src1 : last iterator  of the first buffer
/// @param src2 : iterator to the first element of the second buffer
/// @param end_src2 : last iterator  of the second buffer
/// @param aux  : iterator to the first element of the auxiliary buffer
/// @param comp : object for to Compare elements
/// @return true : not changes done,  false : changes in the buffers
/// @remarks
//-----------------------------------------------------------------------------
template < class Iter1_t, class Iter2_t, class Iter3_t, class Compare >
bool in_place_merge_uncontiguous (Iter1_t src1, const Iter1_t end_src1,
                                  Iter2_t src2, const Iter2_t end_src2,
                                  Iter3_t aux, Compare comp)
{
    typedef typename iterator_traits< Iter1_t >::value_type type1;
    typedef typename iterator_traits< Iter2_t >::value_type type2;
    typedef typename iterator_traits< Iter3_t >::value_type type3;
    static_assert (std::is_same< type1, type2 >::value,
                   "Incompatible iterators\n");
    static_assert (std::is_same< type3, type2 >::value,
                   "Incompatible iterators\n");

    if (src1 == end_src1 or src2 == end_src2 or
        not comp (*src2, *(end_src1 - 1)))
        return true;

    while (src1 != end_src1 and not comp (*src2, *src1)) ++src1;

    Iter3_t const end_aux = aux + (end_src1 - src1);
    Iter2_t src2_first = src2;
    init_move (aux, src1, end_src1);

    while ((src1 != end_src1) and (src2 != end_src2)) {
        *(src1++) = std::move ((not comp (*src2, *aux)) ? *(aux++) : *(src2++));
    }

    if (src2 == end_src2) {
        while (src1 != end_src1) *(src1++) = std::move (*(aux++));
        init_move (src2_first, aux, end_aux);
    }
    else
    {
        half_merge (aux, end_aux, src2, end_src2, src2_first, comp);
    };
    return false;
};

//
//-----------------------------------------------------------------------------
//  function : in_place_merge
/// @brief : merge two contiguous buffers,using an auxiliary buffer pointed
///          by buf. The results are in src1 and src2
///
/// @param src1: iterator to the first position of the first buffer
/// @param src2: final iterator of the first buffer and first iterator
///              of the second buffer
/// @param end_src2 : final iterator of the second buffer
/// @param buf  : iterator to buffer used as auxiliary memory
/// @param comp : object for to Compare elements
/// @return true : not changes done,  false : changes in the buffers
//-----------------------------------------------------------------------------
template < class Iter1_t, class Iter2_t, class Compare >
bool in_place_merge (Iter1_t src1, Iter1_t src2, Iter1_t end_src2, Iter2_t buf,
                     Compare comp)
{
    typedef typename iterator_traits< Iter1_t >::value_type type1;
    typedef typename iterator_traits< Iter2_t >::value_type type2;
    static_assert (std::is_same< type1, type2 >::value,
                   "Incompatible iterators\n");

    if (src1 == src2 or src2 == end_src2 or not comp (*src2, *(src2 - 1)))
        return true;

    Iter1_t end_src1 = src2;
    while (src1 != end_src1 and not comp (*src2, *src1)) ++src1;

    if (src1 == end_src1) return false;

    size_t nx = end_src1 - src1;
    init_move (buf, src1, end_src1);
    half_merge (buf, buf + nx, src2, end_src2, src1, comp);
    return false;
};
//
//****************************************************************************
}; //    End namespace util
}; //    End namespave detail
}; //    End namespace parallel
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
//
#endif
