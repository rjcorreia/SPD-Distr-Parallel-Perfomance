
#include "time_test.h"
#include "msMPI.h"
#include <omp.h>

void check_rows_sum(const int *start, const int *end, int **square, int squareSize,
                    long sum, const int *processId, int *wrongRows, int *wrongRowsCount, int additionalProcesses,
                    const int *nodes) {
    for (int i = *start; i < *end; ++i) {
        MPI_Allreduce(wrongRows, wrongRowsCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        if (!*wrongRowsCount) {
            if (get_sum_row(square, i, squareSize) != sum) {
                *wrongRows = 1;
            }
        }
    }
    if (*processId != *nodes - 1) {
        for (int i = 0; i < additionalProcesses; i++) {
            MPI_Allreduce(wrongRows, wrongRowsCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        }
    }
    MPI_Allreduce(wrongRows, wrongRowsCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
}

void check_columns_sum(const int *start, const int *end, int **square, int size, long sum,
                       const int *processId, int *wrongColumns, int *wrongColumnsCount, int additionalProcesses,
                       const int *nodes) {

    for (int i = *start; i < *end; ++i) {
        MPI_Allreduce(wrongColumns, wrongColumnsCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        if (!*wrongColumnsCount) {
            if (get_sum_column(square, i, size) != sum) {
                *wrongColumns = 1;
            }
        }
    }
    if (*processId != *nodes - 1) {
        for (int i = 0; i < additionalProcesses; i++) {
            MPI_Allreduce(wrongColumns, wrongColumnsCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        }
    }
    MPI_Allreduce(wrongColumns, wrongColumnsCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
}

void check_diagonals_sum(int **square, int squareSize, long sum, int *wrongDiagonalsCount) {
    gettimeofday(&diagonalsStart, 0);
    long resultLeftDiag = 0;
    long resultRightDiag = 0;
    int j = squareSize - 1;
    for (int i = 0; i < squareSize; i++) {
        resultLeftDiag += square[i][i];
        resultRightDiag += square[j][i];
        j--;
    }
    if (resultRightDiag != sum || resultLeftDiag != sum) {
        *wrongDiagonalsCount = 1;
    }
    gettimeofday(&diagonalsTime, 0);
}

void check_ms_mpi(int argc, char **argv, int **square, int sideSize, long sum) {
    int wrongRows = 0;
    int wrongColumns = 0;
    int wrongRowsCount = 0;
    int wrongColumnsCount = 0;
    int wrongDiagonalsCount = 0;
    int processId, nodes;
    int start, portionOfSquare, end, additionalProcesses;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);
    MPI_Comm_size(MPI_COMM_WORLD, &nodes);

    portionOfSquare = sideSize / (nodes);
    start = portionOfSquare * processId;
    if (processId == nodes - 1)
        portionOfSquare = sideSize - start;

    end = start + portionOfSquare;
    additionalProcesses = sideSize % nodes;


    gettimeofday(&columnsStart, 0);
    check_columns_sum(&start, &end, square, sideSize, sum, &processId, &wrongColumns, &wrongRowsCount,
                      additionalProcesses, &nodes);
    MPI_Barrier(MPI_COMM_WORLD);
    gettimeofday(&columnsTime, 0);

    gettimeofday(&rowsStart, 0);
    check_rows_sum(&start, &end, square, sideSize, sum, &processId, &wrongRows, &wrongRowsCount,
                   additionalProcesses, &nodes);
    MPI_Barrier(MPI_COMM_WORLD);
    gettimeofday(&rowsTime, 0);
    if (processId == 0) {
        if (!wrongRowsCount && !wrongColumnsCount)
            check_diagonals_sum(square, sideSize, sum, &wrongDiagonalsCount);
        print_ms_result(&wrongColumnsCount, &wrongRowsCount, &wrongDiagonalsCount);
        gettimeofday(&totalTime, 0);
        print_time_results();
    }
    MPI_Finalize();
}

int main(int argc, char **argv) {
    gettimeofday(&startTotal, 0);
    FILE *f = fopen(argv[1], "r");
    assert(f != NULL);
    int sideSize = get_size_from_file(argv[1]);
    int **square = ints2_new(sideSize, sideSize);
    gettimeofday(&readingStart, 0);
    ints2_get(f, square, sideSize, sideSize);
    gettimeofday(&readingTime, 0);
    long sum = get_sum_row(square, 0, sideSize);
    check_ms_mpi(argc, argv, square, sideSize, sum);
    return 0;
}