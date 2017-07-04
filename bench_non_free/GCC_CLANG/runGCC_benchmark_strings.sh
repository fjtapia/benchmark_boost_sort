clear
echo "=================================================================="
echo "==             B E N C H M A R K   S T R I N G S                =="
echo "==                                                              =="
echo "==                 G C C      C O M P I L E R                   =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
echo "."
g++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../include  -I../include  -s  -o file_generator
g++ ./benchmark_strings.cpp      -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../include -I../include  -pthread  -s  -lpthread -ltbb  -o benchmark_strings
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 5 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "."
echo "The results will be stored in the file GCC_strings.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "=================================================================="> GCC_strings.txt 2>&1
echo "                B E N C H M A R K    S T R I N G S                  ">> GCC_strings.txt 2>&1
echo ".">> GCC_strings.txt 2>&1
lscpu >> GCC_strings.txt 2>&1
echo "==================================================================">> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 1 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 2 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 3 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 4 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 5 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 6 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 7 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 8 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 9 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 10 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 11 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 12 >> GCC_strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_strings 13 >> GCC_strings.txt 2>&1


rm input.bin
rm file_generator
rm benchmark_strings
echo "."
date
echo "."
echo "E N D"
echo "."
