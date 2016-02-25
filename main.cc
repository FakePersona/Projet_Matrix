#include "main.hh"
#include <time.h>

using namespace std;

int main() 
{
    int n = 4;
    
    srand(time(NULL));
    
    int i;
    
    time_t begin, end;
    int max;
    
    for(n = 2; n < 9; n++)
    {
        cout << "n = " << n << " ; \t" << flush;
        max = 2000/(n*n*n);
        begin = clock();
        for(i = 0; i < max; i++)
        {
            Matrix M(n, n);
            M.fill_random(-10.0, 10.0);
            Matrix M2(inverse(M));
        }
        end = clock();
        cout << setw(8) << (double)(end - begin) / CLOCKS_PER_SEC / max << "\t;\t" << flush;
        begin = clock();
        for(i = 0; i < max; i++)
        {
            Matrix M(n, n);
            M.fill_random(-10.0, 10.0);
            Matrix M2(inverse2(M));
        }
        end = clock();
        cout << setw(8) << (double)(end - begin) / CLOCKS_PER_SEC / max << endl;
    }
    
    
    

    // See example at http://www.math.cornell.edu/~andreim/Lec17.pdf
    
    /*
    M.set(0, 0, 0.0);
    M.set(1, 0, -2.0);
    M.set(2, 0, 4.0);
    M.set(0, 1, 1.0);
    M.set(1, 1, 3.0);
    M.set(2, 1, 0.0);
    M.set(0, 2, 2.0);
    M.set(1, 2, -1.0);
    M.set(2, 2, 1.0);
    */
    
    
    //M.removeRow(0);


    /**************************
    Matrix M:

        0       1       2
        -2       3      -1
        4       0       1

    Determinant: -26

    Matrix MM:

    -0.12   0.038    0.27
    0.077    0.31    0.15
        0.46   -0.15  -0.077

    **************************/
/*
    cout << M << M << M;
  //  Matrix MM = inverse(M);
    
    
  //  cout << MM;
    cout << difftime(time(NULL), tbegin) << endl;
    tbegin = time(NULL);
    
    Matrix MMM(inverse2(M));
    cout << MMM;
    cout << difftime(time(NULL), tbegin) << endl;
    //  cout << determinant(M) << endl;;
    //  MM.print();
*/
    //  cout << norm((M * MM) - Id(n)) << " " <<  norm((MM * M) - Id(n)) << endl;
    
    
    return 0;
}
