#ifndef _SQUARE_MATRIX_H_
  #define _SQUARE_MATRIX_H_

enum DataType/*Перечисление типов данных*/
{
  INT_TYPE = 0,
  DOUBLE_TYPE = 1,
  COMPLEX_TYPE = 2
};

struct Complex
{
  double m_re;
  double m_im;

  void init(const double re, const double im)
  {
    m_re = re;
    m_im = im;
  }
};

Complex sum(const Complex A, const Complex B);
Complex multiplication(const Complex A, const Complex B);


void** createSquareMatrix(const unsigned int N, const DataType dtype);

void freeSquareMatrix(void** A, const unsigned int N, const DataType dtype);

//C = A + B with size NxN
bool getSumMatrix(const void* const *const A, const void* const* const B, void** C, const int N, const DataType dtype);

//C = A * B with size NxN
bool getMultMatrix(const void* const *const A, const void* const* const B, void** C, const int N, const DataType dtype);

bool TranspMatrix(const void* const *const B, const int N, void** d, const DataType dtype);


#endif //_SQUARE_MATRIX_H_