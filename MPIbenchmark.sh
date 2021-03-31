#!/bin/bash
for ((c=0; c<31; c++))
do
    mpirun -np 4 ./mpi extra.nosync/$1
done