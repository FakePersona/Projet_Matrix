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
template<typename T>
class Matrix 
{
    public:        
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
        
        void set(unsigned i, unsigned j, T x);
        T get(unsigned i, unsigned j) const;
        
        void use_static(bool b);
        
        
        
        /*********************/
        /* operation methods */
        /*********************/
        
        double norm() const;
        Matrix transpose() const;
        
        Matrix submatrix(unsigned a, unsigned b) const;
        T determinant() const;
        Matrix inverse() const;
        
        
    
        /******************/
        /* static methods */
        /******************/       
        
        static Matrix Id(unsigned n);
        static Matrix Hilbert(unsigned n);
        static Matrix random(unsigned n, unsigned p, T min, T max);

    private:
        static vector<vector<vector<T> > > contents;
        static vector<unsigned> count;
        
        
        unsigned size_i, size_j, index;
        vector<bool> lines, rows;
        
        bool use_static_opt;
};


template<typename T>
ostream &operator<<( ostream &f, Matrix<T> const& M);
template <typename T>
Matrix<T> operator+(const Matrix<T>& M1, const Matrix<T>& M2);
template <typename T>
Matrix<T> operator-(const Matrix<T>& M1, const Matrix<T>& M2);
template <typename T>
Matrix<T> operator*(T a, const Matrix<T>& M1);
template <typename T>
Matrix<T> operator*(const Matrix<T>& M1, const Matrix<T>& M2);




template<typename T> 
vector<vector<vector<T> > > Matrix<T>::contents;

template<typename T>
vector<unsigned> Matrix<T>::count;










/******************************************/
/*      constructors and destructor       */
/******************************************/

// creates an empty matrix of size n*p
template<typename T>
Matrix<T>::Matrix(unsigned n, unsigned p) 
{
    size_i = n;
    size_j = p;
    assert(1 <= size_i);
    assert(1 <= size_j);

    lines = vector<bool>(size_i, true);    
    rows = vector<bool>(size_j, true);
    
    use_static_opt = false;
    
    index = 0;
    
    // find the first empty matrix in contents
    while (index < contents.size() && count[index] > 0)
        index++;
    
    
    // if all matrices are used, we create a new one
    if(index == contents.size())
    {
        contents.push_back( vector<vector<T> >(size_i) );
        count.push_back(1);
    }
    else // if one matrix is not used anymore, we replace it
    {
        contents[index] = vector<vector<T> >(size_i);
        count[index] = 1;
    }
        
    for (unsigned i = 0; i < size_i; i++) // Initialization to 0.0
        contents[index][i] = vector<T>(size_j, 0.0); 
    
}

// copy constructor
template<typename T>
Matrix<T>::Matrix(const Matrix& m)  
{
    size_i = m.size_i;
    size_j = m.size_j;
    index = m.index;
    lines = m.lines;
    rows = m.rows;
    use_static_opt = m.use_static_opt;
    
    count[index]++;
}

// destructor
// clears the matrix in the vector contents if 
// it is not used anymore.
template<typename T>
Matrix<T>::~Matrix()
{
    count[index]--;
    
    if (count[index] <= 0)
        contents[index].clear();
}



/******************************************/
/*                  misc                  */
/******************************************/

// returns (-1)^i
static int toggle(unsigned i) //Note it is static!
{   
    if (i % 2 == 0)
        return 1;
    else
        return -1;
}

// returns the index of the n-th positive value of vect
static unsigned index_nth(vector<bool> vect, unsigned n) 
{    
    unsigned count = 0, k;
    for (k = 0; count <= n && k < vect.size(); k++)
        count += vect[k];
    
    return k-1;
}

template<typename T>
void Matrix<T>::print(ostream &f) const 
{
    for (unsigned i = 0; i < size_i; i++) 
    {
        for (unsigned j = 0; j < size_j; j++) 
            f << setprecision(2) << setw(8) << get(i,j);
        
        f << endl;
    }
    f << "___________________________" << endl;
}

// remove the line i by setting the
// i-th active line to false in lines
template<typename T>
void Matrix<T>::remove_line(unsigned i)
{
    assert(0 <= i && i < size_i);
    
    unsigned k = index_nth(lines, i);
    lines[k] = false;
    
    size_i--;    
}

// remove the row i by setting the
// i-th active row to false in rows
template<typename T>
void Matrix<T>::remove_row(unsigned j)
{    
    assert(0 <= j && j < size_j);
    
    unsigned k = index_nth(rows, j);
    rows[k] = false;
    
    size_j--;
}




/******************************************/
/*            accessor methods            */
/******************************************/

template<typename T>
unsigned Matrix<T>::get_size_i() const 
{
    return size_i;
}

template<typename T>
unsigned Matrix<T>::get_size_j() const 
{
    return size_j;
}

template<typename T>
void Matrix<T>::set(unsigned i, unsigned j, T x) 
{
    assert(0 <= i && i < size_i);
    assert(0 <= j && j < size_j);
    
    unsigned k = index_nth(lines, i);
    unsigned l = index_nth(rows, j);
  
    contents[index][k][l] = x;
}

template<typename T>
T Matrix<T>::get(unsigned i, unsigned j) const 
{
    assert(0 <= i && i < size_i);
    assert(0 <= j && j < size_j);
    
    unsigned k = index_nth(lines, i);
    unsigned l = index_nth(rows, j);
    
    return contents[index][k][l];
}

// set the option use_static_opt
// depending on the value of use_static_opt, the optimization 
// using the static vector will or will not be used
template<typename T>
void Matrix<T>::use_static(bool b)
{
    use_static_opt = b;
}



/******************************************/
/*           operation methods            */
/******************************************/

// computes the infinity norm of the matrix
template<typename T>
double Matrix<T>::norm() const
{
    T n = 0.0;
    
    for (unsigned i = 0; i < size_i; i++) 
    {
        for (unsigned j = 0; j < size_j; j++) 
        {
            T x = fabs(get(i, j));
            if (n < x)
                n = x;
        }
    }
    return n;
}

// returns the transpose of the matrix
template<typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix M(size_j, size_i);

    for (unsigned i = 0; i < size_i; i++) 
        for (unsigned j = 0; j < size_j; j++) 
            M.set(j, i, get(i, j));
    
    return M;
}

// returns the submatrix obtained by deleting line a and row b.
// depending on the value of use_static_opt, the optimization 
// using the static vector will or will not be used
template<typename T>
Matrix<T> Matrix<T>::submatrix(unsigned a, unsigned b) const
{
    assert (0 <= a && a < size_i);
    assert (0 <= b && b < size_j);
    assert(size_i >= 2);
    assert(size_j >= 2);
    
    if (!use_static_opt)
    {
        Matrix M(size_i - 1, size_j - 1);

        for (unsigned i = 0; i < size_i - 1; i++) 
        {
            for (unsigned j = 0; j < size_j - 1; j++) 
            {
                // (i >= a) and (j >= b) and create a shift
                // that will allow us to pick the right value
                // in the original matrix
                T x = get(i + (i >= a), j + (j >= b));                  
                M.set(i, j, x);
            }
        }
        return M;
    }
    else
    {
        Matrix M(*this);
        
        M.remove_line(a);
        M.remove_row(b);
        
        return M;
    }
}

// returns the determinant of the matrix
template<typename T>
T Matrix<T>::determinant() const 
{
    assert(size_i == size_j);
    unsigned size = size_i;
    
    if (size == 1)
        return get(0, 0);
    
    
    T s = 0.0;
    
    for(unsigned k = 0; k < size; k++)
        s += get(k, 0) * toggle(k) * submatrix(k, 0).determinant();  
    
    return s;
}

// Returns the inverse of the matrix
// Exit the programme if the matrix isn't invertible
template<typename T>
Matrix<T> Matrix<T>::inverse() const
{
    assert(size_i == size_j);
    unsigned size = size_i; // = size_j

    T det = determinant();
    if (det == 0) 
    {
        cerr << "Cannot invert a matrix with null determinant" << endl;
        exit(1);
    }

    Matrix<T> cofactors(size, size);
    cofactors.use_static_opt = use_static_opt;

    for (unsigned i = 0; i < size; i++) 
    {
        for (unsigned j = 0; j < size; j++) 
        {
            Matrix M = submatrix(i, j);
            M.use_static_opt = use_static_opt;

            T x = M.determinant();
            T y =  toggle(i+j) * (x / det);
            cofactors.set(i, j, y);
        }
    }
    
    Matrix tr_cofactors = cofactors.transpose();
    return tr_cofactors;
}



/******************************************/
/*            static methods              */
/******************************************/

// returns Identity matrix of size n
template<typename T>
Matrix<T> Matrix<T>::Id(unsigned n)
{
    Matrix M(n, n);
    for (unsigned i = 0; i < n; i++) 
        M.set(i, i, 1.0);
    
    return M;
}

// returns Hilbert matrix of size n
template<typename T>
Matrix<T> Matrix<T>::Hilbert(unsigned n)
{
    Matrix M(n, n);
    for (unsigned i = 0; i < n; i++) 
        for (unsigned j = 0; j < n; j++) 
            M.set(i, j, 1.0 / (i + j + 1.0));
    
    return M;
}

// return a random of size n*p.
// Every number are chosen randomly in [min, max]
template<typename T>
Matrix<T> Matrix<T>::random(unsigned n, unsigned p, T min, T max)
{
    assert(1 <= n);
    assert(1 <= p);
    assert(0 < max - min);
    
    Matrix M(n, p);
    for (unsigned i = 0; i < n; i++) 
    {
        for (unsigned j = 0; j < p; j++) 
        {
            T x = min + (T) (rand()) / ((RAND_MAX/(max-min)));                 
            M.set(i, j, x);
        }
    }
    
    return M;
}







/******************************************/
/*               operators                */
/******************************************/

template<typename T>
ostream &operator<<( ostream &f, Matrix<T> const& M)
{
    M.print(f);
    return f;
}


// adds two matrices
template <typename T>
Matrix<T> operator+(const Matrix<T>& M1, const Matrix<T>& M2) 
{
    assert(M1.get_size_i() == M2.get_size_i());
    assert(M1.get_size_j() == M2.get_size_j());
    unsigned size_i = M1.get_size_i();
    unsigned size_j = M1.get_size_j();
    Matrix<T> M(size_i, size_j);

    for (unsigned i = 0; i < size_i; i++) 
    {
        for (unsigned j = 0; j < size_j; j++) 
        {
            T x =  M1.get(i, j) + M2.get(i, j);
            M.set(i, j, x);
        }
    }

    return M;
}

// substracts two matrices
template <typename T>
Matrix<T> operator-(const Matrix<T>& M1, const Matrix<T>& M2) 
{
    assert(M1.get_size_i() == M2.get_size_i());
    assert(M1.get_size_j() == M2.get_size_j());
    unsigned size_i = M1.get_size_i();
    unsigned size_j = M1.get_size_j();
    Matrix<T> M(size_i, size_j);

    for (unsigned i = 0; i < size_i; i++) 
    {
        for (unsigned j = 0; j < size_j; j++) 
        {
            T x =  M1.get(i, j) - M2.get(i, j);
            M.set(i, j, x);
        }
    }

    return M;
}

// multiplies a scalar and a matrix
template <typename T>
Matrix<T> operator*(T a, const Matrix<T>& M1) 
{
    unsigned size_i = M1.get_size_i();
    unsigned size_j = M1.get_size_j();
    Matrix<T> M(size_i, size_j);

    for (unsigned i = 0; i < size_i; i++) 
    {
        for (unsigned j = 0; j < size_j; j++) 
        {
            T x = a * M1.get(i, j);
            M.set(i, j, x);
        }
    }

    return M;
}

// multiplies two matrices
template <typename T>
Matrix<T> operator*(const Matrix<T>& M1, const Matrix<T>& M2) 
{
    assert(M1.get_size_j() == M2.get_size_i());
    unsigned size_i = M1.get_size_i();
    unsigned size_j = M2.get_size_j();
    unsigned size_k = M1.get_size_j(); // = M2.get_size_i()
    Matrix<T> M(size_i, size_j);

    for (unsigned i = 0; i < size_i; i++) 
    {
        for (unsigned j = 0; j < size_j; j++) 
        {
            T x = 0.0;
            for (unsigned k = 0; k < size_k; k++)
                x +=  M1.get(i, k) * M2.get(k, j);
            M.set(i, j, x);
        }
    }

    return M;
}
