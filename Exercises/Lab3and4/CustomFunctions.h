#include <string>
#include <vector>
#include "gnuplot-iostream.h"
#include "FiniteFunctions.h"

#pragma once //Replacement for IFNDEF

// child classes are all separate and will all inherit
class normFunc : public FiniteFunction {

    public:
       normFunc();  // inherited empty constructor
       normFunc(double range_min, double range_max, double mean, double stdev, std::string outfile);
       double callFunction(double x);
       double evaluate(double x) const override;
       double mean;
       double stdev;

    private:
       double m_mean;
       double m_stdev;
};

class cauchy : public FiniteFunction {

    public:
       cauchy();  // inherited empty constructor
       cauchy(double range_min, double range_max, double gamma, double x0, std::string outfile);
       double callFunction(double x);
       double evaluate(double x) const override;
       double gamma;
       double x0;

    private:
       double m_gamma;
       double m_x0;
};

class crystal : public FiniteFunction {

    public:
       crystal();  // inherited empty constructor
       crystal(double range_min, double range_max, double lowN, double alpha, double sigma, double xHat, std::string outfile);
       double callFunction(double x); 
       double evaluate(double x) const override;
       double lowN;
       double alpha;
       double sigma;
       double xHat;

    private:
       double m_lowN;
       double m_alpha;
       double m_sigma;
       double m_xHat;
};