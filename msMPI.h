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


void print_time_results() {
    elapsedTotal = timedifference_msec(startTotal, totalTime);
    elapsedReading = timedifference_msec(readingStart, readingTime);
    elapsedColumns = timedifference_msec(columnsStart, columnsTime);
    elapsedRows = timedifference_msec(rowsStart, rowsTime);
    elapsedDiagonals = timedifference_msec(diagonalsStart, diagonalsTime);
    printf("R %f ms.\n", elapsedRows);
    printf("C %f ms.\n", elapsedColumns);
    printf("D %f ms.\n", elapsedDiagonals);
    printf("T %f ms.\n", 0.0);
    printf("E %f ms.\n", elapsedTotal);
    printf("e %f ms.\n", elapsedTotal - elapsedReading);
}



#endif //MAGICSQUARE_MPI_H
