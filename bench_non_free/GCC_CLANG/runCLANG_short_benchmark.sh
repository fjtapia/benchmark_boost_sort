clear
echo "=================================================================="
echo "==                 S H O R T _ B E N C H M A R K                =="
echo "==                                                              =="
echo "==                C L A N G     C O M P I L E R                 =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
clang++ ./file_generator.cpp -std=c++11   -march=native -O3 -w -fexceptions  -I../../include -o file_generator
echo "."
clang++ ./short_benchmark.cpp -std=c++11 -O3 -fopenmp -march=native -w -fexceptions  -I../../include   -I../include  -pthread -lpthread -ltbb -fopenmp  -o short_benchmark
date
echo "R U N N I N G . . . . . . . . . . ."
echo "The results will be stored in the file CLANG_short_benchmarks.txt"
./file_generator input.bin 100000000
echo "."
echo " ( The time needed is around 5 to 20 minutes depending of your machine ). . . . . . ."
echo " please, be patient .........."
echo "."
./short_benchmark > CLANG_short_benchmarks.txt
rm input.bin
rm file_generator
rm short_benchmark
date
echo "."
echo "E N D"
echo "."
