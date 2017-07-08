//----------------------------------------------------------------------------
/// @file benchmark_numbers.cpp
/// @brief Benchmark of several sort methods with uint64_t numbers
///
/// @author Copyright (c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
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
#include <stdlib.h>
#include <vector>
#include <ppl.h>

#include <boost/sort/common/file_vector.hpp>
#include <boost/sort/common/time_measure.hpp>
#include <boost/sort/sort.hpp>

#define NELEM 100000000

using namespace std;
namespace bsc = boost::sort::common;
namespace bsort = boost::sort;
namespace bsp = boost::sort::parallel;

using bsc::time_point;
using bsc::now;
using bsc::subtract_time;
using bsc::fill_vector_uint64;
using bsc::write_file_uint64;

int Test(vector<uint64_t> &A, int option);


int main(int argc, char *argv[])
{
	vector<uint64_t> A;
    int option = 0;
    if (argc > 1) option = atoi(argv[1]);
    if (option == 0)
    {
        std::cout << std::endl << std::endl;
        std::cout << std::endl << std::endl;
        std::cout << "\t      M E N U \n";
        std::cout << "\t    =============\n\n\n";
        std::cout << "\t1 .- std::sort  \n";
        std::cout << "\t2 .- Boost pdqsort  \n";
        std::cout << "\t3 .- std::stable_sort  \n";
        std::cout << "\t4 .- Boost spinsort \n";
        std::cout << "\t5 .- Boost flat_stable_sort \n";
        std::cout << "\t6 .- Boost spreadsort \n";
        std::cout << "\t7 .- PPL   parallel sort \n";
        std::cout << "\t8 .- PPL   parallel buffered sort \n";
        std::cout << "\t9 .- Boost block_indirect_sort  \n";
        std::cout << "\t10.- Boost sample sort \n";
        std::cout << "\t11.- Boost parallel stable sort \n";

        std::cout << std::endl << std::endl;
        std::cout << "\t Select option -> ";
        std::cin >> option;
        cout << "\n";
    };
    if (option < 1 or option > 11) return 0;
    //------------------------------------------------------------------------
    //        LOAD THE DATA FROM THE FILE
    //------------------------------------------------------------------------
    A.reserve(NELEM);
    cout << "\n";
    //------------------------ begin -----------------------------
    cout << "Sorting of " << NELEM << " uint64_t elements : ";

    A.clear();
    if (bsc::fill_vector_uint64("input.bin", A, NELEM) != 0) {
        std::cout << "Error in the input file\n";
        return 1;
    };

    if ( option < 17) Test(A,option);

    return 0;
};

int Test(vector<uint64_t> &A, int option)
{
    double duration;
    time_point start, finish;
    std::less<uint64_t> comp;

    switch (option)
    {
        case 1 :
            cout << "std::sort                            : ";
            start = now();
            std::sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 2:
            cout << "Boost pdqsort                        : ";
            start = now();
            bsort::pdqsort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 3:
            cout << "std::stable_sort                     : ";
            start = now();
            std::stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 4:
            cout << "Boost spinsort                        : ";
            start = now();
            bsort::spinsort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 5:
            cout << "Boost flat_stable_sort               : ";
            start = now();
            bsort::flat_stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 6:
            cout << "Boost spreadsort                     : ";
            start = now();
            bsort::spreadsort::spreadsort(A.begin(), A.end());
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 7:
            cout << "PPL   parallel sort                  : ";
            start = now();
            concurrency::parallel_sort(A.begin(), A.end());
            finish = now();
            duration = subtract_time(finish, start);
            std::cout << duration << " secs\n";
            break;

        case 8:
            cout << "PPL Parallel Buffered Sort           : ";
            start = now();
            concurrency::parallel_buffered_sort(A.begin(), A.end());
            finish = now();
            duration = subtract_time(finish, start);
            std::cout << duration << " secs\n";
            break;

        case 9:
            cout << "Boost block_indirect_sort            : ";
            start = now();
            bsp::block_indirect_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 10:
            cout << "Boost sample sort                    : ";
            start = now();
            bsp::sample_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 11:
            cout << "Boost parallel stable sort           : ";
            start = now();
            bsp::parallel_stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;
    };
    return 0;
};
