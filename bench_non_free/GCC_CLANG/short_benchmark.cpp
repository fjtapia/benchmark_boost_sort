//----------------------------------------------------------------------------
/// @file benchmark.cpp
/// @brief Benchmark of several sort methods with different objects
///
/// @author Copyright (c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt )
///
///         This program use for comparison purposes, the Threading Building
///         Blocks which license is the GNU General Public License, version 2
///         as  published  by  the  Free Software Foundation.
///
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector>
#include <boost/sort/common/file_vector.hpp>
#include <boost/sort/common/time_measure.hpp>
#include <boost/sort/common/int_array.hpp>

#include <omp.h>
#include <parallel/algorithm>
#include <parallel/basic_iterator.h>
#include <parallel/features.h>
#include <parallel/parallel.h>

#include "tbb/parallel_sort.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tbb_stddef.h"
#include <parallel_stable_sort/tbb-lowlevel/parallel_stable_sort.h>

#include <boost/sort/sort.hpp>


#define NELEM 100000000
#define NMAXSTRING 10000000

using namespace std;
namespace bsort = boost::sort;
namespace bsc = bsort::common;
namespace bpar = bsort;

using bsc::time_point;
using bsc::now;
using bsc::subtract_time;
using bsc::fill_vector_uint64;
using bsc::write_file_uint64;
using bsc::int_array;
using bsc::H_comp;
using bsc::L_comp;

using bsort::spinsort;
using bsort::spreadsort::spreadsort;
using bsort::pdqsort;

void Generator_sorted(void);
void Generator_reverse_sorted(void);
void Generator_uint64(void);
void Generator_string(void);

template <class IA>
void Generator(uint64_t N);

template <class IA, class compare>
int Test(std::vector<IA> &B, compare comp = compare());

template <class IA>
int Test_spreadsort(std::vector<IA> &B);

template<class IA, class rightshift, class compare>
int Test_spreadsort (std::vector<IA> &A, rightshift shift, compare comp);


template < class IA >
struct H_rightshift {
  inline uint64_t operator()(const IA& A1, unsigned offset) {
    return A1.counter() >> offset;
  }
};

template < class IA >
struct L_rightshift {
  inline uint64_t operator()(const IA& A1, unsigned offset) {
    return A1.M[0] >> offset;
  }
};

int main(int argc, char *argv[])
{
    cout << "\n\n";
    cout << "************************************************************\n";
    cout << "**                                                        **\n";
    cout << "**                 B O O S T    S O R T                   **\n";
    cout << "**             S H O R T _ B E N C H M A R K              **\n";
    cout << "**                                                        **\n";
    cout << "************************************************************\n";
    cout << std::endl;
    std::cout.flush();
    int code = system("lscpu");
    std::cout.flush();
    cout << "\n";

    Generator_sorted();
    Generator_reverse_sorted();
    Generator_uint64();
    Generator_string();

    cout << "=============================================================\n";
    cout << "=            OBJECT COMPARISON                              =\n";
    cout << "=          ---------------------                            =\n";
    cout << "=                                                           =\n";
    cout << "= The objects are arrays of 64 bits numbers                 =\n";
    cout << "= They are compared in two ways :                           =\n";
    cout << "= (H) Heavy : The comparison is the sum of all the numbers  =\n";
    cout << "=             of the array                                  =\n";
    cout << "= (L) Light : The comparison is with the first element of   =\n";
    cout << "=             the array, as a key                           =\n";
    cout << "=                                                           =\n";
    cout << "============================================================\n";
    cout << "\n\n";
    Generator<int_array<1>>(NELEM);
    Generator<int_array<2>>(NELEM >> 1);
    Generator<int_array<4>>(NELEM >> 2);
    Generator<int_array<8>>(NELEM >> 3);
    Generator<int_array<16>>(NELEM >> 4);
    Generator<int_array<32>>(NELEM >> 5);
    Generator<int_array<64>>(NELEM >> 6);

    return code;
}

void Generator_sorted(void)
{
    vector<uint64_t> A;

    A.reserve(NELEM);
    cout << "  " << NELEM << " uint64_t elements already sorted\n";
    cout << "=================================================\n";
    A.clear();
    for (size_t i = 0; i < NELEM; ++i) A.push_back(i);
    Test<uint64_t, std::less<uint64_t>>(A);
    Test_spreadsort(A);
    cout << std::endl;
}
void Generator_reverse_sorted(void)
{
    vector<uint64_t> A;

    A.reserve(NELEM);
    cout << "  " << NELEM << " uint64_t elements reverse sorted\n";
    cout << "=================================================\n";
    A.clear();
    for (size_t i = NELEM; i > 0; --i) A.push_back(i);
    Test<uint64_t, std::less<uint64_t>>(A);
    Test_spreadsort(A);
    cout << std::endl;
}
void Generator_uint64(void)
{
    vector<uint64_t> A;
    A.reserve(NELEM);
    cout << "  " << NELEM << " uint64_t elements randomly filled\n";
    cout << "=================================================\n";
    A.clear();
    if (fill_vector_uint64("input.bin", A, NELEM) != 0) {
        std::cout << "Error in the input file\n";
        return;
    };
    Test<uint64_t, std::less<uint64_t>>(A);
    Test_spreadsort(A);
    cout << std::endl;
}
void Generator_string(void)
{
    cout << "  " << NMAXSTRING << " strings randomly filled\n";
    cout << "===============================================\n";
    std::vector<std::string> A;
    A.reserve(NMAXSTRING);
    A.clear();
    if (bsc::fill_vector_string("input.bin", A, NMAXSTRING) != 0) {
        std::cout << "Error in the input file\n";
        return;
    };
    Test<std::string, std::less<std::string>>(A);
    Test_spreadsort(A);
    cout << std::endl;
};

template <class IA>
void Generator(uint64_t N)
{
    bsc::uint64_file_generator gen("input.bin");
    vector<IA> A;
    A.reserve(N);

    cout << N << " elements of size " << sizeof(IA) << " randomly filled \n";
    cout << "=============================================\n";
    gen.reset();
    A.clear();
    for (uint32_t i = 0; i < N; i++) A.emplace_back(IA::generate(gen));
    cout << "\n  H E A V Y   C O M P A R I S O N\n";
    cout << "====================================\n";
    Test(A, H_comp<IA>());
    Test_spreadsort ( A, H_rightshift<IA>(), H_comp<IA>() );
    cout << "\n  L I G H T   C O M P A R I S O N \n";
    cout << "=======================================\n";
    Test(A, L_comp<IA>());
    Test_spreadsort ( A, L_rightshift<IA>(), L_comp<IA>() );
    cout << std::endl;
};

template <class IA, class compare>
int Test(std::vector<IA> &B, compare comp)
{ //---------------------------- begin --------------------------------
    double duration;
    time_point start, finish;
    std::vector<IA> A(B);

    //--------------------------------------------------------------------
    A = B;
    cout << "std::sort                    : ";
    start = now();
    std::sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "pdqsort                      : ";
    start = now();
    bsort::pdqsort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";


    A = B;
    cout << "std::stable_sort             : ";
    start = now();
    std::stable_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "Boost spinsort               : ";
    start = now();
    bsort::spinsort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "Boost flat_stable_sort       : ";
    start = now();
    bsort::flat_stable_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n\n";

    A = B;
    cout << "OMP parallel sort            : ";
    start = now();
    __gnu_parallel::sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "TBB parallel_sort            : ";
    start = now();
    tbb::parallel_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "Boost block_indirect_sort    : ";
    start = now();
    bpar::block_indirect_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n\n";

    A = B;
    cout << "OMP parallel stable sort     : ";
    start = now();
    __gnu_parallel::stable_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "TBB parallel stable sort     : ";
    start = now();
    pss::parallel_stable_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "Boost sample sort            : ";
    start = now();
    bpar::sample_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    A = B;
    cout << "Boost parallel stable sort   : ";
    start = now();
    bpar::parallel_stable_sort(A.begin(), A.end(), comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n\n";

    return 0;
};

template <class IA>
int Test_spreadsort(std::vector<IA> &B)
{
    double duration;
    time_point start, finish;
    std::vector<IA> A(B);

    //--------------------------------------------------------------------
    A = B;
    cout << "Boost spreadsort             : ";
    start = now();
    boost::sort::spreadsort::spreadsort(A.begin(), A.end());
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    return 0;
};
template<class IA, class rightshift, class compare>
int Test_spreadsort (std::vector<IA> &B, rightshift shift, compare comp)
{
    double duration;
    time_point start, finish;
    std::vector<IA> A(B);
    A = B;
    cout << "Boost spreadsort             : ";
    start = now();
    boost::sort::spreadsort::integer_sort (A.begin (), A.end (), shift, comp);
    finish = now();
    duration = subtract_time(finish, start);
    cout << duration << " secs\n";

    return 0;
};
