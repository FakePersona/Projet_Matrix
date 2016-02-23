#include <iostream>
#include <iomanip>

#include <string>
#include <cmath>
#include <cassert>
#include <cstdlib>

#include <vector>

#include "matrix.hh"

using namespace std;

vector<vector<vector<Matrix::scalar_t> > > Matrix::contents;

Matrix::Matrix(unsigned n, unsigned p) {
  size_i = n;
  size_j = p;
  assert(1 <= size_i);
  assert(1 <= size_j);

  lines = vector<bool>(size_i, true);
  rows = vector<bool>(size_j, true);

  index = contents.size();
  contents.push_back( vector<vector<scalar_t> >(size_i) );
  for (unsigned i = 0; i < size_i; i++)
    contents.at(index).at(i) = vector<scalar_t>(size_j, 0.0);	// Initialization to 0.0
}

Matrix::Matrix(const Matrix& m)  
{
    size_i = m.size_i;
    size_j = m.size_j;
    index = m.index;
    lines = m.lines;
    rows = m.rows;
}

unsigned Matrix::get_size_i() const {
  return size_i;
}

unsigned Matrix::get_size_j() const {
  return size_j;
}


static unsigned index_nth(vector<bool> vect, unsigned n) 
{    
    unsigned count = 0, k;
    for (k = 0; count <= n && k < vect.size(); k++)
        count += vect[k];
    return k-1;
}



void Matrix::removeLine(unsigned i)
{
    assert(0 <= i && i < size_i);
    
    unsigned k = index_nth(lines, i);
    lines[k] = false;
    
}
void Matrix::removeRow(unsigned j)
{    
    assert(0 <= j && j < size_j);
    
    unsigned k = index_nth(rows, j);
    rows[k] = false;
}

void Matrix::set(unsigned i, unsigned j, scalar_t x) 
{
    assert(0 <= i && i < size_i);
    assert(0 <= j && j < size_j);
    /* Looking for the actual "i,j" */
    
    unsigned k = index_nth(lines, i);
    unsigned l = index_nth(rows, j);
  
    cout << k << ", " << l << endl;
    contents[index][k][l] = x;
}

Matrix::scalar_t Matrix::get(unsigned i, unsigned j) const 
{
    assert(0 <= i && i < size_i);
    assert(0 <= j && j < size_j);
    
    unsigned k = index_nth(lines, i);
    unsigned l = index_nth(rows, j);
    
    return contents[index][k][l];
}

void Matrix::print() const 
{
    for (unsigned i = 0; i < size_i; i++) 
    {
        if (lines[i])
        for (unsigned j = 0; j < size_j; j++) 
        {
            if (rows[j])
                cout << setprecision(2) << setw(8) << contents.at(index).at(i).at(j);
        }
        cout << endl;
    }
    cout << "___________________________" << endl;
}

/*****************************************************/

Matrix operator+(const Matrix& M1, const Matrix& M2) {
  assert(M1.get_size_i() == M2.get_size_i());
  assert(M1.get_size_j() == M2.get_size_j());
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M1.get_size_j();
  Matrix M(size_i, size_j);

  for (unsigned i = 0; i < size_i; i++) {
    for (unsigned j = 0; j < size_j; j++) {
      Matrix::scalar_t x =  M1.get(i, j) + M2.get(i, j);
      M.set(i, j, x);
    }
  }

  return M;
}

Matrix operator-(const Matrix& M1, const Matrix& M2) {
  assert(M1.get_size_i() == M2.get_size_i());
  assert(M1.get_size_j() == M2.get_size_j());
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M1.get_size_j();
  Matrix M(size_i, size_j);

  for (unsigned i = 0; i < size_i; i++) {
    for (unsigned j = 0; j < size_j; j++) {
      Matrix::scalar_t x =  M1.get(i, j) - M2.get(i, j);
      M.set(i, j, x);
    }
  }

  return M;
}

Matrix operator*(Matrix::scalar_t a, const Matrix& M1) {
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M1.get_size_j();
  Matrix M(size_i, size_j);

  for (unsigned i = 0; i < size_i; i++) {
    for (unsigned j = 0; j < size_j; j++) {
      Matrix::scalar_t x = a * M1.get(i, j);
      M.set(i, j, x);
    }
  }

  return M;
}

Matrix operator*(const Matrix& M1, const Matrix& M2) {
  assert(M1.get_size_j() == M2.get_size_i());
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M2.get_size_j();
  unsigned size_k = M1.get_size_j(); // = M2.get_size_i
  Matrix M(size_i, size_j);

  for (unsigned i = 0; i < size_i; i++) {
    for (unsigned j = 0; j < size_j; j++) {
      Matrix::scalar_t x = 0.0;
      for (unsigned k = 0; k < size_k; k++)
        x +=  M1.get(i, k) * M2.get(k, j);
      M.set(i, j, x);
    }
  }

  return M;
}

Matrix Id(unsigned n) {
  unsigned size = n;
  Matrix M(size, size);
  for (unsigned i = 0; i < size; i++) {
    M.set(i, i, 1.0);
  }
  return M;
}

double norm(const Matrix& M1) {
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M1.get_size_j();

  Matrix::scalar_t n = 0.0;
  
  for (unsigned i = 0; i < size_i; i++) {
    for (unsigned j = 0; j < size_j; j++) {
      Matrix::scalar_t x = fabs(M1.get(i, j));
      if (n < x)
        n = x;
    }
  }
  return n;
}

/*

static Matrix submatrix(const Matrix& M1, unsigned a, unsigned b) {	//Note it is static!
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M1.get_size_j();
  assert (0 <= a && a < size_i);
  assert (0 <= b && b < size_j);
  assert(size_i >= 2);
  assert(size_j >= 2);
  
  
  Matrix M(size_i - 1, size_j - 1);

  for (unsigned i = 0; i < size_i - 1; i++) {
    for (unsigned j = 0; j < size_j - 1; j++) {
      Matrix::scalar_t x = M1.get(i + (i >= a), j + (j >= b));
      M.set(i, j, x);
    }
  }
  
  return M;
}

static int toggle(unsigned i) {   //Note it is static!
  if (i % 2 == 0)
    return 1;
  else
    return -1;
}

Matrix::scalar_t determinant(const Matrix& M1) {
  assert(M1.get_size_i() == M1.get_size_j());
  unsigned size = M1.get_size_i();
  
  if (size == 1)
    return M1.get(0, 0);
  
  
  Matrix::scalar_t s = 0.0;
  
  for(unsigned k = 0; k < size; k++)
    s += M1.get(k, 0) * toggle(k) * determinant(submatrix(M1, k, 0));  
  
  return s;
}

Matrix transpose(const Matrix& M1) {
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M1.get_size_j();
  Matrix M(size_j, size_i);

  for (unsigned i = 0; i < size_i; i++) {
    for (unsigned j = 0; j < size_j; j++) {
      Matrix::scalar_t x = M1.get(i, j);
      M.set(j, i, x);
    }
  }
  
  return M;
}

Matrix inverse(const Matrix& M1) {
  unsigned size_i = M1.get_size_i();
  unsigned size_j = M1.get_size_j();
  assert(size_i == size_j);

  Matrix::scalar_t det = determinant(M1);
  if (det == 0) {
    cerr << "Cannot invert a matrix with null determinant" << endl;
    M1.print();
    exit(1);
  }

  unsigned size = size_i;
  Matrix cofactors(size, size);
  Matrix M2 = transpose(M1);	// Do not forget it!

  for (unsigned i = 0; i < size; i++) {
    for (unsigned j = 0; j < size; j++) {
      Matrix M = submatrix(M2, i, j);

      Matrix::scalar_t x = determinant(M);
      Matrix::scalar_t y =  toggle(i+j) * (x / det);
      cofactors.set(i, j, y);
    }
  }

  return cofactors;
}
*/
