//
// Created by Ricardo Correia on 28/03/2021.
//

#include "time_test.h"
#include "msMPI.h"

void check_rows_sum(const int *start, const int *end, int **square, int squareSize,
                    long sum, const int *processId, int *wrongRows, int *wrongRowsCount, int additionalProcesses,
                    const int *nodes) {
//    printf("I am process %d i have %d start and %d end, total: %d\n", *processId, *start, *end,
//           *end - *start);
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
//    printf("I am process %d i have %d start and %d end, total: %d\n", *processId, *start, *end,
//    *end - *start);
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
}


int main(int argc, char **argv) {

    FILE *f = fopen(argv[1], "r");
    assert(f != NULL);
    int side_size = readFileName(argv[1]);
    int **square = ints2_new(side_size, side_size);
    ints2_get(f, square, side_size, side_size);
    long sum = get_sum_row(square, 0, side_size);
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


    portionOfSquare = side_size / (nodes);
    start = portionOfSquare * processId;
    if (processId == nodes - 1)
        portionOfSquare = side_size - start;

    end = start + portionOfSquare;
    additionalProcesses = side_size % nodes;


    check_columns_sum(&start, &end, square, side_size, sum, &processId, &wrongColumns, &wrongRowsCount,
                      additionalProcesses, &nodes);
    MPI_Barrier(MPI_COMM_WORLD);

    check_rows_sum(&start, &end, square, side_size, sum, &processId, &wrongRows, &wrongRowsCount,
                   additionalProcesses, &nodes);
    MPI_Barrier(MPI_COMM_WORLD);

    if (processId == 0) {
        if (!wrongRowsCount && !wrongColumnsCount)
            check_diagonals_sum(square, side_size, sum, &wrongDiagonalsCount);
        print_ms_result(&wrongColumnsCount, &wrongRowsCount, &wrongDiagonalsCount);
    }


    MPI_Finalize();

    return 0;
}