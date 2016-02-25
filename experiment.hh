#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;



// This class handles an experiment
// It uses a function, which will be called multiple times
// Then, mean value, variance and standard deviation 
// of execution time will be computed
class Experiment
{
    public:
        Experiment();
        Experiment(void (*fct_)(unsigned));
        
        void reset();
        
        void set_function(void (*fct_)(unsigned));
        
        double get_mean() const;
        double get_var() const;
        double get_sd() const;
        
        
        const Experiment& operator()(unsigned nb_, unsigned param_);
        void print(ostream &flux) const;
        
    private:
        void (*fct)(unsigned);     
        
        unsigned nb;
        unsigned param;
        
        double mean;
        double var; // variance
        double sd;  // standard deviation
};



ostream &operator<<( ostream &f, Experiment const& exp);
