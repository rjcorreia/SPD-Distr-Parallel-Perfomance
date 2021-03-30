//
// Created by Ricardo Correia on 17/03/2021.
//

#ifndef MAGICSQUARE_MPI_H
#define MAGICSQUARE_MPI_H


#include "magicSquare.h"
#include <mpi.h>

void print_ms_result(const int *wrongColumnsCount, const int *wrongRowsCount, const int *wrongDiagonalsCount) {
    if (!*wrongColumnsCount && !*wrongRowsCount) {
        if (!*wrongDiagonalsCount) {
            printf("Quadrado mágico.\n");
        } else {
            printf("Quadrado mágico imperfeito.\n");
        }
    } else {
        printf("Não é quadrado mágico.\n");
    }
}



#endif //MAGICSQUARE_MPI_H
