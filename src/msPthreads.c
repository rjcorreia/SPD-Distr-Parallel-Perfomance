//
// Created by Ricardo Correia on 05/03/2021.
//

#include "msPthreads.h"


/*
 * child function, it receives a Thread struct and checks which job the thread has to do, it can be responsible for:
 * 1 - check if the sums of all the elements of every each row are the same
 * 2 - check if the sums of all the elements of every each column are the same
 * 3 - check if the sums of all the elements of the main diagonals are the same
 */
void *child(void *secondThread) {
    Vector secondThread1 = *((Vector *) secondThread);
    if (secondThread1.job == COLUMNS_DUTY) {
        check_columns_sum(secondThread1.square, secondThread1.start, side_size, secondThread1.end);
    } else if (secondThread1.job == ROWS_DUTY) {
        check_rows_sum(secondThread1.square, secondThread1.start, secondThread1.end, side_size);
    } else if (secondThread1.job == DIAGONALS_DUTY) {
        check_diagonals_sum(secondThread1.square, side_size, side_size);
    } else {
        exit(0);
    }
    return NULL;
}

/*
 * Initializes the necessary number of threads
 */
void init_pthread_array(Vector *secondThreadArr, pthread_t *threadArray, int job) {
    int code;

    if (job == ROWS_DUTY) {
        for (long i = 0; i < rowThreads; i++) {
            pthread_create(&threadArray[i], NULL, child, (void *) &secondThreadArr[i]);
        }
        gettimeofday(&rowsStart, 0);
    } else if (job == COLUMNS_DUTY) {
        for (long i = 0; i < columnThreads; i++) {
            code = pthread_create(&threadArray[i], NULL, child, (void *) &secondThreadArr[i]);
            if (code) {
                fprintf(stderr, "pthread_create failed with code %d\n", code);
            }
        }
        gettimeofday(&columnsStart, 0);
    }
}

/*
 * Run join on every pthread to synchronize them all
 */
void join_pthreads(pthread_t *threadArray, int job) {
    int nThreads = 0;
    if (job == ROWS_DUTY)
        nThreads = rowThreads;
    else if (job == COLUMNS_DUTY)
        nThreads = columnThreads;
    for (long i = 0; i < nThreads; i++) {
        pthread_join(threadArray[i], NULL);
    }
}


/*
 * Initializes the vectors and puts them in a array.
 Each pthread will receive a Vector, so we need as many as we have threads. If we have
 less pthreads than the size of the resulting Vector we need to deal with dividing the
 data among the existing Vectors.
 */
void init_vectors(Vector *secondThreadArr, int **square, int job, int nThreads) {
    int result = 0;
    long remaining = side_size % nThreads;
    int i = 0;
    int remainingLeft = 0;
    while (i < side_size) {
        if (remainingLeft < remaining) {
            secondThreadArr[result++] = vector(square, job, i, i + (side_size / nThreads) + 1);
            i += (side_size / nThreads) + 1;
            remainingLeft++;
        } else {
            secondThreadArr[result++] = vector(square, job, i, i + (side_size / nThreads));
            i += (side_size / nThreads);
        }
    }
}


/*
 * Creates two arrays of pthreads (one for rows and the other for columns) and a single Vector struct for the diagonals,
 * afterwards it initiates the pthreads arrays with the Vector arrays, synchronize all the threads in the end.
 */
void initiate_pthreads(int **square, int rows, Vector *rowsVectorArray, Vector *columnsVectorArray) {
    pthread_t child_thread;
    pthread_t columnPthreadArray[columnThreads];
    pthread_t rowPthreadArray[rowThreads];
    int code;
    Vector diagonalsThread = vector(square, DIAGONALS_DUTY, 0, rows);
    gettimeofday(&threadsStart, 0);
    init_pthread_array(rowsVectorArray, rowPthreadArray, ROWS_DUTY);
    init_pthread_array(columnsVectorArray, columnPthreadArray, COLUMNS_DUTY);
    code = pthread_create(&child_thread, NULL, child, (void *) &diagonalsThread);
    if (code) {
        fprintf(stderr, "pthread_create failed with code %d\n", code);
    }
    join_pthreads(rowPthreadArray, ROWS_DUTY);
    gettimeofday(&rowsTime, 0);
    join_pthreads(columnPthreadArray, COLUMNS_DUTY);
    gettimeofday(&columnsTime, 0);
    pthread_join(child_thread, NULL);
    gettimeofday(&threadsTime, 0);
}


/*
 * Checks if the given square from the input is either a Magic Square, an Imperfect Magic Square or is not a Magic
 * Square, with pthreads parallel programming.
 */
void check_ms_pthreads(const char *filename) {
    gettimeofday(&startTotal, 0);
    side_size = get_size_from_file(filename);
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    int **square = ints2_new(side_size, side_size);
    gettimeofday(&readingStart, 0);
    ints2_get(f, square, side_size, side_size);
    gettimeofday(&readingTime, 0);
    sum = get_sum_column(square, 0, side_size);
    Vector columnsArray[columnThreads];
    Vector rowsArray[rowThreads];
    init_vectors(rowsArray, square, ROWS_DUTY, rowThreads);
    init_vectors(columnsArray, square, COLUMNS_DUTY, columnThreads);
    initiate_pthreads(square, side_size, rowsArray, columnsArray);
    gettimeofday(&totalTime, 0);
    print_ms_result();
    print_time_results();
}

/*
 * PTHREADS PROGRAMING UNIT TESTS
 */

int main(int argc, char **argv) {
    char *filename = NULL;
    check_ms_pthreads(argc > 1 ? argv[1] : filename);
    return 0;
}