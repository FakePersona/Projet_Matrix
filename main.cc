#include "main.hh"
#include <time.h>

using namespace std;

int main() 
{    
    int n;
    int i;
    time_t begin, end;
    int max = 42000;
    
    srand(time(NULL));
    
    Matrix m = Matrix::Hilbert(5);
    
    cout << m.inverse() * m << m * m.inverse() << endl;
    
    
    
    ofstream log("log2.csv");
    
    cout << "n;inverse;inverse2;test(s)" << endl;
    log << "n;inverse;inverse2;test(s)" << endl;
    
    for(n = 2; n < 10; n++)
    {
        cout << n << ";" << flush;
        max /= n;
        if (max < 1)
            max = 1;
        begin = clock();
        
        for(i = 0; i < max; i++)
        {
            Matrix M = Matrix::random(n, n, -10.0, 10.);
            Matrix M2(M.inverse());
        }
        
        end = clock();
        
        cout << setw(8) << (double)(end - begin) / CLOCKS_PER_SEC / max << ";" << flush;
        log << setw(8) << (double)(end - begin) / CLOCKS_PER_SEC / max << ";" << flush;
        
        begin = clock();
        
        for(i = 0; i < max; i++)
        {
            Matrix M = Matrix::random(n, n, -10.0, 10.);
            M.use_static(true);
            Matrix M2(M.inverse());
        }
        
        end = clock();
        
        cout << setw(8) << (double)(end - begin) / CLOCKS_PER_SEC / max << ";" << max << endl;
        log << setw(8) << (double)(end - begin) / CLOCKS_PER_SEC / max << ";" << max << endl;
    }
    
    
    
    return 0;
}
