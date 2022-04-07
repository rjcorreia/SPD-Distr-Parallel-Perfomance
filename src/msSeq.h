//
// Created by Ricardo Correia on 05/03/2021.
//

#ifndef MAGICSQUARE_SEQUENTIAL_H
#define MAGICSQUARE_SEQUENTIAL_H

#include "magicSquare.h"

/*
 * Checks if the sums of the numbers in each column are the same.
 * Returns 1 if TRUE and 0 if FALSE
 */
int check_columns_sum(int **square, int start, int rows, int columns, long sum) {
    gettimeofday(&columnsStart, 0);
    int result = 1;
    for (int j = start; j < columns; ++j) {
        long counter = 0;
        int i = 0;
        while (i < rows) {
            counter += square[i++][j];
        }
        if (counter != sum) {
            result = 0;
            printf("oi?\n");
            break;
        }
    }
    gettimeofday(&columnsTime, 0);
    return result;
}

/*
 * Checks if the sums of the numbers in each row are the same.
 * Returns 1 if TRUE and 0 if FALSE
 */
int check_rows_sum(int **square, int start, int rows, int columns, long sum) {
    gettimeofday(&rowsStart, 0);
    int result = 1;
    for (int i = start; i < rows; ++i) {
        int j = 0;
        long counter = 0;
        while (j < columns) {
            counter += square[i][j++];
        }
        if (counter != sum) {
            result = 0;
            break;
        }
    }
    gettimeofday(&rowsTime, 0);
    return result;
}

/*
 * Checks if the sums of the numbers in both main diagonals are the same.
 * Returns 1 if true and 0 if false.
 */
int check_diagonals_sum(int **square, int rows, int columns, long sum) {
    gettimeofday(&diagonalsStart, 0);
    int result = 1;
    long resultLeftDiag = 0;
    long resultRightDiag = 0;
    int j = rows - 1;
    for (int i = 0; i < columns; i++) {
        resultLeftDiag += square[i][i];
        resultRightDiag += square[j][i];
        j--;
    }
    if (resultRightDiag != sum || resultLeftDiag != sum) {
        result = 0;
    }
    gettimeofday(&diagonalsTime, 0);
    return result;
}


/*
 * Check if the sums of the numbers in each row and each column are the same
 */
int checkColumnsAndRows(int **square, int rows, int columns, long sum) {
    int result = 0;
    if (check_rows_sum(square, 0, rows, columns, sum) && check_columns_sum(square, 0, rows, columns, sum))
        result = 1;
    return result;
}


#endif //MAGICSQUARE_SEQUENTIAL_H
