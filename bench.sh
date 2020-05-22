#!/bin/sh
set -e

for i in 100 1000 10000 100000
do
	echo "Close $i file descriptors"
	./closefrom_bench $i
	./close_bench $i

	echo ""
done
