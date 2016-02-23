#pragma once

#include <vector>

using namespace std;

class Matrix {
public:
  typedef double scalar_t;

private:
  unsigned size_i, size_j, index;
  vector<unsigned> lines, rows;
  static vector<vector<vector<scalar_t> > > contents;

public:
  Matrix(unsigned n, unsigned p);
  unsigned get_size_i(void) const;
  unsigned get_size_j(void) const;
  void set(unsigned i, unsigned j, scalar_t x);
  scalar_t get(unsigned i, unsigned j) const;

  void print() const;
};

/*****************************************************/

Matrix operator+(const Matrix& M1, const Matrix& M2);

Matrix operator-(const Matrix& M1, const Matrix& M2);

Matrix operator*(Matrix::scalar_t a, const Matrix& M1);

Matrix operator*(const Matrix& M1, const Matrix& M2);

//Matrix transpose(const Matrix& M1);

Matrix Id(unsigned n);

double norm(const Matrix& M1);

//Matrix::scalar_t determinant(const Matrix& M1);

//Matrix inverse(const Matrix& M1);

