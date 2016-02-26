#include "experiment.hh"

using namespace std;


Experiment::Experiment()
{
    fct = NULL;
    nb = 1;
    param = 0;
    
    reset();
}

Experiment::Experiment(double (*fct_)(unsigned))
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

void Experiment::set_function(double (*fct_)(unsigned))
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

// Executes the function fct nb times, using param value,
// and computes mean value, variance, and standard deviation
// of the values returned by fct.
// It returns a const reference to the object itself.
const Experiment& Experiment::operator()(unsigned nb_, unsigned param_)
{
    nb = nb_;
    param = param_;
    
    reset();
    
    if (nb == 0)
        return *this;   
    
    for(unsigned i = 0; i < nb; i++)
    {
        double x = fct(param);
        mean += x;
        var += x * x;
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