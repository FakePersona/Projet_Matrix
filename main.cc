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
    
    
    
    Matrix m = Matrix::Hilbert(5);    
    cout << m.inverse() * m << m * m.inverse() << endl;
    
    
    
    ofstream log("log2.csv");
    int max = 42000;
    
    /*
    for(unsigned n = 2; n < 10; n++)
    {
        
        max /= n;
        if (max < 1)
            max = 1;
        cout << "exp1 : " << exp1(max, n) << endl;
        cout << "exp2 : " << exp2(max, n) << endl;
    }
    */
    
    
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
	
        for(i = 0; i < max; i++)
        {
            Matrix M = Matrix::random(n, n, -10.0, 10.);
            Matrix M2(M.inverse());
	    end = clock();
	    slow.at(i) = (double)(end - begin) / CLOCKS_PER_SEC;
	    begin = end;
	    
        }
        
        
        cout << setw(8) << mean(slow) << ";" << stdvar(slow) << ";" << flush;
        log << setw(8) << mean(slow) << ";"  << stdvar(slow) << ";" << flush;

	vector<double> fast = vector<double>(max,0.0);        

        begin = clock();
        

        for(i = 0; i < max; i++)
        {
            Matrix M = Matrix::random(n, n, -10.0, 10.);
            M.use_static(true);
            Matrix M2(M.inverse());
	    end = clock();
	    fast.at(i) = (double)(end - begin) / CLOCKS_PER_SEC;
	    begin = end;
        }
        
        
        cout << setw(8) << mean(fast) << ";" << stdvar(fast) << ";" << max << endl;
        log << setw(8) << mean(fast) << ";"  << stdvar(fast) << ";" << max << endl;
    }
    
    




    
    return 0;
}
