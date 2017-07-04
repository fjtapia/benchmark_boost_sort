//----------------------------------------------------------------------------
/// @file metaprog.hpp
/// @brief This file contains the description of several functions
///         metaprogrammed
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_UTIL_METAPROG_HPP
#define __BOOST_SORT_UTIL_METAPROG_HPP

#include <boost/sort/util/definition.hpp>
#include <boost/sort/util/config.hpp>
#include <cassert>

//---------------------------------------------------------------------------
// The HW align is defined by the HW architecture. Alwais is a power of 2
// The value of PW2_HW_ALIGN is the power of two of the size of the alignment
//
// Value    Number of bytes
// ------------------------------
//  0       1
//  1       2
//  2       4
//  3       8
//  4       16
//  5       32
//
// In the Intel x64 the value is 4
//---------------------------------------------------------------------------


#ifndef PW2_HW_ALIGN
#define PW2_HW_ALIGN 4
#endif // PW2_HW_ALIGN


namespace boost
{
namespace sort
{
namespace util
{
namespace metaprog
{
//##########################################################################
//                                                                        ##
//                G L O B A L     D E C L A R A T I O N S                 ##
//                                                                        ##
//##########################################################################
//
//---------------------------------------------------------------------------
//  function : MASK
/// @brief Calculate the mask for a number of bits
/// @param [in] NBits : Number to examine
/// @exception none
/// @return Mask
/// @remarks
//---------------------------------------------------------------------------
static constexpr inline uint32_t MASK_32 ( uint32_t NBits) noexcept
{   //--------------------------- begin ---------------------
    return ((1U<<NBits)-1);
};
//---------------------------------------------------------------------------
//  function : Mask64
/// @brief Calculate the mask for a number of bits
/// @param [in] NBits : Number to examine
/// @exception none
/// @return Mask
/// @remarks
//---------------------------------------------------------------------------
static constexpr inline uint64_t MASK_64 ( uint64_t NBits) noexcept
{   //------------------------------- begin -------------------
    return ((1ULL<<NBits)-1);
};
//---------------------------------------------------------------------------
//  function : MS1B_32
/// @brief Obtain the position of the most significant one in N
/// @param [in] N : Number to examine
/// @exception none
/// @return Position of the first one
/// @remarks
//---------------------------------------------------------------------------
template <int NBits = 16 >
static constexpr inline int MS1B_32 ( uint32_t N , int Pos =0) noexcept
{   //------------------ begin ----------------------------
#if __DEBUG_CNTREE != 0
    static_assert ( NBits < 32, " NBits too big ");
#endif
    return (((N>>Pos)& (~MASK_32(NBits)))== 0 )?
              MS1B_32<(NBits>>1)>(N,Pos):
              MS1B_32<(NBits>>1)>(N,Pos+NBits);
};
template< >
constexpr inline int MS1B_32<0> ( uint32_t  , int Pos) noexcept
{   return Pos ;
};

//---------------------------------------------------------------------------
//  function : MS1B_64
/// @brief Obtain the position of the most significant one in N
/// @param [in] N : Number to examine
/// @exception none
/// @return Position of the first one
//---------------------------------------------------------------------------
template <int NBits = 32 >
static constexpr inline int MS1B_64 ( uint64_t N , int Pos =0) noexcept
{   //------------------ begin ----------------------------
#if __DEBUG_CNTREE != 0
    static_assert ( NBits < 64, " NBits too big ");
#endif
    return (((N>>Pos)& (~MASK_64(NBits)))== 0 )?
              MS1B_64<(NBits>>1)>(N,Pos):
              MS1B_64<(NBits>>1)>(N,Pos+NBits);
};
template<>
constexpr inline int MS1B_64<0> ( uint64_t  , int Pos) noexcept
{   return Pos ;
};
//##########################################################################
//                                                                        ##
//                    G L O B A L     V A R I B L E S                     ##
//                                                                        ##
//##########################################################################
constexpr static uint32_t const DeBruijn_32[32] =
{   0 , 1 , 28, 2 , 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4 , 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6 , 11, 5 , 10, 9
};
constexpr static const uint32_t DeBruijn_64[64] =
{   63,  0, 58,  1, 59, 47, 53,  2,
    60, 39, 48, 27, 54, 33, 42,  3,
    61, 51, 37, 40, 49, 18, 28, 20,
    55, 30, 34, 11, 43, 14, 22,  4,
    62, 57, 46, 52, 38, 26, 32, 41,
    50, 36, 17, 19, 29, 10, 13, 21,
    56, 45, 25, 31, 35, 16,  9, 12,
    44, 24, 15,  8, 23,  7,  6,  5
};

static constexpr const uint32_t TMSB [256] =
{   0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};
//
//***************************************************************************
};//    End namespace metaprog
};//    End namespace util
};//    End namespace countertree
};//    End namespace boost
//***************************************************************************
//
#endif
