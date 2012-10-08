#ifndef LDA_ALPHA_H
#define LDA_ALPHA_H

#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "lda.h"
#include "utils.h"

#define NEWTON_THRESH 1e-5
#define MAX_ALPHA_ITER 1000

double alhood(double a, double ss, long D, int K);
double d_alhood(double a, double ss, long D, int K);
double d2_alhood(double a, long D, int K);
double opt_alpha(double ss, long D, int K);

#endif
