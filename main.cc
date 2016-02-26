#include "matrix.hh"
#include "main.hh"


using namespace std;

string filename1 = "comparaison.data";
string filename2 = "error.data";



double time_diff(time_t t1, time_t t2)
{
    return (double)(t2 - t1) / (CLOCKS_PER_SEC);
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
  ofstream ofs;
  ofs.open (filename1.c_str(), ofstream::out);
  assert(ofs.is_open());
  ofs << "n" << "\t" << "Time" << endl;

  ofstream err;
  err.open (filename2.c_str(), ofstream::out);
  assert(err.is_open());
  
  int n;
  int i;
  time_t begin, end;
  int max = 42000;
  
  srand(time(NULL));
  
  for (n=2;n<8;n++)
    {
      Matrix<double> m = Matrix<double>::Hilbert(n);
    
      err << n << "\t" << (m.inverse() * m - Matrix<double>::Id((unsigned)n)).norm() << endl;
    }
    
    
  ofstream log("log2.csv");
    
  cout << "n;inverse;stdvar;inverse2;stdvar2;test(s)" << endl;
  log << "n;inverse;stdvar;inverse2;stdvar2;test(s)" << endl;
    
  for(n = 2; n < 8; n++)
    {
      cout << n << ";" << flush;
      max /= n;
      if (max < 1)
	max = 1;
      begin = clock();
      
      vector<double> slow = vector<double>(max,0.0);
	
      for(i = 0; i < max; i++)
        {
	  Matrix<double> M = Matrix<double>::random(n, n, -10.0, 10.);
	  Matrix<double> M2(M.inverse());
	  end = clock();
	  slow.at(i) = (double)(end - begin) / CLOCKS_PER_SEC;
	  begin = end;	  
        }
      
      ofs << n << "\t" << mean(slow) << endl;
      cout << setw(8) << mean(slow) << ";" << stdvar(slow) << ";" << flush;
      log << setw(8) << mean(slow) << ";"  << stdvar(slow) << ";" << flush;
      
      vector<double> fast = vector<double>(max,0.0);        
      
      begin = clock();
        

      for(i = 0; i < max; i++)
        {
	  Matrix<double> M = Matrix<double>::random(n, n, -10.0, 10.);
	  M.use_static(true);
	  Matrix<double> M2(M.inverse());
	  end = clock();
	  fast.at(i) = (double)(end - begin) / CLOCKS_PER_SEC;
	  begin = end;
        }
        
        
      ofs << n << "\t" << mean(fast) << endl;
      cout << setw(8) << mean(fast) << ";" << stdvar(fast) << ";" << max << endl;
      log << setw(8) << mean(fast) << ";"  << stdvar(fast) << ";" << max << endl;
    }
    
    
  ofs.close();



    
    return 0;
}
 
