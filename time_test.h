//
// Created by Ricardo Correia on 05/03/2021.
//
#include <sys/time.h>

#ifndef MAGICSQUARE_TIME_TEST_H
#define MAGICSQUARE_TIME_TEST_H


/*
 *
 */
float timedifference_msec(struct timeval t0, struct timeval t1) {
    return (float) (t1.tv_sec - t0.tv_sec) * 1000.0f + (float) (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

#endif //MAGICSQUARE_TIME_TEST_H
