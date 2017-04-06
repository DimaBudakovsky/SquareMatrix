#include <stdio.h>

#include "square_matrix.h"
#include "in_out_put.h"

int main()
{
  unsigned int N = 0;
  printf("Enter the size of the square matrix\n");
  scanf_s("%d", &N, sizeof(int));
  if (N > 0)
    printf("Size of the square matrix is %d\n", N);
  else
  {
    printf("ERROR:There is incorrect size of the square matrix!\n");
    getchar();
    return -1;
  }

  int d_type = 0;
  DataType dtype = INT_TYPE;
  printf("Enter the data type for the square matrix:\nINT - 0\nDOUBLE - 1\nCOMPLEX - 2\n");
  scanf_s("%d", &d_type, sizeof(int));
  switch (d_type)/*Выбор типа данных*/
  {
  case 0:
    dtype = INT_TYPE;
    printf("Data type for the square matrix is INT_TYPE\n");
    break;
  case 1:
    dtype = DOUBLE_TYPE;
    printf("Data type for the square matrix is DOUBLE_TYPE\n");
    break;
  case 2:
    dtype = COMPLEX_TYPE;
    printf("Data type for the square matrix is COMPLEX_TYPE\n");
    break;
  default:
    printf("ERROR:There is incorrect data type!\n");
    getchar();
    return -1;
  }
  

  void** A = createSquareMatrix(N, dtype);

  readMatrixFromConsol((void**)A, N, dtype);
  printf("A = \n");
  printMatrixToConsol((void**)A, N, dtype);
  printf("\n");

  void** B = createSquareMatrix(N, dtype);

  readMatrixFromConsol((void**)B, N, dtype);
  printf("B = \n");
  printMatrixToConsol((void**)B, N, dtype);
  printf("\n");

  void** SumMatrix = createSquareMatrix(N, dtype);
  void** MultMatrix = createSquareMatrix(N, dtype);

  bool res = getSumMatrix((void**)A, (void**)B, (void**)SumMatrix, N, dtype);
  if (res)
  {
    printf("SumMatrix = \n");
    printMatrixToConsol((void**)SumMatrix, N, dtype);
    printf("\n");
  }
  else
    printf("Operation sum. has been unsuccessful!\n");

  res = getMultMatrix( A, B, MultMatrix, N, dtype);
  if (res)
  {
    printf("MultMatrix = \n");
    printMatrixToConsol((void**)MultMatrix, N, dtype);
    printf("\n");
  }
  else
    printf("Operation mult. has been unsuccessful!\n");



  getchar();
  getchar();

  freeSquareMatrix(A, N, dtype);/*Освобождение выделенной памяти*/
  freeSquareMatrix(B, N, dtype);
  freeSquareMatrix(SumMatrix, N, dtype);
  freeSquareMatrix(MultMatrix, N, dtype);

  return 0;
}