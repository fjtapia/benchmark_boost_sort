//----------------------------------------------------------------------------
/// @file test_separate_compilation2.cpp
/// @brief Test program of the separate compilation
///
/// @author Copyright (c) 2010 2017 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <algorithm>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <ciso646>
//#include <boost/test/included/test_exec_monitor.hpp>
//#include <boost/test/test_tools.hpp>
#include <boost/sort/parallel/sort.hpp>

namespace bsp = boost::sort::parallel;
void function1A(std::vector<uint32_t> & V1);
void function1B(std::vector<uint32_t> & V1);
void function1C(std::vector<uint32_t> & V1);

void function2A(std::vector<uint32_t> & V1)
{

    std::vector<uint32_t> V2;
    V2 = V1;
    std::sort(V2.begin(), V2.end());

    bsp::block_indirect_sort(V1.begin(), V1.end());
    for (unsigned i = 0; i < V1.size(); i++)
    {
        assert(V1[i] == V2[i]);
    };
}

void function2B(std::vector<uint32_t> & V1)
{

    std::vector<uint32_t> V2;
    V2 = V1;
    std::sort(V2.begin(), V2.end());

    bsp::sample_sort(V1.begin(), V1.end());
    for (unsigned i = 0; i < V1.size(); i++)
    {
        assert(V1[i] == V2[i]);
    };
}

void function2C(std::vector<uint32_t> & V1)
{

    std::vector<uint32_t> V2;
    V2 = V1;
    std::sort(V2.begin(), V2.end());

    bsp::parallel_stable_sort(V1.begin(), V1.end());
    for (unsigned i = 0; i < V1.size(); i++)
    {
        assert(V1[i] == V2[i]);
    };
}


int main(int argc, char *argv[])
{
    typedef typename std::vector<uint32_t>::iterator iter_t;
    typedef std::less<uint32_t> compare;

    const uint32_t NElem = 1000000;
    std::vector<uint32_t> V1, V2, V3;
    V1.reserve(NElem);
    V2.reserve(NElem);
    V3.reserve(NElem);
    std::mt19937 my_rand(0);
    for (uint32_t i = 0; i < NElem; ++i)
        V3.push_back(my_rand());
    V2 = V1 = V3;

    function1A(V1);
    function2A(V2);

    for (uint32_t i = 0; i < NElem; ++i)
        assert(V1[i] == V2[i]);

    V2 = V1 = V3;

    function1B(V1);
    function2B(V2);

    for (uint32_t i = 0; i < NElem; ++i)
        assert(V1[i] == V2[i]);

    V2 = V1 = V3;

    function1C(V1);
    function2C(V2);

    for (uint32_t i = 0; i < NElem; ++i)
        assert(V1[i] == V2[i]);
    return 0;
}

