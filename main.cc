#include "main.hh"

using namespace std;




void test1(unsigned size)
{
    Matrix::random(size, size, -10.0, 10.).inverse();
}


void test2(unsigned size)
{
    Matrix M = Matrix::random(size, size, -10.0, 10.);
    M.use_static(true);
    M.inverse();
}




int main() 
{    
    srand(time(NULL)); // random seed
    
    
    Experiment exp1(test1);
    Experiment exp2(test2);
    
    
    
    Matrix m = Matrix::Hilbert(5);    
    cout << m.inverse() * m << m * m.inverse() << endl;
    
    
    
    ofstream log("log2.csv");
    int max = 42000;
    
    for(unsigned n = 2; n < 10; n++)
    {
        max /= n;
        if (max < 1)
            max = 1;
        cout << "exp1 : " << exp1(max, n) << endl;
        cout << "exp2 : " << exp2(max, n) << endl;
    }
    
    
    
    return 0;
}
