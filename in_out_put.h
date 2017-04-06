#ifndef _IN_OUT_PUT_H_
  #define _IN_OUT_PUT_H_

#include <stdio.h>
#include "square_matrix.h"

void readMatrixFromConsol(void** A, const int N, const DataType dtype);

void printMatrixToConsol(void** A, const int N, const DataType dtype);

#endif