//----------------------------------------------------------------------------
/// @file test_flat_stable_sort.cpp
/// @brief test program of the flat_stable_sort algorithm
///
/// @author Copyright (c) 2017 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <boost/sort/flat_stable_sort/flat_stable_sort.hpp>
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/test_tools.hpp>


using boost::sort::flat_internal::flat_stable_sort;
using boost::sort::common::range;
using boost::sort::common::util::circular_buffer;
/*
void test1 ( )
{
    //std::mt19937_64 my_rand (0);
    typedef std::vector<uint64_t>			vector_t ;
    typedef typename vector_t::iterator 	iter_t;
    typedef std::less< uint64_t > 			compare;
    //typedef range< iter_t > 				range_it;

	vector_t VA = { 2, 17, 4, 15, 6, 13, 8, 11,10, 9, 12,
			        7, 14, 5, 16, 3, 18, 1, 24, 20, 22};
	//vector_t VA = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 1, 3,
	//		        5, 7, 9, 11, 13, 15, 17, 19};

	flat_stable_sort<iter_t, compare,2> fss ( VA.begin(), VA.end());
}
*/

struct xk
{
    unsigned tail : 4;
    unsigned num : 28;
    bool operator< (xk A) const { return (num < A.num); };
};

void test1 ( )
{
    std::mt19937_64 my_rand (0);
    typedef typename std::vector< uint64_t >::iterator iter_t;
    typedef std::less< uint64_t > compare;

    std::vector< uint64_t > V1, V2;
    uint32_t NELEM = 0;

    NELEM = 40;
    for (uint32_t i = 0; i < NELEM; ++i) {
        V1.push_back (my_rand ( ) % 10000);
    };
    V2 = V1;
    flat_stable_sort<iter_t, compare,2> fs0 (V2.begin ( ), V2.end ( ), compare ( ));
    std::sort (V1.begin ( ), V1.end ( ));

    for (uint32_t i = 0; i < NELEM; ++i)
    {	BOOST_CHECK (V1[ i ] == V2[ i ]);
    };


    V1.clear ( );
    V2.clear ( );
    NELEM = 75;

    for (uint32_t i = 0; i < NELEM; ++i) {
        V1.push_back (my_rand ( ) % 10000);
    };
    V2 = V1;
    flat_stable_sort<iter_t, compare,2> fs1 (V2.begin ( ), V2.end ( ), compare ( ));
    std::sort (V1.begin ( ), V1.end ( ));

    for (uint32_t i = 0; i < NELEM; ++i)
    {	BOOST_CHECK (V1[i] == V2[i]);
    };


    V1.clear ( );
    V2.clear ( );
    NELEM = 200;

    for (uint32_t i = 0; i < NELEM; ++i) {
        V1.push_back (my_rand ( ) % 10000);
    };
    V2 = V1;
    flat_stable_sort<iter_t, compare,2> fs2 (V2.begin ( ), V2.end ( ), compare ( ));
    std::sort (V1.begin ( ), V1.end ( ));

    for (uint32_t i = 0; i < NELEM; ++i)
    {	BOOST_CHECK (V1[ i ] == V2[ i ]);
    };


    V1.clear ( );
    V2.clear ( );
    NELEM = 400;

    for (uint32_t i = 0; i < NELEM; ++i) {
        V1.push_back (my_rand ( ) % 10000);
    };
    V2 = V1;
    flat_stable_sort<iter_t, compare,2> fs3 (V2.begin ( ), V2.end ( ), compare ( ));
    std::sort (V1.begin ( ), V1.end ( ));

    for (uint32_t i = 0; i < NELEM; ++i)
    {	BOOST_CHECK (V1[ i ] == V2[ i ]);
    };
};

void test2 ( )
{
    uint64_t V1[ 300 ];
    typedef std::less< uint64_t > compare;
    compare comp;

    for (uint32_t i = 0; i < 200; ++i) V1[ i ] = i;

    flat_stable_sort<uint64_t *, compare,4> (&V1[ 0 ], &V1[ 200 ], comp);
    for (unsigned i = 1; i < 200; i++) {
        BOOST_CHECK (V1[ i - 1 ] <= V1[ i ]);
    };

    for (uint32_t i = 0; i < 200; ++i) V1[ i ] = 199 - i;
    flat_stable_sort<uint64_t *, compare,4> (&V1[ 0 ], &V1[ 200 ], comp);
    for (unsigned i = 1; i < 200; i++) {
        BOOST_CHECK (V1[ i - 1 ] <= V1[ i ]);
    };

    for (uint32_t i = 0; i < 300; ++i) V1[ i ] = 299 - i;

    flat_stable_sort<uint64_t *, compare,4> (&V1[ 0 ], &V1[ 300 ], comp);
    for (unsigned i = 1; i < 300; i++) {
        BOOST_CHECK (V1[ i - 1 ] <= V1[ i ]);
    };

    for (uint32_t i = 0; i < 300; ++i) V1[ i ] = 88;

    flat_stable_sort<uint64_t *, compare,4> (&V1[ 0 ], &V1[ 300 ], comp);
    for (unsigned i = 1; i < 300; i++) {
        BOOST_CHECK (V1[ i - 1 ] <= V1[ i ]);
    };
};

void test3 ( )
{
    typedef typename std::vector< xk >::iterator iter_t;
    typedef std::less< xk > compare_t;
    std::mt19937_64 my_rand (0);

    const uint32_t NMAX = 500000;


    std::vector< xk > V1, V2, V3;
    V1.reserve (NMAX);
    for (uint32_t i = 0; i < 8; ++i)
    {
        for (uint32_t k = 0; k < NMAX; ++k)
        {
            uint32_t NM = my_rand ( );
            xk G;
            G.num = NM >> 3;
            G.tail = i;
            V1.push_back (G);
        };
    };
    V3 = V2 = V1;
    flat_stable_sort< iter_t, compare_t, 8 > (V1.begin ( ), V1.end ( ), compare_t ( ));
    std::stable_sort (V2.begin ( ), V2.end ( ));

    BOOST_CHECK (V1.size ( ) == V2.size ( ));
    for (uint32_t i = 0; i < V1.size ( ); ++i) {
        BOOST_CHECK (V1[ i ].num == V2[ i ].num and
                     V1[ i ].tail == V2[ i ].tail);
    };
};

void test4 (void)
{
    typedef std::less< uint64_t > compare_t;
    typedef typename std::vector< uint64_t >::iterator iter_t;

    const uint32_t NElem = 500000;
    std::vector< uint64_t > V1;
    std::mt19937_64 my_rand (0);
    compare_t comp;

    for (uint32_t i = 0; i < NElem; ++i) V1.push_back (my_rand ( ) % NElem);

    flat_stable_sort< iter_t, compare_t, 9 > (V1.begin ( ), V1.end ( ), comp);
    for (unsigned i = 1; i < NElem; i++) {
        BOOST_CHECK (V1[ i - 1 ] <= V1[ i ]);
    };

    V1.clear ( );
    for (uint32_t i = 0; i < NElem; ++i) V1.push_back (i);
    flat_stable_sort< iter_t, compare_t, 9 > (V1.begin ( ), V1.end ( ), comp);
    for (unsigned i = 1; i < NElem; i++) {
        BOOST_CHECK (V1[ i - 1 ] <= V1[ i ]);
    };

    V1.clear ( );
    for (uint32_t i = 0; i < NElem; ++i) V1.push_back (NElem - i);
    flat_stable_sort< iter_t, compare_t, 9 > (V1.begin ( ), V1.end ( ), comp);
    for (unsigned i = 1; i < NElem; i++) {
        BOOST_CHECK (V1[ i - 1 ] <= V1[ i ]);
    };

    V1.clear ( );
    for (uint32_t i = 0; i < NElem; ++i) V1.push_back (1000);
    flat_stable_sort< iter_t, compare_t, 9 > (V1.begin ( ), V1.end ( ), comp);
    for (unsigned i = 1; i < NElem; i++) {
        BOOST_CHECK (V1[ i - 1 ] == V1[ i ]);
    };
};

void test5 (void)
{
    typedef std::vector< uint64_t >::iterator iter_t;
    typedef std::less< uint64_t > compare;

    const uint32_t KMax = 500000;

    std::vector< uint64_t > K, M;
    std::mt19937_64 my_rand (0);
    compare comp;
    circular_buffer <uint64_t,10> circ ;

    for (uint32_t i = 0; i < KMax; ++i) K.push_back (my_rand ( ));
    M = K;


    flat_stable_sort< iter_t, compare, 9 > (K.begin ( ), K.end ( ), comp, &circ);

    std::stable_sort (M.begin ( ), M.end ( ), comp);
    for (unsigned i = 0; i < KMax; i++) BOOST_CHECK (M[ i ] == K[ i ]);
};

void test6 (void)
{
    typedef std::vector< uint64_t >::iterator iter_t;
    typedef std::less< uint64_t > compare_t;
    std::vector< uint64_t > V;

    for (uint32_t i = 0; i < 2083333; ++i) V.push_back (i);
    flat_stable_sort< iter_t, compare_t , 9> (V.begin ( ), V.end ( ), compare_t ( ));
    for (uint32_t i = 0; i < V.size ( ); ++i) {
        BOOST_CHECK (V[ i ] == i);
    };
};

void test7 (void)
{
    typedef typename std::vector< uint64_t >::iterator iter_t;
    typedef std::less< uint64_t > compare_t;

    compare_t comp;
    const uint32_t NELEM = 416667;
    const uint32_t N1 = (NELEM + 1) / 2;
    std::vector< uint64_t > A;

    for (uint32_t i = 0; i < 1000; ++i) A.push_back (0);
    for (uint32_t i = 0; i < NELEM; ++i) A.push_back (NELEM - i);
    for (uint32_t i = 0; i < 1000; ++i) A.push_back (0);

    flat_stable_sort< iter_t, compare_t, 9 > (A.begin ( ) + 1000,
                                    A.begin ( ) + (1000 + NELEM), comp);

    for (iter_t it = A.begin ( ) + 1000; it != A.begin ( ) + (1000 + NELEM);
         ++it)
    {
        BOOST_CHECK ((*(it - 1)) <= (*it));
    };
    BOOST_CHECK (A[ 998 ] == 0 and A[ 999 ] == 0 and A[ 1000 + NELEM ] == 0 and
                 A[ 1001 + NELEM ] == 0);


    A.clear ( );
    for (uint32_t i = 0; i < 1000; ++i) A.push_back (999999999);
    for (uint32_t i = 0; i < NELEM; ++i) A.push_back (NELEM - i);
    for (uint32_t i = 0; i < 1000; ++i) A.push_back (999999999);

    flat_stable_sort< iter_t, compare_t, 9 > (A.begin ( ) + 1000,
                                    A.begin ( ) + (1000 + NELEM), comp);

    for (iter_t it = A.begin ( ) + 1001; it != A.begin ( ) + (1000 + NELEM);
         ++it)
    {
        BOOST_CHECK ((*(it - 1)) <= (*it));
    };
    BOOST_CHECK (A[ 998 ] == 999999999 and A[ 999 ] == 999999999 and
                 A[ 1000 + NELEM ] == 999999999 and
                 A[ 1001 + NELEM ] == 999999999);

    std::vector< uint64_t > B (N1 + 2000, 0);

    A.clear ( );
    range< uint64_t * > Rbuf (&B[ 1000 ], (&B[ 1000 ]) + N1);
    for (uint32_t i = 0; i < NELEM; ++i) A.push_back (NELEM - i);
    circular_buffer <uint64_t,10> circ ;

    flat_stable_sort< iter_t, compare_t,9 > (A.begin ( ), A.end ( ), comp, &circ);
    for (iter_t it = A.begin ( ) + 1; it != A.end ( ); ++it) {
        if ((*(it - 1)) > (*it)) std::cout << "error 1\n";
    };
    BOOST_CHECK (B[ 998 ] == 0 and B[ 999 ] == 0 and B[ 1000 + N1 ] == 0 and
                 B[ 1001 + N1 ] == 0);

    for (uint32_t i = 0; i < B.size ( ); ++i) B[ i ] = 999999999;
    A.clear ( );
    for (uint32_t i = 0; i < NELEM; ++i) A.push_back (NELEM - i);
    flat_stable_sort< iter_t, compare_t ,9> (A.begin ( ), A.end ( ), comp, &circ);

    for (iter_t it = A.begin ( ) + 1; it != A.end ( ); ++it) {
        BOOST_CHECK ((*(it - 1)) <= (*it));
    };
    BOOST_CHECK (B[ 998 ] == 999999999 and B[ 999 ] == 999999999 and
                 B[ 1000 + N1 ] == 999999999 and B[ 1001 + N1 ] == 999999999);
};
void test8 ( void)
{
	typedef typename std::vector<uint32_t>::iterator 	iter_t;
	typedef std::less<uint32_t>       					compare_t;
	std::mt19937 my_rand (0);
	std::vector<uint32_t> V ;
	const uint32_t NELEM = 1000000;
	V.reserve(NELEM);
	for (uint32_t i =0 ; i < NELEM ; ++i) V.push_back(i);


	// few unsorted elements at end
	uint32_t NUMBER1 = 100;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1);
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 1000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1);
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 10000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1);
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 100000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1);
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 500000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1);
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 900000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1);
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 950000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1);
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );
}
void test9 ( void)
{
	typedef typename std::vector<uint32_t>::iterator 	iter_t;
	typedef std::less<uint32_t>       					compare_t;
	std::mt19937 my_rand (0);
	std::vector<uint32_t> V ;
	const uint32_t NELEM = 1000000;
	V.reserve(NELEM);
	for (uint32_t i =0 ; i < NELEM ; ++i) V.push_back(i);


	// few unsorted elements at end
	uint32_t NUMBER1 = 100;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 1000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 10000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 100000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 500000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 900000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 950000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );
}
void test10 ( void)
{
	typedef typename std::vector<uint32_t>::iterator 	iter_t;
	typedef std::less<uint32_t>       					compare_t;
	typedef std::greater<uint32_t>       				inv_compare_t;
	std::mt19937 my_rand (0);
	std::vector<uint32_t> V ;
	const uint32_t NELEM = 1000000;
	V.reserve(NELEM);
	for (uint32_t i =0 ; i < NELEM ; ++i) V.push_back(i);


	// few unsorted elements at end
	uint32_t NUMBER1 = 100;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1,inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 1000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1,inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 10000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1,inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 100000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1,inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 500000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1,inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 900000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1,inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 950000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin(), V.end() - NUMBER1,inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );
}
void test11 ( void)
{
	typedef typename std::vector<uint32_t>::iterator 	iter_t;
	typedef std::less<uint32_t>       					compare_t;
	typedef std::greater<uint32_t>       				inv_compare_t;
	std::mt19937 my_rand (0);
	std::vector<uint32_t> V ;
	const uint32_t NELEM = 1000000;
	V.reserve(NELEM);
	for (uint32_t i =0 ; i < NELEM ; ++i) V.push_back(i);


	// few unsorted elements at end
	uint32_t NUMBER1 = 100;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end(),inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 1000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end(),inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 10000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end(),inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 100000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end(),inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 500000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end(),inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 900000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end(),inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );

	// few unsorted elements at end
	NUMBER1 = 950000;
	std::shuffle( V.begin() , V.end(), my_rand);
	std::sort (V.begin()+ NUMBER1, V.end(),inv_compare_t());
	flat_stable_sort<iter_t, compare_t, 9> ( V.begin() , V.end(), compare_t());
	for (uint32_t i =0 ; i < NELEM ; ++i)
		BOOST_CHECK ( V[i] == i );
}
int test_main (int, char *[])
{
    test1 ( );
    test2 ( );
    test3 ( );
    test4 ( );
    test5 ( );
    test6 ( );
    test7 ( );
    test8 ( );
    test9 ( );
    test10 ( );
    test11 ( );
    return 0;
};
