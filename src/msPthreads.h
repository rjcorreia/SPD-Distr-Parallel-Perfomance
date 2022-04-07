//
// Created by Ricardo Correia on 05/03/2021.
//

#ifndef MAGICSQUARE_PTHREADS_H
#define MAGICSQUARE_PTHREADS_H


#include "magicSquare.h"
#include <pthread.h>


/*
 * Global constants to symbolize the different jobs of the threads, to avoid using magic numbers.
 */
const int columnThreads = 2;
const int rowThreads = 2;
int side_size = 0;
long sum;
const int COLUMNS_DUTY = 0;
const int ROWS_DUTY = 1;
const int DIAGONALS_DUTY = 2;


/*
 * Struct that holds all the required information to be passed to a pthread.
 *  square is a bi-dimensional array that represents the square
 *  job is the assigned job of the pthread(rows, columns, diagonals)
 *  start is the starting index
 *  end is the ending index
 */
typedef struct {
    int **square;
    int job;
    int start;
    int end;
} Vector;


/*
 * Constructor for the Vector struct
 */
Vector vector(int **square, int job, int start, int end) {
    Vector result;
    result.square = square;
    result.job = job;
    result.start = start;
    result.end = end;
    return result;
}

/*
 * Checks if the sums of the numbers in each column are the same and equals to sum.
 */
void check_columns_sum(int **square, int start, int rows, int columns) {
    for (int j = start; j < columns; ++j) {
        if (COLUMN_CHECKER) {
            if (get_sum_column(square, j, rows) != sum) {
                COLUMN_CHECKER = 0;
            }
        }
    }
}


/*
 * Checks if the sums of the numbers in each row are the same and equal to the sum.
 */
void check_rows_sum(int **square, int start, int rows, int columns) {
    for (int i = start; i < rows; ++i) {
        if (ROWS_CHECKER) {
            if (get_sum_row(square, i, columns) != sum) {
                ROWS_CHECKER = 0;
            }
        }
    }
}

/*
 * Checks if the sums of the numbers in both main diagonals are the same and equal to the sum
 */
void check_diagonals_sum(int **square, int rows, int columns) {
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


void print_time_results() {
    elapsedTotal = timedifference_msec(startTotal, totalTime);
    elapsedReading = timedifference_msec(readingStart, readingTime);
    elapsedColumns = timedifference_msec(columnsStart, columnsTime);
    elapsedRows = timedifference_msec(rowsStart, rowsTime);
    elapsedDiagonals = timedifference_msec(diagonalsStart, diagonalsTime);
    elapsedTotal = timedifference_msec(startTotal, totalTime);
    elapsedThreads = timedifference_msec(threadsStart, threadsTime);
    printf("R %f ms.\n", elapsedRows);
    printf("C %f ms.\n", elapsedColumns);
    printf("D %f ms.\n", elapsedDiagonals);
    printf("T %f ms.\n", elapsedThreads);
    printf("E %f ms.\n", elapsedTotal);
    printf("e %f ms.\n", elapsedTotal - elapsedReading);
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

#endif //MAGICSQUARE_PTHREADS_H
