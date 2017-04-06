#include "in_out_put.h"


void readMatrixFromConsol(void** A, const int N, const DataType dtype)
{
  if (A == NULL || N == 0)
    return;

  switch (dtype)
  {
  case INT_TYPE:
    for (int i = 0; i < N; i++)
    {
      int* a_i = (int*)(A[i]);
      for (int j = 0; j < N; j++)
      {
        scanf_s("%d", &a_i[j], sizeof(int));
      }
      printf("\n");
    }

    break;
  case DOUBLE_TYPE:
    for (int i = 0; i < N; i++)
    {
      double* a_i = (double*)(A[i]);
      for (int j = 0; j < N; j++)
      {
        scanf_s("%lf", &a_i[j]);
      }
    }


    break;
  case COMPLEX_TYPE:
    for (int i = 0; i < N; i++)
    {
      Complex* a_i = (Complex*)(A[i]);
      for (int j = 0; j < N; j++)
      {
        scanf_s("%lf+%lfi", &(a_i[j].m_re), &(a_i[j].m_im));
        double re = a_i[j].m_re;
        double im = a_i[j].m_im;
      }
      printf("\n");
    }


    break;
  default:
    break;
  }
}

void printMatrixToConsol(void** A, const int N, const DataType dtype)
{
  if (A == NULL || N == 0)
  {
    printf("There is error input print data!");
    return;
  }

  switch (dtype)
  {
  case INT_TYPE:
    printf("Matrix is \n");
    for (int i = 0; i < N; i++)
    {
      int* a_i = (int*)(A[i]);
      for (int j = 0; j < N; j++)
      {
        printf("%d ", a_i[j]);
      }
      printf("\n");
    }

    break;
  case DOUBLE_TYPE:
    printf("Matrix is \n");
    for (int i = 0; i < N; i++)
    {
      double* a_i = (double*)(A[i]);
      for (int j = 0; j < N; j++)
      {
        printf("%.4lf ", a_i[j]);
      }
      printf("\n");
    }


    break;
  case COMPLEX_TYPE:
    printf("Matrix is \n");
    for (int i = 0; i < N; i++)
    {
      Complex* a_i = (Complex*)(A[i]);
      for (int j = 0; j < N; j++)
      {
        printf("%.2lf+%.2lfi ", a_i[j].m_re, a_i[j].m_im);
      }
      printf("\n");
    }


    break;
  default:
    break;
  }
}