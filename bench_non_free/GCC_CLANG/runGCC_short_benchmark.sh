clear
echo "=================================================================="
echo "==               S H O R T _ B E N C H M A R K                  =="
echo "==                                                              =="
echo "==                G C C      C O M P I L E R                    =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
echo "."
g++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../include  -I../include  -s  -o file_generator
g++ ./short_benchmark.cpp      -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../include -I../include  -pthread  -s  -lpthread -ltbb  -o short_benchmark
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 5 to 20 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "The results will be stored in the file GCC_short_benchmark.txt"
echo "."
echo " please, be patient .........."
echo "."
./short_benchmark >GCC_short_benchmark.txt
rm input.bin
rm file_generator
rm short_benchmark
date
echo "."
echo "E N D"
echo "."
