#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

#include <cmath>
#include <cassert>
#include <cstdlib>


using namespace std;



// This class handles a matrix
// Many common operations are defined, such as
// transpose, inverse, determinant, norm...
class Matrix 
{
    public:
        typedef double scalar_t;

        
        
        /*******************************/
        /* constructors and destructor */
        /*******************************/
        
        Matrix(unsigned n, unsigned p);
        Matrix(const Matrix& m);
        ~Matrix();
        
        
        
        /********/
        /* misc */
        /********/
        
        void print(ostream &flux) const;
        
        void remove_line(unsigned i);
        void remove_row(unsigned j);
        
        
        
        /********************/
        /* accessor methods */
        /********************/
        
        unsigned get_size_i(void) const;
        unsigned get_size_j(void) const;
        
        void set(unsigned i, unsigned j, scalar_t x);
        scalar_t get(unsigned i, unsigned j) const;
        
        void use_static(bool b);
        
        
        
        /*********************/
        /* operation methods */
        /*********************/
        
        double norm() const;
        Matrix transpose() const;
        
        Matrix submatrix(unsigned a, unsigned b) const;
        scalar_t determinant() const;
        Matrix inverse() const;
        
        
    
        /******************/
        /* static methods */
        /******************/       
        
        static Matrix Id(unsigned n);
        static Matrix Hilbert(unsigned n);
        static Matrix random(unsigned n, unsigned p, scalar_t min, scalar_t max);

    private:
        static vector<vector<vector<scalar_t> > > contents;
        static vector<unsigned> count;
        
        
        unsigned size_i, size_j, index;
        vector<bool> lines, rows;
        
        bool use_static_opt;
};



        
/*************/
/* operators */
/*************/

ostream &operator<<( ostream &f, Matrix const& M);
Matrix operator+(const Matrix& M1, const Matrix& M2);
Matrix operator-(const Matrix& M1, const Matrix& M2);
Matrix operator*(Matrix::scalar_t a, const Matrix& M1);
Matrix operator*(const Matrix& M1, const Matrix& M2);






