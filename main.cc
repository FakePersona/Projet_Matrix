
#include "matrix.hh"
#include "main.hh"

using namespace std;



// returns the difference between t1 and t2 in seconds
static double time_diff(time_t t1, time_t t2)
{
    return (double)(t2 - t1) / CLOCKS_PER_SEC;
}


double test1(unsigned size)
{
    time_t t1 = clock();
    Matrix<double>::random(size, size, -10.0, 10.).inverse();
    
    return time_diff(t1, clock());
}

double test2(unsigned size)
{
    time_t t1 = clock();

    Matrix<double> M = Matrix<double>::random(size, size, -10.0, 10.);
    M.use_static(true);
    M.inverse();

    return time_diff(t1, clock());
}

double test3(unsigned size)
{
    Matrix<double> M = Matrix<double>::Hilbert(size);
    Matrix<double> MM = M.inverse();
    Matrix<double> E = (M*MM);

    cout << E << endl;
    
    return E.norm();
}


double mean(vector<double> v)
{
  double sum = 0.0;
  unsigned i;
  for (i=0;i<v.size();i++)
    sum += v.at(i);
  return sum / (double)v.size();
}

double stdvar(vector<double> v)
{
  double sum = 0.0;
  unsigned i;
  for (i=0;i< v.size();i++)
    {
      double avg= mean(v);
      sum += (v.at(i) - avg)*(v.at(i) - avg);
    }
  return sqrt(sum / (double)v.size());
}

int main() 
{    
    srand(time(NULL)); // random seed
    
    
    Experiment exp1(test1);
    Experiment exp2(test2);
    Experiment exp3(test3);
    
    time_t begin, end;
    
    Matrix<double> m = Matrix<double>::Hilbert(7);    
    cout << m.inverse() * m << m * m.inverse() << endl;
    
    
    
    ofstream log("log2.csv");
    unsigned max = 42000;
    
    
    for(unsigned n = 2; n < 10; n++)
    {
        
        max /= n;
        if (max < 1)
            max = 1;
     //   cout << "exp1 : " << exp1(max, n) << endl;
     //   cout << "exp2 : " << exp2(max, n) << endl;
        cout << "exp3 : " << exp3(10, n) << endl;
    }
    
    
    
    max = 42000;
    
    for(unsigned n = 2; n < 8; n++)
    {
        cout << "n;inverse;stdvar;inverse2;stdvar2;test(s)" << endl;
        log << "n;inverse;stdvar;inverse2;stdvar2;test(s)" << endl;
    
        max /= n;
        if (max < 1)
            max = 1;
        cout << "exp1 : " << exp1(max, n) << endl;
        cout << "exp2 : " << exp2(max, n) << endl;
        begin = clock();
        
	vector<double> slow = vector<double>(max,0.0);
	
        for(unsigned i = 0; i < max; i++)
        {
            Matrix<double> M = Matrix<double>::random(n, n, -10.0, 10.);
            Matrix<double> M2(M.inverse());
	    end = clock();
	    slow.at(i) = (double)(end - begin) / CLOCKS_PER_SEC;
	    begin = end;
	    
        }
        
        
        cout << setw(8) << mean(slow) << ";" << stdvar(slow) << ";" << flush;
        log << setw(8) << mean(slow) << ";"  << stdvar(slow) << ";" << flush;

	vector<double> fast = vector<double>(max,0.0);        

        begin = clock();
        

        for(unsigned i = 0; i < max; i++)
        {
            Matrix<double> M = Matrix<double>::random(n, n, -10.0, 10.);
            M.use_static(true);
            Matrix<double> M2(M.inverse());
	    end = clock();
	    fast.at(i) = (double)(end - begin) / CLOCKS_PER_SEC;
	    begin = end;
        }
        
        
        cout << setw(8) << mean(fast) << ";" << stdvar(fast) << ";" << max << endl;
        log << setw(8) << mean(fast) << ";"  << stdvar(fast) << ";" << max << endl;
    }


    
    return 0;
}
