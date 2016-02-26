#include "matrix.hh"
#include "main.hh"


using namespace std;

string filename1 = "comparaison.data";
string filename2 = "error.data";



double time_diff(time_t t1, time_t t2)
{
    return (double)(t2 - t1) / (CLOCKS_PER_SEC);
}


double test_inv1(unsigned size)
{
    time_t t1 = clock();
    Matrix<double>::random(size, size, -10.0, 10.).inverse();
    
    return time_diff(t1, clock());
}

double test_inv2(unsigned size)
{
    time_t t1 = clock();

    Matrix<double> M = Matrix<double>::random(size, size, -10.0, 10.);
    M.use_static(true);
    M.inverse();

    return time_diff(t1, clock());
}

double test_hilbert(unsigned size)
{
    Matrix<double> M = Matrix<double>::Hilbert(size);
    Matrix<double> MM = M.inverse();
    Matrix<double> E = (M*MM - Matrix<double>::Id(size));
    
    return E.norm();
}



int main(int argc, char* argv[]) 
{    
    Experiment exp1(test_inv1);
    Experiment exp2(test_inv2);
    Experiment exp3(test_hilbert);
    
    ofstream ofs_inv1("inv1.data");
    ofstream ofs_inv2("inv2.data");
    ofstream ofs_hilbert("hilbert.data");
    
    assert(ofs_inv1.is_open() && ofs_inv2.is_open() && ofs_hilbert.is_open());
    
    ofs_inv1 << "n\tmean\tsd" << endl;
    ofs_inv2 << "n\tmean\tsd" << endl;
    ofs_hilbert << "n\tmean\tsd" << endl;
    
    unsigned nb = 42000;
    
    for (unsigned i = 2; i < 7; i++)
    {        
        nb /= i;
        if (nb < 1)
            nb = 1;
        
        ofs_inv1 << exp1(nb, i) << endl;
        ofs_inv2 << exp2(nb, i) << endl;
        ofs_hilbert << exp3(nb, i) << endl;
    }
    
    ofs_inv1.close();
    ofs_inv2.close();
    ofs_hilbert.close();
    
    return 0;
    
}
 
