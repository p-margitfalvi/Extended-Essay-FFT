//
//  fht.h
//  extendid esej
//
//  Created by Pavol Margitfalvi on 06/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//



#ifndef fht_h
#define fht_h

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include <float.h>

double randf(void);
double dAvg(int array[], size_t length);
int n_close(double A, double B, double maxDiff, double maxRelDiff);
void swap2 (double *x, int i, int j);
double * bitreversal2(double *x, int N);
double *  fht(double *x, double *xo, double *c, double *s,int N,int p);

#endif /* fht_h */
