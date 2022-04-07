//
// Created by Ricardo Correia on 09/03/2021.
//

#ifndef MAGICSQUARE_OMP_H
#define MAGICSQUARE_OMP_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "magicSquare.h"
#include <omp.h>

/*
 * Checks if the sums of the numbers in each column are the same.
 * Returns 1 if TRUE and 0 if FALSE
 */
void check_columns_sum(int **square, int start, int rows, int columns, long sum) {
    int i, j;
    long counter;
#pragma omp parallel for num_threads(6) private(i, j, counter) shared(square, start, rows, columns, sum)
    for (j = start; j < columns; ++j) {
        if (COLUMN_CHECKER) {
            counter = 0;
            i = 0;
            while (i < rows) {
                counter += square[i++][j];
            }
            if (counter != sum) {
#pragma omp critical
                {
                    COLUMN_CHECKER = 0;
                };
            }
        }
    }
}

/*
 * Checks if the sums of the numbers in each row are the same.
 * Returns 1 if TRUE and 0 if FALSE
 */
void check_rows_sum(int **square, int start, int rows, int columns, long sum) {

    int i, j;
    long counter;
//#pragma omp parallel for private num_threads (i, j, counter) shared(square, start, rows, columns, sum)
    for (i = start; i < rows; ++i) {
        if (ROWS_CHECKER) {
            j = 0;
            counter = 0;
            while (j < columns) {
                counter += square[i][j++];
            }
            if (counter != sum) {
//#pragma omp critical
//                {
                    ROWS_CHECKER = 0;
//                };
            }
        }
    }
}

/*
 * Checks if the sums of the numbers in both main diagonals are the same.
 * Returns 1 if true and 0 if false.
 */
void check_diagonals_sum(int **square, int rows, int columns, long sum) {
    gettimeofday(&diagonalsStart, 0);
    long resultLeftDiag = 0;
    long resultRightDiag = 0;
    int j = rows - 1;
    for (int i = 0; i < columns; i++) {
        resultLeftDiag += square[i][i];
        resultRightDiag += square[j][i];
        j--;
    }
    if (resultRightDiag != sum || resultLeftDiag != sum) {
        DIAGONAL_CHECKER = 0;
    }
    gettimeofday(&diagonalsTime, 0);
}


void print_ms_result() {

    if (ROWS_CHECKER && COLUMN_CHECKER) {
        if (DIAGONAL_CHECKER) {
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
    elapsedThreads = timedifference_msec(threadsStart, threadsTime);
    printf("R %f ms.\n", elapsedRows);
    printf("C %f ms.\n", elapsedColumns);
    printf("D %f ms.\n", elapsedDiagonals);
    printf("T %f ms.\n", elapsedThreads);
    printf("E %f ms.\n", elapsedTotal);
    printf("e %f ms.\n", elapsedTotal - elapsedReading);
}

#endif //MAGICSQUARE_OMP_H
