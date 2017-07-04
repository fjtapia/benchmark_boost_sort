clear
echo "=================================================================="
echo "==              B E N C H M A R K   N U M B E R S               =="
echo "==                                                              =="
echo "==                C L A N G     C O M P I L E R                 =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
echo "."
clang++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../include  -I../include  -s  -o file_generator
clang++ ./benchmark_numbers.cpp -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../include -I../include  -pthread  -s  -lpthread -ltbb  -o benchmark_numbers
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 5 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "."
echo "The results will be stored in the file CLANG_numbers.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "=================================================================="> CLANG_numbers.txt 2>&1
echo "                B E N C H M A R K   N U M B E R S                 ">> CLANG_numbers.txt 2>&1
echo ".">> CLANG_numbers.txt 2>&1
lscpu >> CLANG_numbers.txt 2>&1
echo "==================================================================">> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 1 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 2 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 3 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 4 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 5 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 6 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 7 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 8 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 9 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 10 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 11 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 12 >> CLANG_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 13 >> CLANG_numbers.txt 2>&1

rm input.bin
rm file_generator
rm benchmark_numbers
echo "."
date
echo "."
echo "E N D"
echo "."
