<H1>Benchmark Boost Sort Parallel</H1>
<H2> <a href="https://github.com/fjtapia/benchmark_boost_sort">https://github.com/fjtapia/benchmark_boost_sort</a> </H2>

<H2>PRELIMINARY</H2>

This repository provide :

* The code of the Boost Sort Library until appear in the official release. (We hope  appear in the next version).
The code included in this repository is the proposed for the offcial version, don't expect changes in names and namespaces.
* Benchmarks for to check the speed of the sort algorithms included in the library.
* Brief documentation. (This documentaion is not the official. It is under construction).

<H2>CODE</H2>

In this repository is **included ALL the code needed to compile and run the benchmark** ( Boost Sort Library, benchmarks and scripts to execute). Don't need load any other code.

The code included in this repository is the code proposed for the offcial version. The names and namespacesare the proposed for the final version.

<H2>BENCHMARKS</H2>

There are two kinds of benchmarks:
* Use only the Boost Sort Library. These will be included in the library
* Use external and not free code. These can't be included in the library and are only in this repository.

For the compilers GCC and CLANG in Linux have shell scripts for to compile and run the benchmarks. For others compilers you have detailed instructions for run the benchmarks.

<H4>ONLY BOOST SORT</H4>

These benchmark measure the speed with random data, and with near random data.

You can find benchmark for numbers, strings and objects of different sizes, and with different comparison operators.

There are benchmarks for single thread algorithms and parallel algorithms.

These benchmarks can be compiled by any compiler C++11 compliant, and the results provided have a look similar to this

The program generate a file of 1000 M (input.bin) with the random information used in the benchmark. When finish, this file is deleted


                 B O O S T      S O R T
                S I N G L E    T H R E A D
            I N T E G E R    B E N C H M A R K

          SORT OF 100 000 000 NUMBERS OF 64 BITS

        [ 1 ] std::sort   [ 2 ] pdqsort          [ 3 ] std::stable_sort
        [ 4 ] spin_sort   [ 5 ] flat_stable_sort [ 6 ] spreadsort

                            |      |      |      |      |      |      |
                            | [ 1 ]| [ 2 ]| [ 3 ]| [ 4 ]| [ 5 ]| [ 6 ]|
        --------------------+------+------+------+------+------+------+
        random              | 8.21 | 3.99 | 8.62 | 9.73 |10.80 | 4.26 |
                            |      |      |      |      |      |      |
        sorted              | 1.84 | 0.13 | 4.88 | 0.06 | 0.07 | 0.06 |
        sorted + 0.1% end   | 6.41 | 2.91 | 4.92 | 0.41 | 0.36 | 3.16 |
        sorted +   1% end   |14.15 | 3.39 | 4.97 | 0.55 | 0.49 | 3.65 |
        sorted +  10% end   | 6.72 | 4.15 | 5.73 | 1.32 | 1.40 | 4.39 |
                            |      |      |      |      |      |      |
        sorted + 0.1% mid   | 4.41 | 3.31 | 6.58 | 1.89 | 2.61 | 3.29 |
        sorted +   1% mid   | 4.39 | 3.62 | 7.06 | 2.12 | 3.07 | 3.80 |
        sorted +  10% mid   | 6.35 | 4.71 | 9.56 | 4.02 | 5.49 | 4.99 |
                            |      |      |      |      |      |      |
        reverse sorted      | 1.36 | 0.26 | 5.12 | 0.13 | 0.14 | 1.87 |
        rv sorted + 0.1% end| 7.57 | 2.92 | 5.22 | 0.52 | 0.42 | 2.83 |
        rv sorted +   1% end| 4.99 | 3.33 | 5.29 | 0.66 | 0.55 | 3.45 |
        rv sorted +  10% end| 4.62 | 4.16 | 6.03 | 1.45 | 1.44 | 4.35 |
                            |      |      |      |      |      |      |
        rv sorted + 0.1% mid| 4.38 | 3.29 | 6.52 | 1.89 | 2.54 | 3.28 |
        rv sorted +   1% mid| 4.43 | 3.65 | 7.09 | 2.12 | 3.09 | 3.81 |
        rv sorted +  10% mid| 6.42 | 4.70 | 9.46 | 4.02 | 5.53 | 5.00 |
        --------------------+------+------+------+------+------+------+


<H4>WITH EXTERNAL NON FREE CODE</H4>

These benchmarks compare the Boost Sort algorithms with others algorithms from compilers and external libraries.

These benchmarks can be included in the Boost Sort Library, because use code of external sources as TBB , GCC and Microsoft PPC.

The external programs used are :

* Threading Building Blocks ( TBB )
* OpenMP of the compiler
* [TBB experimental parallel_stable_sort](https://software.intel.com/sites/default/files/managed/48/9b/parallel_stable_sort.zip)

The program generate a file of 800 M (input.bin) with the random information used in the benchmark. When finish, this file is deleted.

In Linux, probably, the Threading Building Blocks (TBB) are in your package repository.

The code had been tested with GCC 6.3 and with CLANG 4.0. Older versions of CLANG can have problems with the OpenMP libraries, because they are not installed by default with the compiler.

In the VC++ folder, you can find the code to compile, or if you prefer, in the bin folder, you have a compiled and optimized 64 bits version with Visual Studio 2015, and bat files for to run them.
If don't run in your computer, probably, need to install the redistributable 2015 package.

<H2>DOCUMENTATION</H2>

(This documentaion IS NOT THE OFFICIAL. IT IS UNDER CONSTRUCTION. It's only for to orientate to the users about the algorithms of the library.


This table provide you a brief description of the sort algorithms of the library.

**<H4>Single thread algorithms</h4>**

The single thread algorithms of the library are :

* **spreadsort**. Is a hybrid algorithm (don't use comparison operator) very fast. Designed and implemented by Steven Ross
* **pdqsort**. Pattern-defeating quicksort (pdqsort) Novel quicksort algorithm very fast. Designed and implemented by Orson Peters.
* **spinsort**. Stable mergesort, very fast with near sorting data. Designed and implemented by Francisco Tapia
* **flat_stable_sort**. Stable sort with an additional memory of around 1% of the data size, very fast with near sorting data. Designed and implemented by Francisco Tapia

| Algorithm | Stable | Additional memory | Best, average, and worst case |
| --- | --- | --- | --- |
| spreadsort | yes | Log N  | N, NLogN, NLogN |
| pdqsort | no | Log N  | N, NLogN, NLogN |
| spinsort | yes | N / 2  | N, NLogN, NLogN |
| flat_stable_sort | yes| N / 100 | N, NLogN, NLogN   |


**<H4>Parallel algorithms</h4>**
The parallel algorithms of the library are :
All the parallel algorithms don't need any library, only need for to compile and run a C++11 compliant compiler.

* **block_indirect_sort**. Very fast parallel sort, with a very small additional memory. Designed and implemented by Francisco Tapia
* **sample\_sort**. Parallel stable sort with an additional memory equal to the data size. Implemented by Francisco Tapia
* **parallel\_stable\_sort**. Parallel stable sort with an additional memory of a half of the data size. Internally based on sample_sort. Implemented by Francisco Tapia.

| Algorithm | Stable | Additional memory | Best, average, and worst case |
| --- | --- | --- | --- | --- |
| block_indirect_sort | no | block_size \* num_threads | N, NLogN, NLogN  |
| sample_sort | yes | N  | N, NLogN, NLogN  |
| parallel_stable_sort| yes | N / 2 | N, NLogN, NLogN   |



The block_size is an internal parameter of the algorithm, which  in order to achieve the highest speed, change according the size of the objects to sort according the next table. The **strings** use a block_size of 128.

| object size (bytes) |1 - 15| 16 - 31 | 32 - 63 | 64 - 127 | 128 - 255 | 256 - 511 | 512 - |
| --- | --- | --- | --- | --- | --- | --- | --- |
| block_size |4096 |2048 | 1024| 768 | 512 | 256 | 128 |



***
*Copyright 2017  [Francisco Tapia (fjtapia@gmail.com) ] (mail:fjtapia@gmail.com)*
