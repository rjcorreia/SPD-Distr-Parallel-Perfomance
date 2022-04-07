//
// Created by Ricardo Correia on 09/03/2021.
//

#include "time_test.h"
#include "msOMP.h"


void check_magicSquare_omp(char *filename) {
    gettimeofday(&startTotal, 0);
    int side_size = get_size_from_file(filename);
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    int **square = ints2_new(side_size, side_size);
    gettimeofday(&readingStart, 0);
    ints2_get(f, square, side_size, side_size);
    gettimeofday(&readingTime, 0);
    long sum = get_sum_column(square, 0, side_size);
    gettimeofday(&threadsStart, 0);

    omp_set_nested(1);
#pragma omp parallel sections num_threads(8)
    {
#pragma omp section
        {
            gettimeofday(&columnsStart, 0);
            check_columns_sum(square, 0, side_size, side_size, sum);
            gettimeofday(&columnsTime, 0);
        }
#pragma omp section
        {
            gettimeofday(&rowsStart, 0);
            check_rows_sum(square, 0, side_size, side_size, sum);
            gettimeofday(&rowsTime, 0);
        }
#pragma omp section
        {
            check_diagonals_sum(square, side_size, side_size, sum);
        }
    }
    gettimeofday(&threadsTime, 0);
    gettimeofday(&totalTime, 0);
    print_time_results();
    print_ms_result();
}

int main(int argc, char **argv) {
    char *filename = NULL;
    check_magicSquare_omp(argc > 1 ? argv[1] : filename);
}

