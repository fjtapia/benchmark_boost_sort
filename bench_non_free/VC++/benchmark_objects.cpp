//----------------------------------------------------------------------------
/// @file  benchmark_objects.cpp
/// @brief Benchmark of several sort methods with different object formats
///        and sizes
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
#include <boost/sort/common/int_array.hpp>
#include <boost/sort/sort.hpp>

#define NELEM 100000000
using namespace std;
namespace bsort = boost::sort;
namespace bsc = bsort::common;

using bsc::time_point;
using bsc::now;
using bsc::subtract_time;
using bsc::fill_vector_uint64;
using bsc::write_file_uint64;
using bsc::int_array;
using bsc::H_comp;
using bsc::L_comp;

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

template<class IA, class rightshift, class compare>
int Test (std::vector<IA> &A, rightshift shift, compare comp,
          std::vector<double> &V, int option);



template <class IA>
void Generator(uint64_t N, int option);

int main(int argc, char *argv[])
{ //------------------------------ Inicio ----------------------------------
    int option = 0;
    if (argc > 1) option = atoi(argv[1]);
    if (option == 0)
    { //----------------------------- menu ---------------------------------
        cout << "=========================================================\n";
        cout << "=            OBJECT COMPARISON                          =\n";
        cout << "=          ---------------------                        =\n";
        cout << "=                                                       =\n";
        cout << "= The objects are arrays of 64 bits numbers             =\n";
        cout << "= They are compared in two ways :                       =\n";
        cout << "= (H) Heavy : The comparison is the sum of all the      =\n";
        cout << "=             numbers of the array                      =\n";
        cout << "= (L) Light : The comparison is with the first          =\n";
        cout << "=             element of the array, as a key            =\n";
        cout << "=                                                       =\n";
        cout << "========================================================\n";
        cout << "\n\n";
        cout << std::endl << std::endl;
        cout << std::endl << std::endl;
        cout << "\t      M E N U \n";
        cout << "\t    =============\n\n\n";
        cout << "\t1 .- std::sort  \n";
        cout << "\t2 .- Boost pdqsort  \n";
        cout << "\t3 .- std::stable_sort  \n";
        cout << "\t4 .- Boost spinsort \n";
        cout << "\t5 .- Boost flat_stable_sort \n";
        cout << "\t6 .- Boost spreadsort \n";
        cout << "\t7 .- PPL   parallel sort \n";
        cout << "\t8 .- PPL   parallel buffered sort \n";
        cout << "\t9 .- Boost block_indirect_sort  \n";
        cout << "\t10.- Boost sample sort \n";
        cout << "\t11.- Boost parallel stable sort \n";

        std::cout << std::endl << std::endl;
        std::cout << "\t Select option -> ";
        std::cin >> option;
        cout << "\n";
    };
    if (option < 1 or option > 11) return 0;
    //------------------------------------------------------------------------
    //        LOAD THE DATA FROM THE FILE
    //------------------------------------------------------------------------
    cout << endl;
    //------------------------ Inicio -----------------------------
    switch (option)
    {
        case 1 : cout << "\t1 .- std::sort  \n"; break;
        case 2 : cout << "\t2 .- Boost pdqsort  \n"; break;
        case 3 : cout << "\t3 .- std::stable_sort  \n"; break;
        case 4 : cout << "\t4 .- Boost spinsort \n"; break;
        case 5 : cout << "\t5 .- Boost flat_stable_sort \n"; break;
        case 6 : cout << "\t6 .- Boost spreadsort \n"; break;
        case 7 : cout << "\t7 .- PPL   parallel sort \n"; break;
        case 8 : cout << "\t8 .- PPL   parallel buffered sort \n"; break;
        case 9 : cout << "\t9 .- Boost block_indirect_sort  \n"; break;
        case 10 : cout << "\t10.- Boost sample sort \n"; break;
        case 11 : cout << "\t11.- Boost parallel stable sort \n"; break;
    };
    cout << endl;



    //------------------------------------------------------------------------
    // Execution with different object format
    //------------------------------------------------------------------------
    Generator<int_array<1> >(NELEM, option);
    Generator<int_array<2> >(NELEM >> 1, option);
    Generator<int_array<4> >(NELEM >> 2, option);
    Generator<int_array<8> >(NELEM >> 3, option);
    Generator<int_array<16> >(NELEM >> 4, option);
    Generator<int_array<32> >(NELEM >> 5, option);
    Generator<int_array<64> >(NELEM >> 6, option);

    return 0;
}

template <class IA>
void Generator(uint64_t N, int option)
{ //------------------------------- begin ----------------------------------
    bsc::uint64_file_generator gen("input.bin");
    vector<IA> A;
    A.reserve(N);
    //IA Aux;

    cout << "\tSort of N = " << N << " elements of size " << sizeof(IA) << "\n";

    cout << "Heavy Comparison   : ";
    gen.reset();
    A.clear();
    for (uint32_t i = 0; i < N; i++) A.emplace_back(IA::generate(gen));

    Test(A, H_rightshift<IA>(), H_comp<IA>(), option);

    cout << "Light Comparison   : ";
    gen.reset();
    A.clear();
    for (uint32_t i = 0; i < N; i++) A.emplace_back(IA::generate(gen));
    Test(A, L_rightshift<IA>(), L_comp<IA>(), option);

    cout << endl;
};

template<class IA, class rightshift, class compare>
int Test(std::vector<IA> &A, rightshift shift, compare comp, int option)
{
    double duration;
    time_point start, finish;

    switch (option)
    {
        case 1 :
            start = now();
            std::sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;


        case 2:
            start = now();
            bsort::pdqsort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;


        case 3:
            start = now();
            std::stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 4:
            start = now();
            bsort::spinsort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 5:
            start = now();
            bsort::flat_stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 6 :
            start = now ();
            bsort::spreadsort::integer_sort (A.begin (), A.end (), shift, comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;


        case 7:
            start = now();
            concurrency::parallel_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 8:
            start = now();
            concurrency::parallel_buffered_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 9:
            start = now();
            bsort::block_indirect_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 10:
            start = now();
            bsort::sample_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;

        case 11:
            start = now();
            bsort::parallel_stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duration = subtract_time(finish, start);
            cout << duration << " secs\n";
            break;
    };
    return 0;
};
