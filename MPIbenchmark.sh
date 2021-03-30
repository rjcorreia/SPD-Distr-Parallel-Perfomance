#!/bin/bash
mpirun -np 4 ./mpi extra.nosync/$1
for ((c=0; c<31; c++))
do
    time mpirun -np 4 ./mpi extra.nosync/$1
done