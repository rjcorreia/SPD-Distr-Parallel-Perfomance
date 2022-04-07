//
// Created by Ricardo Correia on 02/03/2021.
//

#include "time_test.h"
#include "msSeq.h"


/*
 * Checks if the given square is either a Magic Square, an Imperfect Magic Square or is Not a Magic
 * Square, with seq programming. It first checks if each columns and rows have the same sum and than
 * the diagonals.
 */
void printSquareResult(int **square, int rows, long sum) {
    if (checkColumnsAndRows(square, rows, rows, sum)) {
        if (check_diagonals_sum(square, rows, rows, sum)) {
            printf("Quadrado mágico.\n");
        } else {
            printf("Quadrado mágico imperfeito.\n");
        }
    } else {
        printf("Não é quadrado mágico.\n");
    }
}


/*
 * Prints the time results of some selected operations of the program.
 */
void print_time_results() {
    elapsedReading = timedifference_msec(readingStart, readingTime);
    elapsedColumns = timedifference_msec(columnsStart, columnsTime);
    elapsedRows = timedifference_msec(rowsStart, rowsTime);
    elapsedDiagonals = timedifference_msec(diagonalsStart, diagonalsTime);
    elapsedTotal = timedifference_msec(startTotal, totalTime);
    printf("R %f ms.\n", elapsedRows);
    printf("C %f ms.\n", elapsedColumns);
    printf("D %f ms.\n", elapsedDiagonals);
    printf("E %f ms.\n", elapsedTotal);
    printf("e %f ms.\n", elapsedTotal - elapsedReading);
}


/*
 * Main function of the seq program, it reads a file given, creates a bi-dimensional array representing
 * square,calculates the sum of the first row, prints the result of the avaliation of the square and prints some
 * execution times.
 */
void check_ms_sequential(const char *filename) {
    gettimeofday(&startTotal, 0);
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    int side_size = get_size_from_file(filename);
    int **square = ints2_new(side_size, side_size);
    gettimeofday(&readingStart, 0);
    ints2_get(f, square, side_size, side_size);
    gettimeofday(&readingTime, 0);
    long sum = get_sum_column(square, 0, side_size);
    printf("%lu\n", sum);
    printSquareResult(square, side_size, sum);
    gettimeofday(&totalTime, 0);
    print_time_results();
}


/*
 * SEQUENTIAL PROGRAMMING UNIT TESTS
 */


int main(int argc, char **argv) {
    char *filename = NULL;
    check_ms_sequential(argc > 1 ? argv[1] : filename);
    return 0;
}