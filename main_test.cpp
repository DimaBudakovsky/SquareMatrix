#include <stdio.h>

#include "square_matrix.h"
#include "in_out_put.h"

#pragma warning(disable : 4996)

double delta = 1.0/100;
          
bool compareMatrix(const void* const *const A, const void* const *const B, const unsigned int N, const DataType dtype)/*Функция сравнения матриц*/
{
  bool res = true;
  switch (dtype)
  {
  case INT_TYPE:
    for(unsigned int i = 0; i < N; i++)
    {
      int* a_i = (int*) (A[i]);
      int* b_i = (int*) (B[i]);
      for (unsigned int j = 0; j < N; j++)
        res= res && (a_i[j] == b_i[j]);
    }

    break;

  case DOUBLE_TYPE:
    for(unsigned int i = 0; i < N; i++)
    {
      double* a_i = (double*) (A[i]);
      double* b_i = (double*) (B[i]);
      for (unsigned int j = 0; j < N; j++)
        res= res && (a_i[j] <= b_i[j] + delta && a_i[j] >= b_i[j] - delta);
    }

    break;

  case COMPLEX_TYPE:
    for(unsigned int i = 0; i < N; i++)
    {
      Complex* a_i = (Complex*) (A[i]);
      Complex* b_i = (Complex*) (B[i]);
      for (unsigned int j = 0; j < N; j++)
      {
        res= res && (a_i[j].m_im <= b_i[j].m_im + delta && a_i[j].m_im >= b_i[j].m_im - delta) && 
                    (a_i[j].m_re <= b_i[j].m_re + delta && a_i[j].m_re >= b_i[j].m_re - delta);
      }
    }

    break;

  default:
    res = false;
    break;
  }

  return res;
}

bool do_sum_test(const void* const *const A, const void* const *const B, const void* const *const C, const unsigned int N, const DataType dtype)/*Тестирование сложения*/
{
  bool res = false;
  void** sum_matrix = createSquareMatrix(N, dtype);
  if (getSumMatrix((void**)A, (void**)B, (void**)sum_matrix, N, dtype) && 
      compareMatrix(sum_matrix, C, N, dtype))
    res = true;

  freeSquareMatrix(sum_matrix, N, dtype);
  return res;
}

bool do_mult_test(const void* const *const A, const void* const *const B, const void* const *const C, const unsigned int N, const DataType dtype)/*Тестирование умножения*/
{
  bool res = false;
  void** mult_matrix = createSquareMatrix(N, dtype);
  if (getMultMatrix((void**)A, (void**)B, (void**)mult_matrix, N, dtype) && 
    compareMatrix(mult_matrix, C, N, dtype))
    res = true;

  freeSquareMatrix(mult_matrix, N, dtype);
  return res;
}

bool readMatrix(FILE *in, void** A, const unsigned int N, const DataType dtype)/*Чтение матриц из файла*/
{
  if (A == NULL || N == 0)
    return false;

  switch (dtype)
  {
  case INT_TYPE:
    for (unsigned int i = 0; i < N; i++)
    {
      int* a_i = (int*)(A[i]);
      for (unsigned int j = 0; j < N; j++)
        fscanf_s(in,"%d",&a_i[j]);
    }

    break;
  case DOUBLE_TYPE:
    for (unsigned int i = 0; i < N; i++)
    {
      double* a_i = (double*)(A[i]);
      for (unsigned int j = 0; j < N; j++)
        fscanf_s(in,"%lf",&a_i[j]);
    }
    break;
  case COMPLEX_TYPE:
    for (unsigned int i = 0; i < N; i++)
    {
      Complex* a_i = (Complex*)(A[i]);
      for (unsigned int j = 0; j < N; j++)
      {
        fscanf_s(in,"%lf+%lfi", &(a_i[j].m_re), &(a_i[j].m_im));
        double re = a_i[j].m_re;
        double im = a_i[j].m_im;
      }
    }

    break;
  default:
    return false;
  }
  return true;
}

bool read_test_file(FILE *in)/*Чтение тестов из файла*/
{
  bool res = true;
  unsigned int N = 0;
  int type_data = 0;

  fscanf_s(in,"%d%d",&N, &type_data);

  DataType dtype;
  switch (type_data)
  {
  case 0:
    dtype = INT_TYPE;
    break;
  case 1:
    dtype = DOUBLE_TYPE;
    break;
  case 2:
    dtype = COMPLEX_TYPE;
    break;
  default:
    return false;
  }
  void** data[4];
  for (unsigned int k = 0; k < 4; k++)
  {
    data[k] = createSquareMatrix(N, dtype);
    res = res && readMatrix(in, data[k], N, dtype);
  }

  if (!res)
    printf("Error reading matrix!\n");
  else
  {
    if (do_sum_test(data[0], data[1], data[2], N, dtype))
      printf("Sum test has been gone successful!\n");
    else
      printf("Warning: Sum test has been gone unsuccessful!\n");

    if (do_mult_test(data[0], data[1], data[3], N, dtype))
      printf("Mult test has been gone successful!\n");
    else
      printf("Warning: Mult test has been gone unsuccessful!\n");
  }

  for (unsigned int k = 0; k < 4; k++)
    freeSquareMatrix(data[k], N, dtype);

  return res;
}


int main()
{
    FILE *pFile=fopen("test_square_mtrix.txt", "rt");
    if (pFile == NULL)
    {
        printf("Error opening file!\n");
        return -1;
    }
    int inx = 1;
    while(!feof(pFile))
    {
        printf("Number Test: %d\n", inx);
        read_test_file(pFile);
        printf("\n");
        inx++;
    }
    fclose(pFile);

    getchar();

    return 0;
}
