clear
echo "=================================================================="
echo "==              B E N C H M A R K   N U M B E R S               =="
echo "==                                                              =="
echo "==                 G C C      C O M P I L E R                   =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
echo "."
g++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../include  -I../include  -s  -o file_generator
g++ ./benchmark_numbers.cpp -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../include -I../include  -pthread  -s  -lpthread -ltbb  -o benchmark_numbers
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 5 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "."
echo "The results will be stored in the file GCC_numbers.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "=================================================================="> GCC_numbers.txt 2>&1
echo "                B E N C H M A R K   N U M B E R S                 ">> GCC_numbers.txt 2>&1
echo ".">> GCC_numbers.txt 2>&1
lscpu >> GCC_numbers.txt 2>&1
echo "==================================================================">> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 1 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 2 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 3 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 4 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 5 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 6 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 7 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 8 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 9 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 10 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 11 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 12 >> GCC_numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_numbers 13 >> GCC_numbers.txt 2>&1


rm input.bin
rm file_generator
rm benchmark_numbers
echo "."
date
echo "."
echo "E N D"
echo "."
