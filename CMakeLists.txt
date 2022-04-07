cmake_minimum_required(VERSION 3.17)
project(MagicSquare_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(MagicSquarePthreads src/msPthreads.c)
add_executable(MagicSquareSeq src/msSeq.c)
add_executable(MagicSquareOMP src/msOMP.c)
add_executable(MagicSquareMPI src/msMPI.c)
add_executable(MagicSquareHybrid src/msHybrid.c)