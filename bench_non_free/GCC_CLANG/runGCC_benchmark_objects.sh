clear
echo "=================================================================="
echo "==              B E N C H M A R K   O B J E C T S               =="
echo "==                                                              =="
echo "==                 G C C      C O M P I L E R                   =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
echo "."
g++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../include  -I../include  -s  -o file_generator
g++ ./benchmark_objects.cpp -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../include -I../include  -pthread  -s  -lpthread -ltbb  -o benchmark_objects
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 20 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "The results will be stored in the file GCC_objects.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "==================================================================" > GCC_objects.txt 2>&1
echo "                B E N C H M A R K   N U M B E R S                 " >> GCC_objects.txt 2>&1
echo "." >> GCC_objects.txt 2>&1
lscpu >> GCC_objects.txt 2>&1
echo "==================================================================" >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 1 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 2 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 3 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 4 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 5 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 6 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 7 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 8 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 9 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 10 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 11 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 12 >> GCC_objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./benchmark_objects 13 >> GCC_objects.txt 2>&1

rm input.bin
rm file_generator
rm benchmark_objects
echo "."
date
echo "."
echo "E N D"
echo "."
