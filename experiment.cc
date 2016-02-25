#include "experiment.hh"

using namespace std;


// returns the difference between t1 and t2 in seconds
static double time_diff(time_t t1, time_t t2)
{
    return (double)(t2 - t1) / CLOCKS_PER_SEC;
}


Experiment::Experiment()
{
    fct = NULL;
    nb = 1;
    param = 0;
    
    reset();
}

Experiment::Experiment(void (*fct_)(unsigned))
{
    fct = fct_;
    nb = 1;
    param = 0;
    
    reset();
}

void Experiment::reset()
{
    mean = 0.0;
    var = 0.0;
    sd = 0.0;
}

void Experiment::set_function(void (*fct_)(unsigned))
{
    fct = fct_;
}

double Experiment::get_mean() const
{
    return mean;
}

double Experiment::get_var() const
{
    return var;
}

double Experiment::get_sd() const
{
    return sd;
}

// executes the function f nb times, using param value,
// and computes mean value, variance, and standard deviation
// of execution time
const Experiment& Experiment::operator()(unsigned nb_, unsigned param_)
{
    nb = nb_;
    param = param_;
    
    reset();
    
    if (nb == 0)
        return *this;   
    
    for(unsigned i = 0; i < nb; i++)
    {
        time_t t1 = clock();
        fct(param);
        time_t t2 = clock();
        double t = time_diff(t1, t2);
        mean += t;
        var += t * t;
    }
    
    mean /= nb;
    var /= nb;
    var -= mean * mean;
    
    sd = sqrt(var);
    
    return *this;
}

void Experiment::print(ostream &f) const
{
    f << param << " ; " <<
         nb << " ; " <<
         mean << " ; " <<
         var << " ; " <<
         sd;
}

ostream &operator<<( ostream &f, Experiment const& exp)
{
    exp.print(f);
    return f;
}