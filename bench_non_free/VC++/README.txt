
README.TXT
==============
If you want to do manually or with different compiler.

file_generator is a program which generte a file with random information
               for to be used in the benchmark.
               After compiled the invocation is
               file_generator input.bin 1000000000

This generate a 800 MB file input.bin with random information for the benchmark programs.
When finish, this file can be deleted.

Now we have the data file and only need to compile and run the programs.
                short_benchmark.cpp
                benchmark_objects.cpp
                benchmark_strings.cpp
                benchmark_numbers.cpp

The four programs use the file input.bin, created with file_generator

short_benchmark.cpp This program is a time benchmark of the Boost Sort Library
                    compared with the algorithms of the Microsoft PPL library

In the programs benchmark_objects.cpp, benchmark_strings.cpp, benchmark_numbers.cpp appear a
menu where you select the algorithm to use for sort the random numbers obtained from the file input.bin.
The program shows the time spent in the sorting.

This can be useful for to see the memory used. In Windows I don't know any command which permit me to know the
maximun memory used by a program. You can see with iterative programs, being the most simple the program manager.
Watching it you can see the memory used by each algorithm


benchmark_numbers.cpp This program sort 100000000 numbers of 64 bits, by different algorithms
benchmark_strings.cpp This program sort 10000000 strings filled with random information
benchmark_objects.cpp This program sort  objects of size 8, 16, 32, 64, 128, 256 and 512 bytes
