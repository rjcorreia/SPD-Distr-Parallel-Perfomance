//
// Created by Ricardo Correia on 05/03/2021.
//

#ifndef MAGICSQUARE_MAGIC_SQUARE_H
#define MAGICSQUARE_MAGIC_SQUARE_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "time_test.h"

struct timeval startTotal;
struct timeval readingTime;
struct timeval readingStart;
struct timeval rowsStart;
struct timeval columnsStart;
struct timeval diagonalsStart;
struct timeval rowsTime;
struct timeval columnsTime;
struct timeval diagonalsTime;
struct timeval totalTime;
struct timeval threadsStart;
struct timeval threadsTime;
float elapsedRows;
float elapsedColumns;
float elapsedDiagonals;
float elapsedReading;
double elapsedThreads;
float elapsedTotal;


/*
 * Global variables that represent if the sums of the elements of very columns, rows and diagonals are of the same
 * value. They all start with 0 (FALSE), can be further changed by the pthreads.
 */
volatile int ROWS_CHECKER = 1;
volatile int COLUMN_CHECKER = 1;
volatile int DIAGONAL_CHECKER = 1;



//
// Created by Ricardo Correia on 24/03/2021.
//



/*
 * AUTHOR : PROF. PEDRO GUERREIRO
 */
int *ints_new(long n) {
    return (int *) malloc(n * sizeof(int));
}


int readFileName(const char *filename) {
    int num;
    sscanf(filename, "%*[^0-9]%d", &num);
    return num;
}


/*
 * AUTHOR : PROF. PEDRO GUERREIRO
 */

int **ints2_new(int rows, int cols) {
    int **result = (int **) malloc(rows * sizeof(int *));
    int *p = ints_new(rows * cols);
    for (int i = 0; i < rows; i++, p += cols)
        result[i] = p;
    return result;
}


int ints_get_some(FILE *f, int *a, int n) {
    int result = 0;
    int x;
    while (result < n && fscanf(f, "%d", &x) != EOF)
        a[result++] = x;
    return result;
}

void ints2_get(FILE *f, int **m, int rows, int columns) {
    ints_get_some(f, *m, rows * columns);
}

/*
 * Sums the elements of a given interval of an matrix of ints and returns the sum.
 */
long get_sum_row(int **matrix, int index, int columns) {
    long result = 0;
    for (int j = 0; j < columns; ++j) {
        result += matrix[index][j];
    }
    return result;
}


/*
 * Sums the elements of a given interval of an matrix of ints and returns the sum.
 */
long get_sum_column(int **matrix, int index, int rows) {
    long result = 0;
    for (int i = 0; i < rows; ++i) {
        result += matrix[i][index];
    }
    return result;
}


#endif //MAGICSQUARE_MAGIC_SQUARE_H
