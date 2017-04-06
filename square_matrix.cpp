#include <stdlib.h>
#include "square_matrix.h"


Complex sum(const Complex A, const Complex B)/*Сложение комплексных чисел*/
{
  Complex C;
  C.init(A.m_re + B.m_re, A.m_im + B.m_im);
  return C;
}

Complex multiplication(const Complex A, const Complex B)/*Умножение комплексных чисел*/
{
  Complex C;
  C.init(A.m_re * B.m_re - A.m_im * B.m_im, A.m_im * B.m_re + A.m_re * B.m_im);
  return C;
}


void** createSquareMatrix(const unsigned int N, const DataType dtype)/*Функция создания матриц*/
{
  void** A = NULL;

  if (N == 0)
    return NULL;

  switch (dtype)
  {
  case INT_TYPE:
    A = (void **)malloc(N * sizeof(int*));
    if (A == NULL)
      return NULL;
    for(unsigned int i = 0; i < N; i++) 
    {
      A[i] = (void *)malloc(N * sizeof(int));
      if (A[i] == NULL)
        return NULL;
    }
    for(unsigned int i = 0; i < N; i++) 
    {
      int* a_i = (int*)A[i];
      for (unsigned int j = 0; j < N; j++)
        a_i[j] = 0;
    }
    break;
  case DOUBLE_TYPE:
    A = (void **)malloc(N * sizeof(double*));
    if (A ==  NULL)
      return NULL;
    for(unsigned int i = 0; i < N; i++) 
    {
      A[i] = (void *)malloc(N * sizeof(double));
      double* a_i = (double*)A[i];
      if (A[i] == NULL)
        return NULL;
      for (unsigned int j = 0; j < N; j++)
        a_i[j] = 0;
    }
    break;
  case COMPLEX_TYPE:
    A = (void **)malloc(N * sizeof(Complex*));
    if (A == NULL)
      return NULL;
    for(unsigned int i = 0; i < N; i++)
    {
      A[i] = (void *)malloc(N * sizeof(Complex));
      Complex* a_i = (Complex*)(A[i]);
      if (A[i] == NULL)
        return NULL;
      for (unsigned int j = 0; j < N; j++)
        a_i[j].init(.0,.0);
    }
    break;
  default:
    break;
  }

  return A;
}

void freeSquareMatrix(void** A, const unsigned int N, const DataType dtype)/*Функция освобождения памяти*/
{
  if (A == NULL)
    return;
  switch (dtype)
  {
  case INT_TYPE:
    for(unsigned int i = 0; i < N; i++)
      free((int*) A[i]);

    free((int**) A);
    break;
  case DOUBLE_TYPE:
    for(unsigned int i = 0; i < N; i++) 
      free((double*) A[i]);

    free((double**) A);
    break;
  case COMPLEX_TYPE:
    for(unsigned int i = 0; i < N; i++)
      free((Complex*) A[i]);

    free((Complex**) A);
    break;
  default:
    break;
  }

}

bool getSumMatrix(const void* const *const A, const void* const* const B, void** C, const int N, const DataType dtype)/*Сложение матриц*/
{
  bool res(true);
  if (A == NULL)
    return false;

  if (B == NULL)
    return false;

  if (C == NULL)
    return false;

  switch (dtype)
  {
    case INT_TYPE:
      for (int i = 0; i < N; i++)
      {
        int* a_i = (int*)(A[i]);
        int* b_i = (int*)(B[i]);
        int* c_i = (int*)(C[i]);
        for (int j = 0; j < N; j++)
        {
          c_i[j] = a_i[j] + b_i[j];
        }
      }
      break;
    case DOUBLE_TYPE:
      for (int i = 0; i < N; i++)
      {
        double* a_i = (double*)(A[i]);
        double* b_i = (double*)(B[i]);
        double* c_i = (double*)(C[i]);
        for (int j = 0; j < N; j++)
        {
          c_i[j] = a_i[j] + b_i[j];
        }
      }
      break;
    case COMPLEX_TYPE:
      for (int i = 0; i < N; i++)
      {
        Complex* a_i = (Complex*)(A[i]);
        Complex* b_i = (Complex*)(B[i]);
        Complex* c_i = (Complex*)(C[i]);
        for (int j = 0; j < N; j++)
        {
          c_i[j] = sum(a_i[j], b_i[j]);
        }
      }
      break;
    default:
      res = false;
      break;
  }
  return res;
}

bool TranspMatrix(const void* const* const B, const int N, void** d, const DataType dtype)/*Транспонирование матрицы B*/
{
  bool res = true;
  int** buf_int = NULL;
  double** buf_double = NULL;
  Complex** buf_complex = NULL;
  if (B == NULL)
    return false;

  switch (dtype)
  {
  case INT_TYPE:
    buf_int = (int**)B;
    for (int i = 0; i < N; i++)
    {
      int* d_i = (int*)d[i];
      for (int j = 0; j < N; j++)
      {
        d_i[j] = buf_int[j][i];
      }
    }
    break;
  case DOUBLE_TYPE:
    buf_double = (double**)B;
    for (int i = 0; i < N; i++)
    {
      double* d_i = (double*)d[i];
      for (int j = 0; j < N; j++)
      {
        d_i[j] = buf_double[j][i];
      }
    }
    break;
  case COMPLEX_TYPE:
    buf_complex = (Complex**)B;
    for (int i = 0; i < N; i++)
    {
      Complex* d_i = (Complex*)d[i];
      for (int j = 0; j < N; j++)
      {
        d_i[j] = buf_complex[j][i];
      }
    }
    break;
  default:
    res = false;
    break;
  }
  return res;
}

bool getMultMatrix(const void* const *const A, const void* const* const B, void** C, const int N, const DataType dtype)/*Умножение матриц*/
{
  bool res(true);
  if (A == NULL)
    return false;

  if (B == NULL)
    return false;

  if (C == NULL)
    return false;

  void** B_transp = createSquareMatrix(N, dtype);
  res = TranspMatrix(B, N, B_transp, dtype);

  switch (dtype)
  {
  case INT_TYPE:
    for (int i = 0; i < N; i++)
    {
      int* c_i = (int*)(C[i]);
      int* a_i = (int*)(A[i]);
      for (int j = 0; j < N; j++)
      {
        int* d_j = (int*)(B_transp[j]);
        for (int k = 0; k < N; k++)
          c_i[j] = c_i[j] + a_i[k] * d_j[k];
      }
    }
    break;
  case DOUBLE_TYPE:
    for (int i = 0; i < N; i++)
    {
      double* a_i = (double*)(A[i]);
      double* c_i = (double*)(C[i]);
      for (int j = 0; j < N; j++)
      {
        double* d_j = (double*)(B_transp[j]);
        for (int k = 0; k < N; k++)
          c_i[j] = c_i[j] + a_i[k] * d_j[k];
      }
    }
    break;
  case COMPLEX_TYPE:
    for (int i = 0; i < N; i++)
    {
      Complex* a_i = (Complex*)(A[i]);
      Complex* c_i = (Complex*)(C[i]);
      for (int j = 0; j < N; j++)
      {
        Complex* d_j = (Complex*)(B_transp[j]);
        for(int k=0; k < N; k++)
          c_i[j] = sum(c_i[j], multiplication(a_i[k], d_j[k]));
      }
    }
    break;
  }
  freeSquareMatrix(B_transp, N, dtype);
  return res;
}

