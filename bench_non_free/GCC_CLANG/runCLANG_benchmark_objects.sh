clear
echo "=================================================================="
echo "==              B E N C H M A R K   O B J E C T S               =="
echo "==                                                              =="
echo "==               C L A N G     C O M P I L E R                  =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
echo "."
clang++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../include  -I../include  -s  -o file_generator
clang++ ./benchmark_objects.cpp -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../include -I../include  -pthread  -s  -lpthread -ltbb  -o benchmark_objects
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 20 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "The results will be stored in the file CLANG_objects.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "==================================================================" > CLANG_objects.txt 2>&1
echo "                B E N C H M A R K   N U M B E R S                 " >> CLANG_objects.txt 2>&1
echo "." >> CLANG_objects.txt 2>&1
lscpu >> CLANG_objects.txt 2>&1
echo "==================================================================" >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 1 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 2 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 3 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 4 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 5 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 6 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 7 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 8 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 9 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 10 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 11 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 12 >> CLANG_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 13 >> CLANG_objects.txt 2>&1

rm input.bin
rm file_generator
rm benchmark_objects
echo "."
date
echo "."
echo "E N D"
echo "."
