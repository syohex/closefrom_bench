all: closefrom_bench close_bench

closefrom_bench: bench.cpp
	clang++ -O3 -DUSE_CLOSEFROM -o closefrom_bench bench.cpp

close_bench: bench.cpp
	clang++ -O3  -o close_bench bench.cpp

.PHONY: bench

bench: closefrom_bench close_bench
	./bench.sh
