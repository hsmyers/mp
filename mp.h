/**
 **  @file mp.h
 **  @author Hugh S. Myers
 **  @brief Includes and declarations for mp.c
 **  @date Mon Aug 14 11:22:27 2017
 **
 **  @section DESCRIPTION
 **
 **  Support file for mp.c. This removes the 'clutter' from the primary file for mp.exe.
 **
 **  @bug No known bugs.
 **/
#ifndef _MP_H // Include guard
#define _MP_H
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <omp.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include <gd.h>
#include <assert.h>
#include "palette.h"
#include "elapsed.h"
#include "colors.h"
#include "getopt.h"
#include "util.h"

typedef struct timespec time_spec;

Array colors;
gdImagePtr im;

ColorFLT MSetCPMFLT( ColorFLT cp, int maxiter );
ColorDBL MSetCPMDBL( ColorDBL cp, int maxiter );
ColorLDBL MSetCPMLDBL( ColorLDBL cp, int maxiter );
Color128 MSetCPMFLT128( Color128 cp, int maxiter );
ColorFLT GiveDistanceFLT( ColorFLT cp, int iMax );
ColorDBL GiveDistanceDBL( ColorDBL cp, int iMax );
ColorLDBL GiveDistanceLDBL( ColorLDBL cp, int iMax );
Color128 GiveDistanceFLT128( Color128 cp, int iMax );
Parameters MSetDBL( Parameters g );
Parameters MSetFLT( Parameters g );
Parameters MSetFLT128( Parameters g );
Parameters MSetLDBL( Parameters g );

float gauss_kernel[3][3] = {
    {1.0, 2.0, 1.0},
    {2.0, 4.0, 2.0},
    {1.0, 2.0, 1.0}
};

float lpf_filter_6[3][3] = {
    {0.0, 1.0, 0.0},
    {1.0, 2.0, 1.0},
    {0.0, 1.0, 0.0}
};

float lpf_filter_9[3][3] = {
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0}
};

float lpf_filter_10[3][3] = {
    {1.0, 1.0, 1.0},
    {1.0, 2.0, 1.0},
    {1.0, 1.0, 1.0}
};

float lpf_filter_16[3][3] = {
    {1.0, 2.0, 1.0},
    {2.0, 4.0, 2.0},
    {1.0, 2.0, 1.0}
};

float lpf_filter_32[3][3] = {
    {1.0, 4.0, 1.0},
    {4.0, 12.0, 4.0},
    {1.0, 4.0, 1.0}
};

float hpf_filter_1[3][3] = {
    {0.0, -1.0, 0.0},
    {-1.0, 5.0, -1.0},
    {0.0, -1.0, 0.0}
};

float intensified_sharpen_kernel[3][3] = {
    {-1.0, -1.0, -1.0},
    {-1.0, 8.0, -1.0},
    {-1.0, -1.0, -1.0}
};

float hpf_filter_2[3][3] = {
    {-1.0, -1.0, -1.0},
    {-1.0, 9.0, -1.0},
    {-1.0, -1.0, -1.0}
};

float hpf_filter_3[3][3] = {
    {1.0, -2.0, 1.0},
    {-2.0, 5.0, -2.0},
    {1.0, -2.0, 1.0}
};

#endif // _MP_H