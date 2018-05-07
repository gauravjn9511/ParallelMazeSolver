#!/bin/bash

compile=0

if [[ $compile -eq 1 ]]; then
	echo "Compiling..."

	nvcc -c dijkstra_parallel.cu prim_mst_parallel.cu

	g++ -o grid_parallel -std=c++11 dijkstra_parallel.o prim_mst_parallel.o main.cpp pgm.cpp grid.cpp  -L/usr/include/ -lcudart

	g++ -o grid_serial -std=c++11  main.cpp grid.cpp pgm.cpp prim_mst.cpp dijkstra.cpp
fi


# Parameters
num_rows=10
num_cols=10
pixels=5 				# Zero for no rendering 

echo "Serial execution"
./grid_serial $num_rows $num_cols $pixels

echo "Parallel execution"
./grid_parallel $num_rows $num_cols $pixels