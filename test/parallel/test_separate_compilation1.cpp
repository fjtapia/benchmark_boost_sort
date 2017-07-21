//----------------------------------------------------------------------------
/// @file test_separate_compilation1.cpp
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
#include <boost/sort/sort.hpp>

namespace bsp = boost::sort;
void function1A(std::vector<uint32_t> & V1)
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

void function1B(std::vector<uint32_t> & V1)
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

void function1C(std::vector<uint32_t> & V1)
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

