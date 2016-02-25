#pragma once

#include <vector>
#include <ctime>

using namespace std;




class Matrix 
{
    public:
        typedef double scalar_t;

    private:
        unsigned size_i, size_j, index;
        vector<bool> lines, rows;
        static vector<vector<vector<scalar_t> > > contents;
        static vector<unsigned> count;

    public:
        static void print_matrix(unsigned index);
        
        Matrix(unsigned n, unsigned p);
        Matrix(const Matrix& m);
        ~Matrix();
        
        unsigned get_size_i(void) const;
        unsigned get_size_j(void) const;
        
        void remove_line(unsigned i);
        void remove_row(unsigned j);
        
        void set(unsigned i, unsigned j, scalar_t x);
        scalar_t get(unsigned i, unsigned j) const;
        
        void fill_random(scalar_t min, scalar_t max); 

        void print(ostream &flux) const;
};

/*****************************************************/

ostream &operator<<( ostream &f, Matrix const& M);

Matrix operator+(const Matrix& M1, const Matrix& M2);

Matrix operator-(const Matrix& M1, const Matrix& M2);

Matrix operator*(Matrix::scalar_t a, const Matrix& M1);

Matrix operator*(const Matrix& M1, const Matrix& M2);

Matrix transpose(const Matrix& M1);

Matrix Id(unsigned n);

double norm(const Matrix& M1);

Matrix::scalar_t determinant(const Matrix& M1);
Matrix::scalar_t determinant2(const Matrix& M1);

Matrix inverse(const Matrix& M1);
Matrix inverse2(const Matrix& M1);

