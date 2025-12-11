#include <iostream>
#include <string>
#include <vector>
#include <cmath>
// #include "FiniteFunctions.h"
#include "CustomFunctions.h"
#include <filesystem> //To check extensions in a nice way

using std::filesystem::path;


// Overloaded constructor for normal distribution
normFunc::normFunc(double range_min, double range_max, double mean, double stdev, std::string outfile){
    // FiniteFunction(range_min, range_max, outfile); this isn't working?
    m_RMin = range_min;
    m_RMax = range_max;
    m_mean = mean;
    m_stdev = stdev;
    this->checkPath(outfile);
}

double normFunc::normalDist(double x){
    const double inv_sqrt_2pi = 1.0/ std::sqrt(2.0 * M_PI);
    double pow = (x - m_mean) / m_stdev;  // power in exponent

    return (inv_sqrt_2pi / m_stdev) * std::exp(-0.5 * pow * pow);
}

// for normFunc to call the normal distribution function instead of invxsquared when integrating
double normFunc::callFunction(double x){return this->normalDist(x);}



// Overloaded constructor for cauchy distribution
cauchy::cauchy(double range_min, double range_max, double gamma, double x0, std::string outfile){
    // FiniteFunction(range_min, range_max, outfile); this isn't working?
    m_RMin = range_min;
    m_RMax = range_max;
    m_gamma = gamma;
    m_x0 = x0;
    this->checkPath(outfile);
}

double cauchy::cauchyFunc(double x){
    double denom = (x - m_x0) * (x - m_x0) + m_gamma * m_gamma;
    return (m_gamma / (M_PI * denom));
}

// for cauchy to call correct function
double cauchy::callFunction(double x){return this->cauchyFunc(x);};


// Overloaded constructor for crystal ball distribution
crystal::crystal(double range_min, double range_max, double lowN, double alpha, double sigma, double xHat, std::string outfile){
    // FiniteFunction(range_min, range_max, outfile); this isn't working?
    m_RMin = range_min;
    m_RMax = range_max;
    m_lowN = lowN;      // power law exponent
    m_alpha = alpha;    // transition point
    m_sigma = sigma;    // gaussian width
    m_xHat = xHat;      // gaussian peak
    this->checkPath(outfile);
}

double crystal::crystalBall(double x){
    const double sqrtPiOver2 = std::sqrt(M_PI / 2.0);
    const double sqrt2 = std::sqrt(2.0);

    double t = (x - m_xHat) / m_sigma;
    double absAlpha = std::fabs(m_alpha);

    // constants
    double A = std::pow(m_lowN / absAlpha, m_lowN) * std::exp(-0.5 * absAlpha * absAlpha);
    double B = m_lowN / absAlpha - absAlpha;

    // normalisation factor
    double C = (m_lowN / absAlpha) * std::exp(-0.5 * absAlpha * absAlpha) / (m_lowN - 1.0); 
    double D = sqrtPiOver2 * (1.0 + std::erf(absAlpha / sqrt2)); 

    double N = 1.0 / (m_sigma * (C + D));  // normalisation constant

    // alpha conditions

    if (t > -absAlpha) {
        return N * std::exp(-0.5 * t * t);

    } else {
        return N * A * std::pow(B - t, -m_lowN);
    }
}

// for crystal to call correct function
double crystal::callFunction(double x){return this->crystalBall(x);};

int main(){

    // NOTES TO COME BACK TO

    // load in random generated data
    // use user input for each test parameter to match to the generated data without recompiling each time
    // implement metropolis algorithm...

    int nPoints = 1000;

    FiniteFunction baseTest(-10, 10, "basetest");
    baseTest.integral(nPoints);
    baseTest.printInfo();
    baseTest.plotFunction();

    normFunc nTest(-10, 10, 0, 2.5, "normtest");
    nTest.integral(nPoints);
    nTest.printInfo();
    nTest.plotFunction();

    cauchy cTest(-10, 10, 2.5, 0, "cauchytest");
    cTest.integral(nPoints);
    cTest.printInfo();
    cTest.plotFunction();

    crystal c2Test(-10, 10, 3, 0.5, 0.5, 0, "crystaltest");
    c2Test.integral(nPoints);
    c2Test.printInfo();
    c2Test.plotFunction();

    return 0;
}