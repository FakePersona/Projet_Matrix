#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;



// This class handles an experiment
// It uses a function, which will be called multiple times
// Then, mean value, variance and standard deviation will be computed
class Experiment
{
    public:
        Experiment();
        Experiment(double (*fct_)(unsigned));
        
        void reset();
        
        void set_function(double (*fct_)(unsigned));
        
        double get_mean() const;
        double get_var() const;
        double get_sd() const;
        
        
        const Experiment& operator()(unsigned nb_, unsigned param_);
        void print(ostream &flux) const;
        
    private:
        double (*fct)(unsigned);     
        
        unsigned nb;
        unsigned param;
        
        double mean;
        double var; // variance
        double sd;  // standard deviation
};



ostream &operator<<( ostream &f, Experiment const& exp);
